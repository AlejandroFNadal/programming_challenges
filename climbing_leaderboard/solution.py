#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'climbingLeaderboard' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER_ARRAY ranked
#  2. INTEGER_ARRAY player
#
def embed_ranked_in_point_structure(ranked):
    really_ranked = []
    current_rank = 1
    current_elem = ranked[0]
    for elem in ranked:
        new_elem = {}
        new_elem['val']=elem
        if elem != current_elem:
            current_rank += 1
        new_elem['rank'] = current_rank
        really_ranked.append(new_elem)
        current_elem = elem
    print(really_ranked)
    return really_ranked

        
def dicotomic_search(r_ranked: list, val: int, left_index: int, right_index: int):
    left_val = r_ranked[left_index]['val']
    right_val = r_ranked[right_index]['val']
    mid_index = left_index + math.floor((right_index - left_index)/2)
    mid_val = r_ranked[mid_index]['val']
    if val > left_val:
        # we dont even bother, the result will be one
        print('val > left_val')
        return 1
    
    elif val < right_val:
        print('val > right_val')
        # the result will be one smaller than the smallest rankning
        return r_ranked[-1]['rank'] +1
    elif val == mid_val:
        print('val == mid_Val')
        # once again, we can stop here, just give it the same ranking as current
        return r_ranked[mid_index]['rank']
    elif mid_index == left_index or mid_index == right_index:
        # there is no element like val in ranked. We have to check whether it should get a higher or lower score than whatever is in midindex
        print('mid index == extremes')
        mid_val_rank = r_ranked[mid_index]['rank']
        print(f'midval_rank {mid_val_rank}')
        if val < mid_val:
            print('mid index == extremes and val < mid_val')
            return mid_val_rank +1
        else:
            print('mid index == extremes and val > mid_val')
            return mid_val_rank -1
    elif val < mid_val:
        # we move the left to the middle
        left_index = mid_index
        print('val < mid_val')
        return dicotomic_search(r_ranked, val, left_index, right_index)
    elif val > mid_val:
        # val is higher than midval
        right_index = mid_index
        print('val > mid_val')
        return dicotomic_search(r_ranked, val, left_index, right_index)
        
        
            
def climbingLeaderboard(ranked, player):
    # Write your code here
    new_ranked = embed_ranked_in_point_structure(ranked)
    result = []
    right_index = len(ranked) -1
    for elem in player:
       result.append(dicotomic_search(new_ranked, elem, 0, right_index)) 
    return result
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    ranked_count = int(input().strip())

    ranked = list(map(int, input().rstrip().split()))

    player_count = int(input().strip())

    player = list(map(int, input().rstrip().split()))

    result = climbingLeaderboard(ranked, player)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()

