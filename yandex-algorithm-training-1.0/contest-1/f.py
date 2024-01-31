def get_sides(x1, y1, x2, y2):
    return x1 + x2, max(y1, y2)

x1, y1, x2, y2 = map(int, input().split())

t1 = get_sides(x1, y1, x2, y2)
t2 = get_sides(y1, x1, y2, x2)
t3 = get_sides(y1, x1, x2, y2)
t4 = get_sides(x1, y1, y2, x2)

print(*min(t1, t2, t3, t4, key=lambda x: x[0] * x[1]))