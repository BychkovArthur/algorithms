n = int(input())

dct = {}
dct_reverse = {}

for i in range(n):
    word1, word2 = input().split()
    dct[word1] = word2
    dct_reverse[word2] = word1

if (s:= input()) in dct:
    print(dct[s])
else:
    print(dct_reverse[s])