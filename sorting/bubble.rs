fn bubble_sort (arr: &mut Vec<i32>){
    let mut changed = true;
    let mut mem: i32;
    while changed == true{
        changed = false;
        for j in 0..arr.len() -1 {
            if arr[j] > arr[j+1]{
                mem = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = mem;
                changed = true;
            }
        }
    }
}

fn main(){
    let mut arr = vec![7,4,2,3, 1, 5, 9, 8];
    bubble_sort(&mut arr);
    println!("{:?}", arr);
}
