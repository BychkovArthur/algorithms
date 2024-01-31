n = int(input())
turtles = set()
for i in range(n):
    a, b = map(int, input().split())
    
    if a < 0 or b < 0:
        continue
    
    if a + b != n - 1:
        continue
    
    turtles.add(a)
    
print(len(turtles))