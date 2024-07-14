def absolute_sorting(array):
    return sorted(array, key=abs)

def minimum_absolute_difference(array):
    ordered_arr = absolute_sorting(array)
    print(ordered_arr)
    # we start with the first possible difference
    min_dif = abs(ordered_arr[1]-ordered_arr[0])
    for i in range(0, len(ordered_arr)-1):
        diff = abs(ordered_arr[i] - ordered_arr[i+1])
        if diff < min_dif:
            min_dif = diff
    return min_diff

case1 = [3,-7,0]
solution1 = 3

print(minimum_absolute_difference(case1))
    
