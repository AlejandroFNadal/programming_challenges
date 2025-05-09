use std::env;
use std::process::Command;
use std::fs::{self, File, OpenOptions};
use std::io::{Write, Result};
use std::time::Instant;

/// A single result record for CSV output
struct Record {
    fs: &'static str,
    mount_opts: &'static str,
    duration_ms: u128,
}

/// Number of files and per-file chunk size
const FILE_COUNT: usize = 50000;
const CHUNK_SIZE: usize = 1024; // 1 KiB per file, 
const DIR_BATCH_SIZE: usize = 100;

fn main() -> Result<()> {
    // Expect the device path as the only argument
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        eprintln!("Usage: {} <device_path>", args[0]);
        std::process::exit(1);
    }
    let device = &args[1];
    let mountpoint = "/mnt/sdcard";
    fs::create_dir_all(mountpoint)?;

    let mut results: Vec<Record> = Vec::new();

    // Benchmark FAT32 and ext4
    benchmark_fs("ext4", device, mountpoint, &mut results, &["-F", "-i", "4096"], "ext4");
    benchmark_fs("FAT32", device, mountpoint, &mut results, &["-F", "32","-s", "1"], "vfat");

    // Output CSV
    println!("fs,mount_options,duration_ms");
    for rec in results {
        println!("{},{},{}", rec.fs, rec.mount_opts, rec.duration_ms);
    }
    Ok(())
}

/// Formats, mounts, writes initial files, then measures write performance
fn benchmark_fs(
    fs_name: &'static str,
    device: &str,
    mountpoint: &str,
    results: &mut Vec<Record>,
    mkfs_opts: &[&str],
    mkfs_cmd: &str,
) {
    println!("=== Benchmarking {} on {} ===", fs_name, device);

    // 1) Format
    Command::new(format!("mkfs.{}", mkfs_cmd))
        .args(mkfs_opts)
        .arg(device)
        .status()
        .expect("mkfs failed");

    // 2) Mount and create files
    mount_device(device, mountpoint, "");
    let init_buf = vec![b'x'; CHUNK_SIZE];
    for i in 0..FILE_COUNT {
        let dir_index = i / DIR_BATCH_SIZE;
        let dir_path = format!("{}/dir_{}", mountpoint, dir_index);
        fs::create_dir_all(&dir_path).expect("create dir failed");
        let path = format!("{}/file_{}", dir_path, i);
        let mut f = File::create(&path).expect("create file failed");
        f.write_all(&init_buf).expect("initial write failed");
        // print every 1000 files
        if i % 1000 == 0 {
            println!("Created {} files", i);
        }
    }
    Command::new("sync").status().unwrap();
    unmount_device(mountpoint);

    // 3) Mount with noatime, measure write
    mount_device(device, mountpoint, "noatime");
    let d_noatime = write_bench(mountpoint);
    results.push(Record { fs: fs_name, mount_opts: "noatime", duration_ms: d_noatime });
    unmount_device(mountpoint);

    // 4) Mount default, measure write
    mount_device(device, mountpoint, "");
    let d_default = write_bench(mountpoint);
    results.push(Record { fs: fs_name, mount_opts: "default", duration_ms: d_default });
    unmount_device(mountpoint);
}

fn mount_device(device: &str, mountpoint: &str, opts: &str) {
    let mut args = Vec::new();
    if !opts.is_empty() {
        args.push("-o".to_string()); args.push(opts.to_string());
    }
    args.push(device.to_string()); args.push(mountpoint.to_string());
    Command::new("mount").args(&args).status().expect("mount failed");
}

fn unmount_device(mountpoint: &str) {
    Command::new("umount").arg(mountpoint).status().expect("umount failed");
}
///
/// Write benchmark (writes one more chunk to each file in its directory)
fn write_bench(mountpoint: &str) -> u128 {
    let start = Instant::now();
    let write_buf = vec![b'y'; CHUNK_SIZE];
    for i in 0..FILE_COUNT {
        let dir_index = i / DIR_BATCH_SIZE;
        let path = format!("{}/dir_{}/file_{}", mountpoint, dir_index, i);
        let mut f = OpenOptions::new()
            .write(true)
            .open(&path)
            .expect("open file failed");
        f.write_all(&write_buf).expect("write failed");
        // print every 1000 files
        if i % 1000 == 0 {
            println!("Wrote {} files", i);
        }
    }
    Command::new("sync").status().unwrap();
    start.elapsed().as_millis()
}

