#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'nonDivisibleSubset' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER k
#  2. INTEGER_ARRAY s
#

def generate_new_subset(original_l: list, s2_set: list, latest_subset: list):
    # we iterate over the elements of the latest_subset 
    new_s = []
    for sx_i in latest_subset:
        # we create a set because we can use it to substract the elements from the original list, avoiding repetition
        sx_i_set = set(sx_i)
        substracted_original = set(original_l) - sx_i_set
        # now, we have to check possible candidates to add to these elements.
        for original in substracted_original:
            sx_i_copy = {elem for elem in sx_i} 
            can_insert = True
            # we compare each element of the existing set with the original element to see if they are in s2
            for sx_i_j in sx_i_copy:
                if sx_i_j < original:
                    key = f"{sx_i_j}_{original}"
                else:
                    key = f"{original}_{sx_i_j}"
                if key not in s2_set:
                    can_insert = False
            if can_insert:
                sx_i_copy.add(original)
                if sx_i_copy not in new_s:
                    new_s.append(sx_i_copy)
    return new_s
def nonDivisibleSubset(k, s):
    # We generate a set of pairs that cannot be divided by k after being summed up
    s2 = []
    s2_dict = {} 
    #O(n^2) for this section
    for i in tqdm(range(0, len(s))):
        index_elem = s[i]
        for j in range(i + 1, len(s)):
            check_elem = s[j]
            if (index_elem + check_elem) % k != 0:
                if index_elem < check_elem:
                    s2_dict[f"{index_elem}_{check_elem}"] = {index_elem, check_elem}
                else:
                    s2_dict[f"{check_elem}_{index_elem}"] = {check_elem, index_elem}
                s2.append({index_elem, check_elem})
    divisible_sets = [s2]
    continue_iter = True
    # we will call the generate subset function until we get an empty array
    while continue_iter:
        new_set = generate_new_subset(s, s2_dict, divisible_sets[-1])
        if new_set == []:
            continue_iter =False  
        else:
            divisible_sets.append(new_set)
    return len(divisible_sets + 1)
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    k = int(first_multiple_input[1])

    s = list(map(int, input().rstrip().split()))

    result = nonDivisibleSubset(k, s)
    print(result)

    fptr.write(str(result) + '\n')

    fptr.close()

