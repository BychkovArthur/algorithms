n = int(input())
KEYS = list(map(int, input().split()))
k = int(input())
key_press = map(int, input().split())
for key in key_press:
    KEYS[key - 1] -= 1
for key in KEYS:
    if key < 0:
        print('YES')
    else:
        print('NO')
