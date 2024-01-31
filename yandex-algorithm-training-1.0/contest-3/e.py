have = set(input().split())
need = set()
for letter in input():
    need.add(letter)
# print(len(need - have))
cnt = 0
for i in need:
    if i not in have:
        cnt += 1
print(cnt)