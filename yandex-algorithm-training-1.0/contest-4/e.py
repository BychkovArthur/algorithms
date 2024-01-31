n = int(input())
ht = {}
for i in range(n):
    w, h = map(int, input().split())
    if w not in ht:
        ht[w] = h
    else:
        ht[w] = max(ht[w], h)
sm = 0
for key in ht:
    sm += ht[key]
print(sm)