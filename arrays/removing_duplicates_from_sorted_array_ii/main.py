class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        already_sorted_pos = 0
        curr_pos = 0
        repetition_counter = 0
        curr_elem_for_repetition_check = nums[0]
        while curr_pos < len(nums):
            while curr_pos < len(nums) and curr_elem_for_repetition_check == nums[curr_pos]:
                repetition_counter += 1
                if repetition_counter <= 2:
                    nums[already_sorted_pos] = nums[curr_pos]
                    already_sorted_pos += 1
                curr_pos += 1
            # here we are placed in a different element.
            if curr_pos < len(nums):
                curr_elem_for_repetition_check = nums[curr_pos]
                repetition_counter = 0
        return already_sorted_pos
