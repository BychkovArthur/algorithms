f = open('input.txt', 'r')
dct = {}

for line in f:
    for word in line.split():
        if word not in dct:
            print(0, end=' ')
            dct[word] = 1
        else:
            print(dct[word], end=' ')
            dct[word] += 1
print()      
    
f.close()