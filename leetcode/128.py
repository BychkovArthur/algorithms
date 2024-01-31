def longestConsecutive(nums):
    ht = {i : [1, 1] for i in nums}
    
    for num in nums:
        if num + 1 in ht:
            ht[num][0] = ht[num + 1][0] + 1
        if num - 1 in ht:
            ht[num][0] = ht[num - 1][0] + 1
    for num in reversed(nums):
        if num + 1 in ht:
            ht[num][0] = ht[num + 1][0] + 1
        if num - 1 in ht:
            ht[num][0] = ht[num - 1][0] + 1
    print(ht)

from itertools import permutations
for i in permutations([1, 2, 3, 4, 5]):
    print(i)
    longestConsecutive(i)
    print('\n')
