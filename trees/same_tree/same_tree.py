# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        if p is None and q is not None:
            return False
        if p is not None and q is None:
            return False
        if p is None and q is None:
            return True
        if p.val != q.val:
            return False
        if self.isSameTree(p.left, q.left) is False:
            return False
        if self.isSameTree(p.right, q.right) is False:
            return False
        return True 
