def get_manhattan_distance(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

def get_dots(x, y, distance, st):
    for dist_now in range(distance + 1):
        for curr in range(dist_now + 1):
            st.add((x + curr, y + (dist_now - curr)))
            st.add((x + curr, y - (dist_now - curr)))
            st.add((x - curr, y + (dist_now - curr)))
            st.add((x - curr, y - (dist_now - curr)))
        
# t, d, n = map(int, input().split())


def slow(t, d, n, data):
    
    ans = [0, []]
    where_can_be = set()
    where_can_be.add((0, 0))

    for i in data:
        x, y = i
        new = set()
        for elem in where_can_be:
            get_dots(elem[0], elem[1], t, new)
        new_2 = set()
        get_dots(x, y, d, new_2)
        where_can_be = new & new_2

    ans[0] = len(where_can_be)
    for i in where_can_be:
        ans[1] += [i]
    return ans

def fast(t, d, n, data):
    
    ans = [0, []]
    where_can_be = set()
    where_can_be.add((0, 0))

    for i in data:
        x, y = i
        new = set()
        
        nearest = (1e9, 1e9)
        for dot in where_can_be:
            if get_manhattan_distance(dot[0], dot[1], x, y) < get_manhattan_distance(nearest[0], nearest[1], x, y):
                nearest = dot
        
        for dot in where_can_be:
            if get_manhattan_distance(dot[0], dot[1], x, y) == get_manhattan_distance(nearest[0], nearest[1], x, y):
                get_dots(dot[0], dot[1], t, new)            
        
        new_2 = set()
        get_dots(x, y, d, new_2)
        where_can_be = new & new_2

    ans[0] = len(where_can_be)
    for i in where_can_be:
        ans[1] += [i]
    return ans

def checker():
    import random
    cnt = 0
    while True:
        t, d, n = random.randint(1, 10), random.randint(1, 10), random.randint(1, 5)
        data = []
        for i in range(n):
            a, b = random.randint(-10, 10), random.randint(-10, 10)
            data += [(a, b)]
        cnt += 1
        if slow(t, d, n, data) == fast(t, d, n, data):
            
            print(f'Test {cnt} passed, t:{t} d:{d} n:{n}')
            print(*data)
            print()
        else:
            print(f'Test {cnt} ERROR, t:{t} d:{d} n:{n}')
            print(*data)
            print('slow:' ,slow(t, d, n, data))
            print('fast:' ,fast(t, d, n, data))
            
            print()
            break



checker()