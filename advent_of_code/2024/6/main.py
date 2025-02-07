# pylint: disable-all
f = open('input.txt')
lab = []
while True:
    li = f.readline()
    if not li:
        break
    lab.append(list(li.rstrip('\n').strip()))

print(lab)

"""
def start_finder(ii, j, mlab):
    while i < len(mlab):
        while j < len(mlab[0]):
            if lab[i][j] == "^":
                return (i, j)
            j += 1
        i += 1
    return (None, None)
"""

# i, j = start_finder(0, 0, lab)


def loop_finder(a,b,mat, cdir):
    if cdir == 'up':
        #if a >= 1 and b < len(mat[0]) - 2 and mat[a][b + 1] in ['r', '+'] and mat[a][b + 2] in ['r', '+']:
        if a >= 1 and b < len(mat[0]) - 1 and mat[a][b + 1] in ['r', '+']:
            return True
    if cdir == 'down':
        #if a < len(mat[0]) -1 and b < len(mat[0]) - 2 and mat[a][b - 1] in ['l', '+'] and mat[a][b - 2]  in ['l', '+']:
        if a < len(mat[0]) -1 and b < len(mat[0]) - 1 and mat[a][b - 1] in ['l', '+']:
            return True
    if cdir == 'left':
        #if b >= 1 and a >=2 and mat[a - 1][b] in ['t', '+'] and mat[a -2][b] in ['t', '+']:
        if b >= 1 and a >=1 and mat[a - 1][b] in ['t', '+']:
            return True
    if cdir == 'right':
        #if b < len(mat[0]) -1 and a < len(mat) - 1 and mat[a +1][b] in ['b', '+'] and mat[a + 2][b] in ['b', '+']:
        if b < len(mat[0]) -1 and a < len(mat) - 1 and mat[a +1][b] in ['b', '+']:
            return True
    return False

def path_finder():
    i = 70
    steps = 0
    j = 60
    obst = 0
    while i < len(lab) and j < len(lab[0]) and i >= 0 and j >= 0:
        # print(i,j)
        while i >= 0:
            if lab[i][j] != ".":
                lab[i][j] = "+"
            else:
                lab[i][j] = "t"
            if i != 0 and lab[i - 1][j] == '#':
                lab[i][j] = "+"
                break
            if loop_finder(i,j,lab, 'up'):
                obst += 1     
            steps += 1
            i -= 1
        if i == -1:
            return obst 
        while j < len(lab[0]):
            if lab[i][j] == ".":
                lab[i][j] = "r"
            else:
                lab[i][j] = "+"
            if j != len(lab[0]) - 1 and lab[i][j + 1] == '#':
                lab[i][j] = "+"
                break
            if loop_finder(i,j,lab, 'right'):
                obst += 1     

            j += 1
            steps += 1
        if j == len(lab[0]):
            return obst 
        while i < len(lab):
            if lab[i][j] == ".":
                lab[i][j] = "b"
            else:
                lab[i][j] = "+"
            if i != len(lab) - 1 and lab[i + 1][j] == '#':
                lab[i][j] = "+"
                break
            if loop_finder(i,j,lab, 'down'):
                obst += 1     

            i += 1
            steps += 1
        if i == len(lab):
            return obst 
        while j >= 0:
            if lab[i][j] == ".":
                lab[i][j] = "l"
            else:
                lab[i][j] = "+"
            if j != 0 and lab[i][j - 1] == '#':
                lab[i][j] = "+"
                break
            if loop_finder(i,j,lab, 'left'):
                obst += 1     
            j -= 1
            steps += 1
        if j == -1:
            return obst
    return obst


print(path_finder())
dist = 0
for r in lab:
    for c in r:
        if c == 'X':
            dist += 1








