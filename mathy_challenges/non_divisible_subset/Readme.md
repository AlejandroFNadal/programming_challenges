Challenge: https://www.hackerrank.com/challenges/non-divisible-subset/problem

In this problem, we have to find the maximum size subset of a given set, that given a integer K, all possible sums of pairs of the subset 
(star operation on the subset) cannot be evenly divided by K.

In "firstAttempt.py" you will see a algorithmic solution. Finding all possible sets of pairs that cannot be divided using two nested for loops (n^2)
and then using a dictionary to store them, as then later these are used to check what values can be added to bigger sets.

The complexity of this solution is O(n^4) and as such, it is a bit terrible.

The secondAttempt.py approach required a lot more online reading on the math theory used to solve these kind of problem. Part of the math is explained in this article: https://medium.com/@mrunankmistry52/non-divisible-subset-problem-comprehensive-explanation-c878a752f057 . I only used the math and not the solution from this person, but afterwards I checked and the solutions are practically identical.

This solution is O(n). The idea is as follows:

Given two numbers A and B, natural numbers, if the sum of those numbers is evenly divisible by K, the sum of their modulo against K would also be equal to K or it will be equal to 0.

We can express this as:

$$\forall A,B,K,p,q \in \mathbb{Z} , p = (A mod K) \land q= (B mod K) \land \frac{A+B}{K}\in\mathbb{Z})\Rightarrow p + q = K \lor p+q = 0$$

We need to count how many combinations of values we can make that will not result in a sum divisible by K. If we have K as a divisor, then the modulo can be from o to K -1. We count how many elements of the set fall in each possible modulo result. Then, we know that the sum of the combinations of certain sets will not work, this is, where p + q = K. So for these combinations, we count only one of the sets. If we express the p+q = K as p = K -q, we realize that p needs to grow from 1 and q needs to decrease from K:

E.g: K = 5

p = 1, q = 4
p = 2, q = 3

The combinations of those sets are not valid, so we sum only the bigger of each set.
So, if you have 4 numbers that fit in the set of modulo 2 and 5 numbers that fit in the set of modulo 3, you would only use the set of modulo 3, as you cannot use both.

There are two special cases: if p + q = 0, it means that the sum of the elements of this set (set of modulo 0) are also divisible by K. Then, you cannot put them all in the final result and you can only use one of them. The same thing occurs if p = q. 

The input.txt files can be used to test the algos and they are part of the Hackerrank test cases. The input7.txt will crash the first attempt because the
first algo was too ineficient.

