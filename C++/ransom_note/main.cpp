//https://leetcode.com/problems/ransom-note/
#include <cassert>
#include <iostream>
#include <string>
#include <map>
class Solution {
public:
    bool canCosntruct(std::string ransomNote, std::string magazine){
        std::map<char, int> magazineDict;

        // for every element in magazine, we will either insert if it is not in the dict
        // or count it up if it is
        for(auto it = magazine.begin(); it != magazine.end(); it++){
            if(magazineDict.find(*it) != magazineDict.end()){
                magazineDict[*it]++;
            } else {
                magazineDict[*it] = 1;
            }
        }
        for(auto it = ransomNote.begin(); it != ransomNote.end(); it++){
            if(magazineDict.find(*it) != magazineDict.end()){
                magazineDict[*it]--;
                if(magazineDict[*it] == -1){
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

};

int main(){
    Solution obj;
    std::string magazine = "AABBCCDDEEFF";
    std::string ransomNote = "ABCDEF";
    std::string ransomNote2 = "ABBBCD";
    assert(true == obj.canCosntruct(ransomNote, magazine));
    assert(false == obj.canCosntruct(ransomNote2, magazine));
    return 0;
}
