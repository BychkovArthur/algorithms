n, k = map(int, input().strip().split())

nums = list(map(int, input().strip().split()))



def solution(nums, n, k):
    from collections import defaultdict
    left = 0
    right = 0
    current_nums = defaultdict(int)
    current_nums[nums[0]] = 1
    min_len = n
    ans_left = 1
    ans_right = n
    while True: 
        if len(current_nums) == k:
            if right - left + 1 < min_len:
                min_len = right - left + 1
                ans_left = left + 1
                ans_right = right + 1
        
        if left == right and right < n - 1:
            right += 1
            current_nums[nums[right]] += 1
        elif left < n - 1 and current_nums[nums[left]] > 1:
            current_nums[nums[left]] -= 1
            left += 1
        elif right < n - 1:
            right += 1
            current_nums[nums[right]] += 1
        else:
            break
        
    return ans_left, ans_right


print(*solution(nums, n, k))
