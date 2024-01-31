n, k = map(int, input().strip().split())
nums = list(map(int, input().strip().split()))
current_sum = 0
left = 0
ans = 0
for i in range(n):
    current_sum += nums[i]
    
    while current_sum > k:
        current_sum -= nums[left]
        left += 1
    
    if k == current_sum:
        ans += 1
print(ans)
