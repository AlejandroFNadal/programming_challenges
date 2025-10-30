class Solution:
    def romanToInt(self, s: str) -> int:
        res = 0
        equiv = {
            'I':1,
            'V':5,
            'X':10,
            'L':50,
            'C': 100,
            'D': 500,
            'M': 1000
        }
        prev=s[0]
        for i in range(1, len(s)):
            curr = s[i]
            if equiv[curr] > equiv[prev]:
                res -= equiv[prev]
            else:
                res += equiv[prev]
            prev=s[i]
        return res + equiv[prev]
