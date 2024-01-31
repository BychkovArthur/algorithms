n, r = map(int, input().strip().split())

nums = list(map(int, input().strip().split()))

left = 0
right = 1
cnt = 0
while right < len(nums):
    if nums[right] - nums[left] <= r:
        right += 1
    else:
        cnt += len(nums) - right
        left += 1
print(cnt)