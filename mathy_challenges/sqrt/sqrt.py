from math import floor
def find_root(target, left, right):
    temp = floor((left + right)/ 2)
    test_val = temp * temp
    if test_val <= target and (temp + 1) * (temp +1) > target:
        return temp
    else:
        if test_val < target:
            left = temp
        else:
            right = temp
        return find_root(target, left, right)

class Solution:
    def mySqrt(self, x: int) -> int:
        return find_root(x, 1, x)
        
