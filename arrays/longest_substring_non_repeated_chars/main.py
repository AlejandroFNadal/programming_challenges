def lengthOfLongestSubstring(s: str) -> int:
    """
    https://leetcode.com/problems/longest-substring-without-repeating-characters/?
    Two pointer solution
    """
    right = 0
    left = 0
    max_len = 0
    max_pos = len(s)
    char_set = set()
    while right < max_pos:
        if s[right] not in char_set:
            char_set.add(s[right])
            right += 1
            if len(char_set) > max_len:
                max_len = len(char_set)
        else:
            char_set.discard(s[left])
            left += 1
    return max_len
            
