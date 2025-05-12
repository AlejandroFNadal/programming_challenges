from collections import deque

test_array1=[[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
test_array2=[[-1,-1,-1],[-1,9,8],[-1,8,9]]
test_array3 = [[1,1,-1],[1,1,1],[-1,1,1]]


def jump(row, col, amount, width, jumps_so_far) -> tuple[int , int, int]:
    """ Returns -1, -1 when the target is reached."""
    ends_right = width % 2 != 0 # odd size matrices end on the top right side
    jumps_so_far += 1
    print(f"Ends right is {ends_right}")
    while amount > 0:
        print(f"r:{row} c:{col}")
        # we move right in even rows if the end is on the right side of the matrix. If the end is on the left, we move right on odd rows.
        go_right = (row % 2 == 0 and ends_right) or (row % 2 != 0 and ends_right == False)
        if go_right and col < (width - 1):
            col += 1
        elif go_right and  col == (width - 1): # we do not consider the case here of being on the top here because that is where you win
            row -= 1
        elif go_right == False and col != 0:
            col -= 1
        elif go_right == False and col == 0:
            row -= 1
        else:
            raise Exception("Must never happen")
        if ends_right and row == 0 and col == (width - 1):
            return (-1, -1, jumps_so_far)
        if ends_right == False and row == 0 and col == 0:
            return (-1, -1, jumps_so_far)
        amount -= 1
    return (row, col, jumps_so_far)

    
def traversal(array):
    size_mat = len(array)
    operations = deque([])
    for i in range(1, 7):
        operations.append((size_mat - 1, 0, i, size_mat, 0))
    while len(operations) != 0:
        print(operations)
        curr_jump = operations.popleft() 
        print(curr_jump)
        new_row, new_col, jumps_so_far = jump(*curr_jump)
        if new_row == -1:
            return jumps_so_far
        value_in_array = array[new_row][new_col]
        if value_in_array != -1:
            print(f"Jump to {value_in_array}")
            new_row, new_col, _ = jump(size_mat - 1, 0, value_in_array - 1, size_mat, 0)
            if new_row == -1:
                return jumps_so_far
        # kill loops
        if new_row != curr_jump[0] or new_col != curr_jump[1]:
            for i in range(1, 7):
                jump_to = (new_row, new_col, i, size_mat, jumps_so_far)
                operations.append(jump_to)
    return -1

assert(traversal(test_array1) == 4)
assert(traversal(test_array2) == 1)
assert(traversal(test_array3) == -1) 

