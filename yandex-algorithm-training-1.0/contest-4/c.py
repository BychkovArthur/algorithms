f = open('input.txt', 'r')
dct = {}
for line in f:
    for word in line.split():
        if word in dct:
            dct[word] += 1
        else:
            dct[word] = 1
mx = max(dct.values())
for key in sorted(dct.keys()):
    if dct[key] == mx:
        print(key)
        break
    
f.close()