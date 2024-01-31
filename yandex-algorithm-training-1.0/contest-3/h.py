n = int(input())

min_x = set()

for i in range(n):
    x, y = map(int, input().split())
    min_x.add(x)
print(len(min_x))