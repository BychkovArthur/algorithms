nums = list(map(int, input().split()))

key = 1

if len(nums) <= 1:
    print('YES')
else:
    for i in range(len(nums) - 1):
        if nums[i] >= nums[i + 1]:
            key = 0
            break

    if key:
        print('YES')
    else:
        print('NO')