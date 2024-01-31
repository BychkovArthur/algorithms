n = int(input())

def unite(a, b):
    return max(a[0], b[0]), min(a[1], b[1])

def get_mid(a, b):
    return a + (b - a) / 2

segment = (30, 4000)
last = float(input())

for i in range(n - 1):
    current, where = input().split()
    current = float(current)
    
    mid = get_mid(min(current, last), max(current, last))
    
    if last <= current and where == 'closer' or last >= current and where == 'further':
        segment = unite(segment, (mid, 4000))
    if last <= current and where == 'further' or last >= current and where == 'closer':
        segment = unite(segment, (30, mid))
    
    last = current

print(*segment)