
def emergency(k1, m, k2, p2, n2):
    import math
    p1 = set()
    n1 = set()
    key = 0

    for flats_per_floor in range(1, 10 ** 6 + 1):
        floor_2 = (p2 - 1) * m + n2
        
        if flats_per_floor * (floor_2 - 1) < k2 <= flats_per_floor * floor_2:
            floor_1 = math.ceil(k1 / flats_per_floor)
            p1.add(math.ceil(floor_1 / m))
            n1_curr = floor_1 % m
            if n1_curr != 0:
                n1.add(n1_curr)
            else:
                n1.add(m)

    if len(p1) == 0 or len(n1) == 0 or n2 > m:
        return [-1, -1]
    elif len(p1) == 1 and len(n1) > 1:
        return [list(p1)[0], 0]
    elif len(p1) > 1 and len(n1) == 1:
        return [0, list(n1)[0]]
    elif len(p1) > 1 and len(n1) > 1:
        return [0, 0]
    else:
        return [list(p1)[0], list(n1)[0]]


assert emergency(89, 20, 41, 1, 11) == [2, 3]
assert emergency(11, 1, 1, 1, 1) == [0, 1]
assert emergency(3, 2, 2, 2, 1) == [-1, -1]
assert emergency(16, 2, 15, 2, 1) == [2, 0]
assert emergency(17, 2, 15, 2, 1) == [2, 0]
assert emergency(18, 2, 15, 2, 1) == [2, 0]
assert emergency(19, 2, 15, 2, 1) == [2, 0]
assert emergency(20, 2, 15, 2, 1) == [2, 0]
assert emergency(21, 2, 15, 2, 1) == [0, 0]
assert emergency(22, 2, 15, 2, 1) == [0, 0]
assert emergency(23, 2, 15, 2, 1) == [0, 0]
assert emergency(24, 2, 15, 2, 1) == [0, 0]
assert emergency(25, 2, 15, 2, 1) == [0, 0]
assert emergency(26, 2, 15, 2, 1) == [0, 0]
assert emergency(27, 2, 15, 2, 1) == [0, 0]
assert emergency(28, 2, 15, 2, 1) == [0, 0]
assert emergency(29, 2, 15, 2, 1) == [3, 0]
assert emergency(5, 20, 2, 1, 1) == [1, 0]
assert emergency(20, 20, 2, 1, 1) == [1, 0]
assert emergency(21, 20, 2, 1, 1) == [1, 0]
assert emergency(753, 10, 1000, 1, 1) == [1, 1]
assert emergency(10, 3, 50, 1, 50) == [-1, -1]
assert emergency(25, 3, 1, 1, 1) == [0, 0]
assert emergency(25, 3, 1, 1, 1) == [0, 0]
assert emergency(24, 3, 1, 1, 1) == [0, 0]
assert emergency(23, 3, 1, 1, 1) == [0, 0]
assert emergency(22, 3, 1, 1, 1) == [0, 0]
assert emergency(21, 3, 1, 1, 1) == [0, 0]
assert emergency(20, 3, 1, 1, 1) == [0, 0]
assert emergency(19, 3, 1, 1, 1) == [0, 0]
assert emergency(18, 3, 1, 1, 1) == [0, 0]
assert emergency(17, 3, 1, 1, 1) == [0, 0]
assert emergency(16, 3, 1, 1, 1) == [0, 0]
assert emergency(15, 3, 1, 1, 1) == [0, 0]
assert emergency(19, 3, 8, 1, 1) == [1, 0]
assert emergency(19, 3, 7, 1, 1) == [1, 0]
assert emergency(19, 3, 6, 1, 1) == [0, 0]
assert emergency(18, 3, 6, 1, 1) == [1, 0]
assert emergency(6, 3, 18, 1, 1) == [1, 1]
assert emergency(3, 1, 9, 7, 3) == [-1, -1]
assert emergency(3, 1, 2, 1, 1) == [0, 1]
assert emergency(2, 1, 1, 1, 1) == [0, 1]
assert emergency(3, 2, 2, 1, 1) == [1, 0]
assert emergency(2, 3, 1, 1, 1) == [1, 0]
assert emergency(842887, 10, 163729, 24, 8) == [123, 0]
assert emergency(20, 10, 4, 1, 5) == [-1, -1]
assert emergency(20, 10, 5, 1, 5) == [2, 10]
assert emergency(11, 2, 4, 1, 2) == [0, 2]