n = int(input())
nums = list(map(int, input().split()))

mx_value = -1e9
mx_index = -1e9

for i in range(n):
    if nums[i] > mx_value:
        mx_value = nums[i]
        mx_index = i

vasiliy_cnt = 0

for i in range(n - 1):
    if nums[i] % 10 == 5 and i > mx_index and nums[i + 1] < nums[i]:
        vasiliy_cnt = max(vasiliy_cnt, nums[i])

if vasiliy_cnt:

    cnt = 0

    for i in range(n):
        if nums[i] > vasiliy_cnt:
            cnt += 1

    print(cnt + 1)
else:
    print(0)