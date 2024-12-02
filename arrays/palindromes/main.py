def is_palindrome(txt: str) -> bool:
    """
    Basic palindrome detection with two pointer approach.
    https://leetcode.com/problems/valid-palindrome/
    """
    start = 0
    end = len(txt) - 1
    while start < end:
        if txt[start].isalnum() is False:
            start += 1
            continue
        if txt[end].isalnum() is False:
            end -= 1
            continue
        if txt[start].lower() != txt[end].lower():
            return False
        start += 1
        end -= 1
    return True
