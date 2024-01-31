def intersect(lt1, rt1, lb1, rb1, lt2, rt2, lb2, rb2):
    return min(lt1, lt2), min(rt1, rt2), max(lb1, lb2), max(rb1, rb2)

t, d, n = map(int, input().split())
lt, rt, lb, rb = 0, 0, 0, 0
for _ in range(n):
    x, y = map(int, input().split())
    lt, rt, lb, rb = intersect(lt + t, rt + t, lb - t, rb - t, y + d - x, y + d + x, y - d + x, y - d - x)

ans = []
for y_eq_minus_x in range(lb, rt + 1):
    for y_eq_x in range(rb, lt + 1):
        y = (y_eq_minus_x + y_eq_x) / 2
        if y == y // 1:
            x = y_eq_minus_x - y
            ans += [(int(x), int(y))]

print(len(ans))
for i in ans:
    print(*i)