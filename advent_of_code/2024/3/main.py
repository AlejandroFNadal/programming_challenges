# grep "mul([0-9]\+,[0-9]\+)" input.txt -o > filtered.txt
# just applied previous regex and then deleted the extra things with vim
f = open('filtered.txt')
lines = []
while True:
  l = f.readline()
  if not l:
    break
  lines.append(l)

res = 0
for l in lines:
    res += int(l.split(",")[0]) * int(l.split(",")[1]) 

print(res)

# second part, new regex
# grep "mul([0-9]\+,[0-9]\+)\|do()\|don't()" input.txt -o > filtered2.txt
f = open('filtered2.txt')
lines = []
while True:
  l = f.readline()
  if not l:
    break
  lines.append(l)

res = 0
enabled = True
for l in lines:
    if l == "don't()\n":
        enabled = False
        continue
    if l == "do()\n":
        enabled = True
        continue
    if enabled:
        res += int(l.split(",")[0]) * int(l[:-2].split(",")[1]) 

print(res)
