import math

def isValidSudoku(board: List[List[str]]) -> bool:
    """
    https://leetcode.com/problems/valid-sudoku

    """
    cols_set = [set() for _ in range(9)]
    rows_set = [set() for _ in range(9)]
    small_squares = [set() for i in range(9)]
    for i in range(9):
        for j in range(9):
            elem = board[i][j]
            if elem == ".":
                continue
            if elem in cols_set[j]:
                return False
            cols_set[j].add(elem)
            if elem in rows_set[i]:
                return False
            rows_set[i].add(elem)
            # this part was fun, then I saw that other people just used // instead of floor.
            square = math.floor(i / 3) * 3 + math.floor(j / 3)
            if elem in small_squares[square]:
                return False
            small_squares[square].add(elem)
    return True
