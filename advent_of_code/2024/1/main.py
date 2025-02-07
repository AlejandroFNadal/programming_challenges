f = open('input.txt', encoding='UTF-8')
list_a = []
list_b = []
while True:
    line = f.readline()
    if not line:
        break
    a,b = line.split(',')
    a,b = int(a), int(b)
    list_a.append(a)
    list_b.append(b)

list_a.sort()
list_b.sort()
diff = 0
for i in range(len(list_a)):
    diff += abs(list_a[i] - list_b[i])

print(diff)

similar = 0
for el in list_a:
    similar += el * list_b.count(el)

print(similar)
