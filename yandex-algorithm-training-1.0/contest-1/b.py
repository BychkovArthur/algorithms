a = int(input())
b = int(input())
c = int(input())

key = 0
    
if 2 * max(a, b, c) < a + b + c:
    key = 1

if key:
    print('YES')
else:
    print('NO')