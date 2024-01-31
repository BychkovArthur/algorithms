a = int(input())
b = int(input())
c = int(input())

if c < 0:
    print('NO SOLUTION')
elif a == 0:
    if c * c == b:
        print('MANY SOLUTIONS')
    else:
        print('NO SOLUTION')
else:
    result = (c * c - b) / a
    if int(result) == result:
        print(int(result))
    else:
        print('NO SOLUTION')