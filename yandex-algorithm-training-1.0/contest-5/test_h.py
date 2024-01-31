from collections import defaultdict
def solution(stirng, n, k):
    left = 0
    right = 0
    current_nums = defaultdict(int)
    current_nums[stirng[0]] = 1
    max_len = 1
    ans_left = 1
    while True:
        if right - left + 1 > max_len:
            max_len = right - left + 1
            ans_left = left + 1
        if right < n - 1 and current_nums[stirng[right + 1]] < k:
            right += 1
            current_nums[stirng[right]] += 1
        elif left < right:
            current_nums[stirng[left]] -= 1
            left += 1
        else:
            break
        

    return max_len, ans_left

def slow(nums, n, k):
    max_len = 1
    max_left = 1
    for left in range(n):
        for right in range(left, n):
            current_nums = defaultdict(int)
            for i in range(left, right + 1):
                current_nums[nums[i]] += 1
            if all(i <= k for i in current_nums.values()) and right - left + 1 > max_len:
                max_len = right - left + 1
                max_left = left + 1
    return max_len, max_left

def compare():
    import random
    count = 0
    while True:
        n = random.randint(1, 10)
        k = random.randint(1, n)
        nums = ''.join([str(random.randint(1, k)) for _ in range(n)])

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