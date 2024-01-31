import sys
dct = {}
for line in sys.stdin:
    name, item, count = line.split()
    count = int(count)
    if name not in dct:
        dct[name] = {item : count}
    else:
        if item in dct[name]:
            dct[name][item] += count
        else:
            dct[name][item] = count
    
# print(dct)
for person in sorted(dct.keys()):
    print(f'{person}:')
    for item in sorted(dct[person]):
        print(f'{item} {dct[person][item]}')