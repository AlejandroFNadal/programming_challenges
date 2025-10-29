https://leetcode.com/problems/h-index/?envType=study-plan-v2&envId=top-interview-150

Possible values of h index 

For an array of 1 element:
[2]: The h-index is 1 or 0, it is 0 if it has zero citations

For an array of 2 elements:
[2, 3]: the length of the array limits the max h-index: 2 is the max. The value can never be larger than the array, and all zero values are useless.

If I have [3, 1, 6, 9, 2, 5]:

Ordering it, I get [1, 2, 3, 5, 6, 9]

I have 3 who have 5, but I need 5 who have 5
I have 4 that have 3: 3 is the h index.
