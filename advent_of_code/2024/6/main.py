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


def path_finder():
    i = 70
    steps = 0
    j = 60
    while i < len(lab) and j < len(lab[0]) and i >= 0 and j >= 0:
        # print(i,j)
        while i >= 0:
            lab[i][j] = "X"
            if i != 0 and lab[i - 1][j] == '#':
                break
            steps += 1
            i -= 1
        if i == -1:
            return steps
        while j < len(lab[0]):
            lab[i][j] = "X"
            if j != len(lab[0]) - 1 and lab[i][j + 1] == '#':
                break
            j += 1
            steps += 1
        if j == len(lab[0]):
            return steps
        while i < len(lab):
            lab[i][j] = "X"
            if i != len(lab) - 1 and lab[i + 1][j] == '#':
                break
            i += 1
            steps += 1
        if i == len(lab):
            return steps
        while j >= 0:
            lab[i][j] = 'X'
            if j != 0 and lab[i][j - 1] == '#':
                break
            j -= 1
            steps += 1
        if j == -1:
            return steps
    return steps


print(path_finder())
dist = 0
for r in lab:
    for c in r:
        if c == 'X':
            dist += 1
print(dist)








