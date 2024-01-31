n = int(input())
a = list(map(int, input().strip().split()))
m = int(input())
b = list(map(int, input().strip().split()))

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

print(min_a, min_b)