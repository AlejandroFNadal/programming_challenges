def minimumSwaps(arr):
    swaps = 0
    #first we sort the array
    ordered_arr = sorted(arr)
    #now we compare the differences
    # we load all the positions in a dict
    hash_table = {}
    i=0
    for elem in arr:
        hash_table[elem] = i
        i+=1
    for i in range(0, len(arr)): # we must not reach the last element
        #we obtain the smallest element
        smallest_elem = ordered_arr[0]
        if smallest_elem < arr[i]:
            # we obtain the position of the smallest element
            pos_smallest_element = hash_table[smallest_elem]
            # we update the new position on the hash table of arr[i]
            hash_table[arr[i]] = pos_smallest_element
            # we swap, most of the time we will have to do it, it makes no sense to check, there are no repeated elements
            arr[i], arr[pos_smallest_element] = arr[pos_smallest_element], arr[i]
            swaps+=1
        # delete first element of ordered_arr
        ordered_arr.pop(0)
    return swaps

case1= "8 45 35 84 79 12 74 92 81 82 61 32 36 1 65 44 89 40 28 20 97 90 22 87 48 26 56 18 49 71 23 34 59 54 14 16 19 76 83 95 31 30 69 7 9 60 66 25 52 5 37 27 63 80 24 42 3 50 6 11 64 10 96 47 38 57 2 88 100 4 78 85 21 29 75 94 43 77 33 86 98 68 73 72 13 91 70 41 17 15 67 93 62 39 53 51 55 58 99 46"

arr_case1 = case1.split()
arr_int_case1 = [int(elem) for elem in arr_case1]
solution_case1 = 91
print(minimumSwaps(arr_int_case1))
