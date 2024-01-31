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

def slow(nums, n, k):
    min_len = n
    ans_left = 1
    ans_right = n
    for left in range(n):
        for right in range(left, n):
            current_nums = set()
            for i in range(left, right + 1):
                current_nums.add(nums[i])
            if len(current_nums) == k and right - left + 1 < min_len:
                min_len = right - left + 1
                ans_left = left + 1
                ans_right = right + 1
    return ans_left, ans_right

def compare():
    import random
    count = 0
    while True:
        n = random.randint(1, 10)
        k = random.randint(1, n)
        nums = [random.randint(1, k) for _ in range(n)]

        slow_res = slow(nums, n, k)
        fast_res = solution(nums, n, k)
        if slow_res == fast_res:
            print(f'Тест {count} пройден успешно')
            count += 1
        else:
            print(f'Тест {count} провален')
            print(f'nums: {nums}\nn={n}, k={k}')
            print(f'slow:{slow_res}, fast:{fast_res}')

            break

compare()