//
//https://leetcode.com/problems/remove-element
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // there is a val element, we swap the element at the end if it is not a val
        // every time we swap, we move this marker and check if the marker is a val.
        // the left checker should stop at the marker, and the size of the array - the right marker should be the return element
        vector<int>::iterator iter_left;
        vector<int>::iterator iter_right;
        iter_left = nums.begin();
        iter_right = nums.end() -1;
        int swap_var = 0;
        while(iter_left <= iter_right){
            // if the left is val, we try to move 
            if(*iter_left == val){
                // if right is not val, we can swap them
                if(*iter_right != val){
                    swap_var = *iter_left; 
                    *iter_left = *iter_right;
                    *iter_right = swap_var;
                    iter_left++;
                    iter_right--;
                    // if the right is val, we have to look for another value to swap
                } else{
                    iter_right--;
                }
            } else{ // if the left pointer is not val, we can just skip it.
                iter_left++;
            }
        }
        int k = iter_left - nums.begin();
        return k;
    }
};
int main(){
    Solution obj1;
    int val1 = 2;
    vector<int> vec1 = {2,2,2,2,2,2,2};
    int val2 = 2;
    vector<int> vec2 = {1,2,3,4,5,6,7,8};
    copy(vec1.begin(), vec1.end(), ostream_iterator<int>(cout, " "));
    cout << " " << endl;
    vector<int> vec1_sol = {2,2,2,2,2,2,2};
    assert (obj1.removeElement(vec1, val1) == 0);
    vector<int> vec2_sol = {1,3,4,5,6,7,8,2};
    assert (obj1.removeElement(vec2, val2) == 7);
    copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
    cout << " " << endl;
    vector<int> vec3 = {2,1,2,3,2,5,2,2,2};
    assert (obj1.removeElement(vec3, 2) == 3);
    copy(vec3.begin(), vec3.end(), ostream_iterator<int>(cout, " "));
    cout << " " << endl;
    vector<int> vec4 = {3,2,2,3};
    assert (obj1.removeElement(vec4, 2) == 2);
    copy(vec4.begin(), vec4.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
