from collections import defaultdict
n, k = map(int, input().strip().split())
stirng = list(input().strip())

def solution(stirng, n, k):
    left = 0
    right = 0
    current_nums = defaultdict(int)
    current_nums[stirng[0]] = 1
    max_len = 1
    ans_left = 1
    while True:
        if right - left + 1 > max_len and all(i <= k for i in current_nums.values()):
            max_len = right - left + 1
            ans_left = left + 1
        if right < n - 1 and current_nums[stirng[right + 1]] < k:
            right += 1
            current_nums[stirng[right]] += 1
        elif left < right:
            current_nums[stirng[left]] -= 1
            left += 1
        elif right < n - 1:
            right += 1
            current_nums[stirng[right]] += 1
        else:
            break
        
    return max_len, ans_left

print(*solution(stirng, n, k))
