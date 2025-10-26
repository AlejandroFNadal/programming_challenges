# We are pruning the tree by having a list of dead paths
# If a position has not worked after exploring all alternatives for it, as soon as we 
# reach the position, we consider it dead.
# Also, if a posible value to jump is not big enough to escape its area of reach, then we also dont follow it.

class Solution:
    def canJump(self, nums: List[int]) -> bool:
        useless_positions = {}
        def recurs_jump(pos):
            #print(pos)
            # if we got to the end, true
            if pos >= len(nums) - 1:
                return True
            if useless_positions.get(pos):
                return False
            # we try all posiblities
            for i in range(nums[pos], 0, -1):
                if pos+i < len(nums) - 1 and nums[pos + i] + i < nums[pos]:
                    useless_positions[pos + i] = True
                    continue
                if recurs_jump(pos + i):
                    return True
            # none of them worked, we return false
            useless_positions[pos] = True
            return False
        return recurs_jump(0)
