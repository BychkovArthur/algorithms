n, m = map(int, input().split())
anya = set()
borya = set()

for i in range(n):
    anya.add(int(input()))
for i in range(m):
    borya.add(int(input()))

both = []
a1 = []
b1 = []
for el in anya:
    if el in borya:
        both += [el]
    else:
        a1 += [el]

for el in borya:
    if el not in anya:
        b1 += [el]

print(len(both))
print(*sorted(both))
    
print(len(a1))
print(*sorted(a1))

    
print(len(b1))
print(*sorted(b1))
