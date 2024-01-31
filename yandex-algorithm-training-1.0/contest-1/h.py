a = int(input())
b = int(input())
n = int(input())
m = int(input())

min_1 = (n - 1) * a + n
min_2 = (m - 1) * b + m

max_1 = (n + 1) * a + n
max_2 = (m + 1) * b + m

if min_1 > max_2 or min_2 > max_1:
    print(-1)
else:
    print(max(min_1, min_2), min(max_1, max_2))