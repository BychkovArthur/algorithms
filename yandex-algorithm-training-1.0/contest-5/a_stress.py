import random
def fast(n, a, m, b):
    a_ind = 0
    b_ind = 0
    current_diff = abs(a[0] - b[0])
    minimal_diff = current_diff
    min_a = a[0]
    min_b = b[0]

    while not(a_ind + 1 == len(a) and b_ind + 1 == len(b)):
        
        if a_ind + 1 != len(a) and abs(a[a_ind + 1] - b[b_ind]) <= current_diff:
            a_ind += 1
            current_diff = abs(a[a_ind] - b[b_ind])
            if minimal_diff > current_diff:
                minimal_diff = current_diff
                min_a = a[a_ind]
                min_b = b[b_ind]
                
        elif b_ind + 1 != len(b) and abs(a[a_ind] - b[b_ind + 1]) <= current_diff:
            b_ind += 1
            current_diff = abs(a[a_ind] - b[b_ind])
            if minimal_diff > current_diff:
                minimal_diff = current_diff
                min_a = a[a_ind]
                min_b = b[b_ind]
        else:
            if b_ind + 1 != len(b):
                b_ind += 1
            else:
                a_ind += 1
            current_diff = abs(a[a_ind] - b[b_ind])
    return min_a, min_b

def slow(n, a, m, b):
    min = abs(a[0] - b[0])
    min_a = a[0]
    min_b = b[0]
    for i in a:
        for j in b:
            if abs(i - j) < min:
                min = abs(i - j)
                min_a = i
                min_b = j
    return min_a, min_b

def generate():
    n = random.randint(1, 7)
    m = random.randint(1, 7)
    a = sorted(set([random.randint(0, 10) for _ in range(n)]))
    b = sorted(set([random.randint(0,  10) for _ in range(m)]))
    return n, a, m, b

def compare():
    
    counter = 1
    while True:
        data = generate()
        sl = slow(*data)
        fs = fast(*data)
        if abs(sl[0] - sl[1]) == abs(fs[0] - fs[1]):
            print(f'Тест {counter} пройден')
            counter += 1
        else:
            print(f'Тест {counter} не пройден')
            print(f'n = {data[0]}, a = {data[1]}')
            print(f'm = {data[2]}, b = {data[3]}')
            print(f'slow: {slow(*data)}, fast: {fast(*data)}')
            break
compare()