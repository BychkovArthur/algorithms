nums = list(map(int, input().split()))

cnt = 0

for i in range(1, len(nums) - 1):
    if nums[i - 1] < nums[i] > nums[i + 1]:
        cnt += 1
        
print(cnt)