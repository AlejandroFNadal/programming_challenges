from statistics import mean

class Solution:
    # averages will contain list containing all the elements of each level
    def rec(self, root, averages: [], level: int):
        if root is None:
            return None
        if root.val is None:
            return None
        if len(averages) == level:
            averages.append([root.val])
        elif len(averages) > level:
            averages[level].append(root.val)
        else:
            raise Exception("Should not happen")
        self.rec(root.left, averages, level + 1)
        self.rec(root.right, averages, level + 1)
        
    def averageOfLevels(self, root: Optional[TreeNode]) -> List[float]:
        averages = []
        self.rec(root, averages, 0)
        final_averages = []
        print(averages)
        for elem in averages:
            final_averages.append(mean(elem))
        return final_averages
