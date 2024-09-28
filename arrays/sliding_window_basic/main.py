class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        if sum(nums) < target:
            return 0
        left = 0
        right = 0 
        max_sum = 0
        min_len = len(nums)
        curr_len = 0
        size_arr = len(nums)
        while right < size_arr:
            while max_sum < target and right < size_arr:
                max_sum += nums[right]
                right += 1
                curr_len += 1
                if max_sum >= target:
                    if min_len > curr_len:
                        min_len = curr_len
            while max_sum >= target and left < size_arr:
                max_sum -= nums[left]
                left += 1
                curr_len -= 1
                if max_sum >= target:
                    if min_len > curr_len:
                        min_len = curr_len
        return min_len


