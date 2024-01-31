from collections import defaultdict
n = int(input().strip())
dots = [((a:= list(map(int, input().strip().split())))[0], a[1]) for _ in range(n)]
ans = 0
for first in dots:
    distances = defaultdict(set)
    for second in dots:
        if first == second:
            continue
        x1, y1 = first
        x2, y2 = second
        dst = (x1 - x2) ** 2 + (y1 - y2) ** 2
        distances[dst].add((x2 - x1, y2 - y2))
    print(distances)
    for dst in distances:
        print(dst)
        ans += len(distances[dst]) - 1
        print(len(distances[dst]))
print(ans)
    