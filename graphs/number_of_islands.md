# Link

<https://leetcode.com/problems/number-of-islands/description/?envType=study-plan-v2&envId=top-interview-150>

 An island is a set of 1 elements in a matrix connected horizontally or vertically. 

The goal is to find the amount of islands


# First approach

Traverse the whole matrix. Whenever a one is found, a recursive approach is done in which we traverse in all possible directions finding ones. the elements get added to a list of positions which already belong to the island so as to limit the search.

Whenever we finish going through the island, we continue on the furthest element outside the island in a normal matrix traversal

```

class Solution:
    def islandFinder(self, grid: List[List[str]], x, y, islands):
        if grid[y][x] == '0':
            return
        if f"{y}_{x}" in islands:
            return
        islands[f"{y}_{x}"] = 1 
        if x < len(grid[0]) - 1:
            self.islandFinder(grid, x + 1, y, islands)
        if y < len(grid) - 1:
            self.islandFinder(grid, x, y+1, islands)
        if y > 0:
            self.islandFinder(grid, x,  y-1,islands)
        if x > 0:
            self.islandFinder(grid, x-1, y, islands)
    
    
    def numIslands(self, grid: List[List[str]]) -> int:
        islands = {} # y_x
        islandCounter = 0
        for y in range(len(grid)):
            for x in range(len(grid[0])):
                if grid[y][x] == "1":
                    if f"{y}_{x}" not in islands:
                        self.islandFinder(grid, x, y, islands)
                        islandCounter +=1        
        return islandCounter
```

