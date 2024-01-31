n = int(input())
nums = list(map(int, input().split()))
m = int(input())

delta = 1e9
ans = 1e9

for i in range(n):
    
    if abs(m - nums[i]) < delta:
        delta = abs(m - nums[i])
        ans = nums[i]

print(ans)