nums = list(map(int, input().split()))


mx_1 = max(nums[0], nums[1], nums[2])
mx_2 = nums[0] + nums[1] + nums[2] - min(nums[0], nums[1], nums[2]) - max(nums[0], nums[1], nums[2])
mx_3 = min(nums[0], nums[1], nums[2])

for i in range(3, len(nums)):
    if nums[i] >= mx_1:
        mx_3 = mx_2
        mx_2 = mx_1
        mx_1 = nums[i]
    elif mx_2 <= nums[i] < mx_1:
        mx_3 = mx_2
        mx_2 = nums[i]
    elif mx_3 < nums[i] < mx_2:
        mx_3 = nums[i]
    
ans_1 = [mx_1, mx_2, mx_3]

mx_1 = max(-nums[0], -nums[1])
mx_2 = min(-nums[0], -nums[1])

for i in range(2, len(nums)):
    nums[i] *= -1
    if nums[i] >= mx_1:
        mx_2 = mx_1
        mx_1 = nums[i]
    elif mx_2 < nums[i] < mx_1:
        mx_2 = nums[i]

ans_2 = [ans_1[0], -mx_1, -mx_2]

print(*max(ans_1, ans_2, key=lambda x: x[0] * x[1] * x[2]))