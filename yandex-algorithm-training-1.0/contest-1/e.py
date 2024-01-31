import math
k1, m, k2, p2, n2 = map(int, input().split())

key = 0
ans = [ -1, -1]

for flats_per_floor in range(1, 10 ** 6 + 1):
    floor_2 = (p2 - 1) * m + n2
    
    if flats_per_floor * (floor_2 - 1) < k2 <= flats_per_floor * floor_2:
        floor_1 = math.ceil(k1 / flats_per_floor)
        p1_curr = math.ceil(floor_1 / m)
        n1_curr = floor_1 % m
        if n1_curr == 0:
            n1_curr = m
            
        if ans[0] == -1 and ans[1] == -1:
            ans[0] = p1_curr
            ans[1] = n1_curr
        else:
            if p1_curr != ans[0]:
                ans[0] = 0
            if n1_curr != ans[1]:
                ans[1] = 0
if n2 > m:
    print(-1, -1)
else:
    print(*ans)
# if len(p1) == 0 or len(n1) == 0 or n2 > m:
#     print('-1 -1')
# elif len(p1) == 1 and len(n1) > 1:
#     print(list(p1)[0], 0, sep=' ')
# elif len(p1) > 1 and len(n1) == 1:
#     print(0, list(n1)[0], sep=' ')
# elif len(p1) > 1 and len(n1) > 1:
#     print(0, 0)
# else:
#     print(list(p1)[0], list(n1)[0], sep=' ')
    
