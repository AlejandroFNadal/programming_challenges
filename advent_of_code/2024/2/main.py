import tqdm

f = open('input.txt', encoding='UTF-8')
reports = []
while True:
    line = f.readline()
    if not line:
        break
    reports.append([int(x) for x in line.split(',')])

safe_reports = 0


def is_increasing(items: list):
    prev = items[0]
    for i in range(1, len(items)):
        if (prev >= items[i] or (prev + 3) < items[i]):
            return False
        prev = items[i]
    return True


def is_decreasing(items: list):
    prev = items[0]
    for i in range(1, len(items)):
        if (prev <= items[i] or (prev - 3) > items[i]):
            return False
        prev = items[i]
    return True


for rep in tqdm.tqdm(reports):
    # if the previous element has not increased or increased way too fast
    if is_decreasing(rep) or is_increasing(rep):
        safe_reports += 1
    else:
        for i in range(0, len(rep)):
            new_rep = rep.copy()
            new_rep.pop(i)
            if is_decreasing(new_rep) or is_increasing(new_rep):
                safe_reports += 1
                break

print(safe_reports)
