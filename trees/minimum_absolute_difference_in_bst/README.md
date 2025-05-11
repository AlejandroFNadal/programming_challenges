# Minimum Absolute difference in a BST

## Dumbest-easy approach

Traverse all numbers, put them on a list, and then calculate the minimum absolute difference between all of them:

```
def traverseTree(node: Optional[TreeNode], listN: [int]):
    if node.left:
        traverseTree(node.left, listN)
    if node.right:
        traverseTree(node.right, listN)
    listN.append(node.val) 


class Solution:
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        numberList = []
        traverseTree(root, numberList)
        minDiff = None
        for index, val in enumerate(numberList):
            for sec_index, sec_val in enumerate(numberList):
                if sec_index == index:
                    continue
                diff = abs(sec_val-val)
                if minDiff is None or diff < minDiff :
                    minDiff = diff 
        return minDiff
```
## Less simple

Given the properties of a BST, the element which will be closest to it in value is going to be the closest to it horizontally on the very bottom of the tree. 
To reach it, we first go one to the left, and then all the way down to the right. Then, we repeat this but inverted, one right, and then all the way down to the left.

```
def closestValue(node: Optional[TreeNode]):
    leftTempNode = None
    rightTempNode = None
    diff = None
    if node.left:
        leftTempNode = node.left
        while leftTempNode.right is not None:
            leftTempNode = leftTempNode.right 
        diff = abs(leftTempNode.val - node.val)
    if node.right is not None:
        rightTempNode = node.right 
        while rightTempNode.left is not None:
            rightTempNode = rightTempNode.left
        if diff is None or diff > abs(rightTempNode.val - node.val):
            diff = abs(rightTempNode.val - node.val)
    return diff 

def traverseTree(node: Optional[TreeNode], diffObj: [int]):
    curr_diff = closestValue(node)
    if curr_diff is not None and (diffObj[0] is None or curr_diff < diffObj[0]):
        diffObj[0] = curr_diff
    if node.left:
        traverseTree(node.left, diffObj)
    if node.right:
        traverseTree(node.right, diffObj)

class Solution:
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        diffObj = [None] 
        traverseTree(root, diffObj)
        return diffObj[0] 
        
```

## Best approach

Use the in-order traversal of a BST. In that way, you get a sorted list, which means finding the difference is extremely easy.

```
def processNode(node, diffObj: [int, int]):
    if diffObj[1] is not None and diffObj[0] is None:
        # first difference
        diffObj[0] = abs(diffObj[1] - node.val)
    elif diffObj[1] is not None:
        if diffObj[0] > abs(diffObj[1] - node.val):
            diffObj[0] = abs(diffObj[1] - node.val)
    diffObj[1] = node.val

def traverseInOrder(node, diffObj: [int, int]):
    if node.left:
        traverseInOrder(node.left, diffObj)
    processNode(node, diffObj)
    if node.right:
        traverseInOrder(node.right, diffObj)
    return diffObj[0]

class Solution:
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        # diff, lastval
        diffObj = [None, None] 
        traverseInOrder(root, diffObj)
        return diffObj[0] 
        
```

