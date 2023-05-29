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


def nonDivisibleSubset(k, s):
    # for an operation a % m = p, p belongs to [0..m)
    remainders = [0]* k
    # we calculate all modulo results and sum the amount of instances for each possible result
    for elem in s:
        modulo = elem % k
        remainders[modulo] +=1
    # special case: p -q = 0. These values, when summed, are divisible by K and thus only one of them can belong to the final set. It could also be empty
    p_q_0 = min(1, remainders[0])
    # second special case, p = q. Same scenario as p-q = 0
    p_q_equal = 0
    if k % 2 == 0: # if k is even
        pivot = k/2
        p_q_equal = min(remainders[pivot], 1)
    # normal scenario. We increase the value of p and reduce the value of q. These sets, when all their possible combinations are summed up, all result in
    # numbers divisible by K, and thus only one of those sets can be used. We will use the biggest one.
    other_p_q = 0
    for i in range(1,math.ceil(k/2)):
       other_p_q += max(remainders[i], remainders[k-i]) 
    # the final result is the sum of these three possibilities. All these sets, the combinations summed together, do not fall under the case of p = k -q and thus
    # can be added safely to the final set
    result = p_q_0 + other_p_q + p_q_equal
    return result
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    k = int(first_multiple_input[1])

    s = list(map(int, input().rstrip().split()))

    result = nonDivisibleSubset(k, s)

    fptr.write(str(result) + '\n')

    fptr.close()

