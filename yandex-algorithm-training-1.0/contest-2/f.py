n = int(input())
nums = list(map(int, input().split()))

def is_valid_index(i):
    return 0 <= i < n

def odd_len(i):
    for j in range(1, n - i + 1):
        if is_valid_index(i - j) and is_valid_index(i + j):
            if nums[i + j] == nums[i - j]:
                continue
            else:
                return 1e9
        if not(is_valid_index(i - j)) and not(is_valid_index(i + j)):
            return 0
        if not(is_valid_index(i - j)) and is_valid_index(i + j):
            return 1e9
        return max(i - j + 1, n - (i + j))
    
def even_right_len(i):
    if not(is_valid_index(i -1) and nums[i] == nums[i - 1]):
        return 1e9
    for j in range(1, n):
        if is_valid_index(i + j) and is_valid_index(i - 1 - j):
            if nums[i + j] == nums[i - 1 - j]:
                continue
            else:
                return 1e9
        if not(is_valid_index(i - j - 1)) and not(is_valid_index(i + j)):
            return 0
        if not(is_valid_index(i - j - 1)) and is_valid_index(i + j):
            return 1e9
        return max(i - j, n - (i + j))

'''
1. Является ли элемент "центром симметрии последовательсности"
Тут 3 случая, 
'''

type = 0 # 1 - odd 2 - even
m = 1e9
ind = -1

for i in range(n):
    if even_right_len(i) < m:
        type = 2
        m = even_right_len(i)
        ind = i
    
    if odd_len(i) < m:
        type = 1
        m = odd_len(i)
        ind = i
        
print(m)
if m != 0:
    if type == 1:
        for i in range(m - 1, -1, -1):
            print(nums[i], end=' ')
    else:
        for i in range(m - 1, -1, -1):
            print(nums[i], end=' ')
print()