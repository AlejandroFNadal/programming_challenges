//
//https://leetcode.com/problems/remove-element
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // stupid approach: copy all elements that are not val to
        // another array, and rewrite the array. Time: 2n. Memory: 2n
        vector<int> temp_array;
        vector<int>::iterator iter = nums.begin();

        for(iter; iter < nums.end(); iter++){
            if(*iter != val){
                temp_array.push_back(*iter);
            }
        }
        vector<int>::iterator temp_iter = temp_array.begin();
        iter = nums.begin();
        for(iter, temp_iter; temp_iter < temp_array.end(); iter++,temp_iter++){
            *iter = *temp_iter;
        }
        int k = temp_array.size();
        return k;
        // better: traverse the array from left to right, every time 
        // there is a val element, we swap the element at the end if it is not a val
        // every time we swap, we move this marker and check if the marker is a val.
        // the left checker should stop at the marker, and the size of the array - the right marker should be the return element
    }
};
