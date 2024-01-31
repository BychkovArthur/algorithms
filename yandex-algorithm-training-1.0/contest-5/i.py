k = int(input().strip())
s = input().strip()
n = len(s)
left = 0
right = k - 1
total_cnt = 0
current_streak = 0
while right < n - 1:
    if s[left] == s[right + 1]:
        current_streak += 1
        total_cnt += current_streak
    else:
        current_streak = 0
    left += 1
    right += 1
print(total_cnt)