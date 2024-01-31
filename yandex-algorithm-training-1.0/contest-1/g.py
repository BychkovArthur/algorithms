n, k, m = map(int, input().split())

cnt = 0
if (n < k or k < m):
    print(0)
else:
    while n >= k:
        
        cnt += n // k * (k // m)
        n = n - (n // k) * k + (k % m) * (n // k)

    print(cnt)