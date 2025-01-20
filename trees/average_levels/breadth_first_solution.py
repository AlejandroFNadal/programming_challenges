class Solution:
    # averages will contain list containing all the elements of each level
    def averageOfLevels(self, root: Optional[TreeNode]) -> List[float]:
        my_queue = [root]
        averages = []
        while len(my_queue) > 0:
            nodes_in_level = len(my_queue)
            level_averages = 0
            for _ in range(0, nodes_in_level):
                node = my_queue.pop(0)
                level_averages += node.val
                if node.left:
                    my_queue.append(node.left)
                if node.right:
                    my_queue.append(node.right)
            averages.append(level_averages / nodes_in_level)
        return averages
