Link: https://www.hackerrank.com/challenges/minimum-swaps-2/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays

Goal: find the minimum amount of swaps required to order an array of numbers

It was not possible just to sort with a for loop inside another, it took too much time for a few of the cases. So I presort the array and use it to have the smallest value with a 
time complexity of O(1) and then I keep the position of every element using a hash_table, that will have an access time of O(1) in the average case. Thus the whole function is 
now below n^2 time complexity. My guess is around 3*n*log(n), if we follow this: https://wiki.python.org/moin/TimeComplexity
