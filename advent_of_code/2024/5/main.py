from collections import defaultdict

f = open('input.txt')
rules = []
while True:
    line = f.readline()
    if line == "\n":
        break
    rules.append(line.rstrip("\n"))
#print(rules)
pages_list = []

while True:
    line = f.readline()
    if not line:
        break
    pages_list.append(line.rstrip("\n").split(','))
#print(pages)

previous_forbidden = defaultdict(list) 
next_forbidden = defaultdict(list)
for r in rules:
    a,b = r.split("|")
    previous_forbidden[a].append(b)
    next_forbidden[b].append(a)
#print(previous_forbidden)
#print(next_forbidden)

ignore_list = []
for x,pages in enumerate(pages_list):
    for i in range(len(pages)):
        curr_page = pages[i]
        for j in range(i + 1, len(curr_page)):
            if pages[j] in next_forbidden[curr_page]:
                ignore_list.append(x)
        for j in range(i, -1, -1):
            if pages[j] in previous_forbidden[curr_page]:
                ignore_list.append(x)
ignore_list = list(set(ignore_list))
print(ignore_list)

center_sum = 0
corrected_sum = 0
for x, pages in enumerate(pages_list):
    if x in ignore_list:
        for i in range(len(pages)):
            curr_page = pages
            for j in range(i + 1, len(curr_page)):
                if pages[j] in next_forbidden[curr_page[i]]:
                    curr_page[i], curr_page[j] = curr_page[j], curr_page[i]
            for j in range(i, -1, -1):
                if pages[j] in previous_forbidden[curr_page[i]]:
                    curr_page[i], curr_page[j] = curr_page[j], curr_page[i]
        corrected_sum += int(pages[len(pages)//2])
    else:
        center_sum += int(pages[len(pages)//2])

print(center_sum)
print(corrected_sum)





