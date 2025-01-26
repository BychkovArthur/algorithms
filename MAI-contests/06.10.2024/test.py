# cnt = 0
# for i in range(1, 555555 + 1):
#     if '9' in str(i):
#         cnt += 1
# print(cnt)

# print(4 * 40951 + 2 * 3439 + 9 * 271 + (1000 - 271) + 5 * 19 + 13 )


# print(5 * 40951 + 55556)

# print(
#     (5 * 40951 + (10**5 - 40951)) 
#     + (5 * 3439 + (10**4 - 3439))
#     + (5 * 271 + (10**3 - 271))
#     + (5 * 19 + (100 - 19))
#     + (5 * 1 + (10 - 1))
#     + 1
#       )
# print(40951 * 2)

# print(12345678 - 5217031 - 468559 * 2 - 40951 * 3 - 3439 * 4 - 271 * 5 - 19 * 6 - 7 + 1)


arr = [1]
sm = 1

for i in range(1, 30):
    arr += [8 * arr[i - 1] + 10 ** i]
    arr[i] += arr[i - 1]
    
# print(arr)
    
t = int(input())
for _ in range(t):
    n, x = map(int, input().split())
    strn = str(n)[::-1]
    
    cnt = 0
    
    i = len(strn) - 1
    while i >= 1:
        digit = int(strn[i])
        if digit < x:
            cnt += digit * arr[i - 1]
            # print(f'adding1 {digit * arr[i - 1]}')
        elif digit > x:
            cnt += digit * arr[i - 1] + (10 ** i - arr[i - 1])
            # print(f'adding2 {digit * arr[i - 1] + (10 ** i - arr[i - 1])}')
        else:
            cnt += digit * arr[i - 1] + int(strn[:i][::-1]) + 1
            # print(digit * arr[i - 1])
            # print(int(strn[:i][::-1]))
            # print(f'adding3 {digit * arr[i - 1] + int(strn[:i:-1])}')
            break
        i -= 1
        
    if i == 0:
        cnt += (int(strn[i]) >= x)
    
    print(n - cnt + 1)
    
    
