f = open('input.txt', 'r')
mat=[]
while True:
    l = f.readline() 
    if not l:
        break
    mat.append(l)
cnt = 0

def forward_finder(i:int,j: int, mat:list):
    if j + 3 < len(mat[0]):
        if mat[i][j]== 'X' and mat[i][j + 1] == "M" and mat[i][j + 2] == "A" and mat[i][j + 3] == "S":
            return True
    return False
def backward_finder(i:int,j: int, mat:list):
    if j - 3 >= 0:
        if mat[i][j]== 'X' and mat[i][j - 1] == "M" and mat[i][j - 2] == "A" and mat[i][j - 3] == "S":
            return True
    return False
def top_finder(i:int,j: int, mat:list):
    if i - 3 >= 0:
        if mat[i][j]== 'X' and mat[i - 1][j] == "M" and mat[i - 2][j] == "A" and mat[i - 3][j] == "S":
            return True
    return False
def bottom_finder(i:int,j: int, mat:list):
    if i + 3 < len(mat):
        if mat[i][j]== 'X' and mat[i + 1][j] == "M" and mat[i + 2][j] == "A" and mat[i + 3][j] == "S":
            return True
    return False

def top_left(i:int,j: int, mat:list):
    if i - 3 >= 0 and j - 3 >= 0:
        if mat[i][j]== 'X' and mat[i - 1][j - 1] == "M" and mat[i - 2][j - 2] == "A" and mat[i - 3][j - 3] == "S":
            return True
    return False
def top_right(i:int,j: int, mat:list):
    if i - 3 >= 0 and j + 3 < len(mat[0]):
        if mat[i][j]== 'X' and mat[i - 1][j + 1] == "M" and mat[i - 2][j + 2] == "A" and mat[i - 3][j + 3] == "S":
            return True
    return False
def bottom_right(i:int,j: int, mat:list):
    if i + 3 < len(mat) and j + 3 < len(mat[0]):
        if mat[i][j]== 'X' and mat[i + 1][j + 1] == "M" and mat[i + 2][j + 2] == "A" and mat[i + 3][j + 3] == "S":
            return True
    return False
def bottom_left(i:int,j: int, mat:list):
    if i + 3 < len(mat) and j - 3 >= 0:
        if mat[i][j]== 'X' and mat[i + 1][j - 1] == "M" and mat[i + 2][j - 2] == "A" and mat[i + 3][j - 3] == "S":
            return True
    return False

def mas_finder(i:int, j:int, mat:list):
    if i + 2 < len(mat) and j + 1 < len(mat[0]):
        if mat[i][j]== 'M' and mat[i + 1][j + 1] == "A" and mat[i + 2][j + 2] == "S" and mat[i][j + 2] == "S" and mat[i + 2][j] == "M":
            return True
        if mat[i][j]== 'S' and mat[i + 1][j + 1] == "A" and mat[i + 2][j + 2] == "M" and mat[i][j + 2] == "S" and mat[i + 2][j] == "M":
            return True
        if mat[i][j]== 'M' and mat[i + 1][j + 1] == "A" and mat[i + 2][j + 2] == "S" and mat[i][j + 2] == "M" and mat[i + 2][j] == "S":
            return True
        if mat[i][j]== 'S' and mat[i + 1][j + 1] == "A" and mat[i + 2][j + 2] == "M" and mat[i][j + 2] == "M" and mat[i + 2][j] == "S":
            return True

mas = 0
for i in range(len(mat)):
    for j in range(len(mat[0])):
        if forward_finder(i, j, mat):
            cnt += 1
        if backward_finder(i, j, mat):
            cnt +=1
        if bottom_finder(i, j, mat):
            cnt += 1
        if top_finder(i, j, mat):
            cnt +=1
        if top_left(i, j, mat):
            cnt += 1
        if top_right(i,j,mat):
            cnt+= 1
        if bottom_left(i, j, mat):
            cnt += 1
        if bottom_right(i,j, mat):
            cnt += 1
        if mas_finder(i,j,mat):
            mas += 1
print(cnt)

print(mas)

