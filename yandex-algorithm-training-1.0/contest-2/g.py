nums = list(map(int, input().split()))

mx_1 = max(nums[0], nums[1])
mx_2 = min(nums[0], nums[1])

for i in range(2, len(nums)):
    if nums[i] >= mx_1:
        mx_2 = mx_1
        mx_1 = nums[i]
    elif mx_2 < nums[i] < mx_1:
        mx_2 = nums[i]

ans_1 = [mx_2,  mx_1]

mx_1 = max(-nums[0], -nums[1])
mx_2 = min(-nums[0], -nums[1])

for i in range(2, len(nums)):
    nums[i] *= -1
    if nums[i] >= mx_1:
        mx_2 = mx_1
        mx_1 = nums[i]
    elif mx_2 < nums[i] < mx_1:
        mx_2 = nums[i]

print(*max(ans_1, [-mx_1, -mx_2], key=lambda x: x[0] * x[1]))