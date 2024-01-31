a = int(input())
b = int(input())
c = int(input())
e = int(input())
d = int(input())

def is_fit(a, b, c, d):
    return c <= a and d <= b

if is_fit(e, d, a, b) or is_fit(e, d, a, c) or is_fit(e, d, b, a) or is_fit(e, d, b, c) or is_fit(e, d, c, a) or is_fit(e, d, c, b):
    print("YES")
else:
    print("NO")