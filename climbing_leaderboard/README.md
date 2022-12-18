Hackerrack challenge located at:
https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem?isFullScreen=true

My solution implies:
When I receive the array with the current values, I add them to another array that contains an object for every element of the array, also containing its rank
This allows me to not need to calculate the ranks every time

Then I apply binary search with a few minor optimizations that make sense only for this problem
