n, m, k = map(int, input().split())

pole = [['' for i in range(m + 1)] for i in range(n + 1)]

def valid_index(x, y):
    return 1 <= x <= n and 1 <= y <= m

def get_mines_around(x, y):
    move_x = [-1, -1, -1, 0, 0, 1, 1, 1]
    move_y = [1, 0, -1, 1, -1, 1, 0, -1]
    
    cnt = 0
    for i in range(8):
        new_x = x + move_x[i]
        new_y = y + move_y[i]
        if valid_index(new_x, new_y) and pole[new_x][new_y] == '*':
            cnt += 1
    return cnt



for i in range(k):
    x, y = map(int, input().split())
    pole[x][y] = '*'
    
for x in range(1, n + 1):
    for y in range(1, m + 1):
        if pole[x][y] != '*':
            pole[x][y] = str(get_mines_around(x, y))

for x in range(1, n + 1):
    print(*pole[x][1:])
        