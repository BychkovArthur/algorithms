from collections import defaultdict
n, k = map(int, input().strip().split())
nums = sorted(map(int, input().strip().split()))
counter = defaultdict(int)
for key in nums:
    counter[key] += 1
keys = list(counter.keys())
count_nums_more_2_times = [0] * len(keys)
total_count_nums_more_2_times = 0
for i, key in enumerate(keys):
    if counter[key] >= 2:
        total_count_nums_more_2_times += 1
    count_nums_more_2_times[i] = total_count_nums_more_2_times
left = 0
right = 0
answer = 0

for left in range(len(keys)):
    while right < len(keys) - 1 and keys[left] * k >= keys[right + 1]:
        right += 1
    answer += (right - left) * (right - left - 1) * 3
    count_nums_more_2_times_in_segment = count_nums_more_2_times[right] - count_nums_more_2_times[left]
    answer += count_nums_more_2_times_in_segment * 3
    if counter[keys[left]] >= 2:
        answer += 3 * (right - left)
    if counter[keys[left]] >= 3:
        answer += 1


print(answer)