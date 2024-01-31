n = int(input().strip())
preffix_up = [0] * n
preffix_down = [0] * n
previous_y = -1
for i in range(n):
    x, y = map(int, input().strip().split())
    if previous_y == -1:
        previous_y = y
    else:
        diff = y - previous_y
        if diff > 0:
            preffix_up[i] = preffix_up[i - 1] + diff
            preffix_down[i] = preffix_down[i - 1]
        else:
            preffix_down[i] = preffix_down[i - 1] - diff
            preffix_up[i] = preffix_up[i - 1]
        previous_y = y

m = int(input().strip())
for i in range(m):
    s, f = map(int, input().strip().split())
    s -= 1
    f -= 1
    if s <= f:
        print(preffix_up[f] - preffix_up[s])
    else:
        print(preffix_down[s] - preffix_down[f])