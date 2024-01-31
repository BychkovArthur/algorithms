a = input()
b = input()

genom_a = []
genom_b = set()

for i in range(len(a) - 1):
    genom_a += [a[i] + a[i + 1]]
for i in range(len(b) - 1):
    genom_b.add(b[i] + b[i + 1])
    
cnt = 0    
for genom in genom_a:
    if genom in genom_b:
        cnt += 1
print(cnt)
