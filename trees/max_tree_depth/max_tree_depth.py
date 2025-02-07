# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        ext_max_depth = 0
        def deep_path(node:Optional[TreeNode], depth:int, ext_max_depth):
            if node is None:
                return ext_max_depth
            if ext_max_depth < depth:
                ext_max_depth = depth
            val = deep_path(node.left, depth + 1, ext_max_depth)
            if val > ext_max_depth:
                ext_max_depth = val
            val = deep_path(node.right, depth + 1, ext_max_depth)
            if val > ext_max_depth:
                ext_max_depth = val
            return ext_max_depth
        return deep_path(root, 1, ext_max_depth)
        
