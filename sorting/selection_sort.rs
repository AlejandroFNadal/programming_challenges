fn selection_sort(arr: &mut Vec<i32>){
    if arr.len() == 0 || arr.len() == 1{
        return ;
    } else{
        let mut i = 0;
        let mut mem: i32;
        let mut j: usize;
        let mut mem_pos;
        while i < arr.len(){
            mem_pos = i;
            mem = arr[i];
            j = i + 1;
            while j < arr.len(){
                // Search the smallest
                if arr[j] < mem {
                    mem = arr[j];
                    mem_pos = j;
                }
                j = j + 1;
            }
            if mem_pos != i{
                arr[mem_pos] = arr[i];
                arr[i] = mem;
            }
            i = i + 1;
        }
    }
}


fn main(){
    let mut arr = vec![7,4,2,3];
    selection_sort(&mut arr);
    println!("{:?}", arr);
}
