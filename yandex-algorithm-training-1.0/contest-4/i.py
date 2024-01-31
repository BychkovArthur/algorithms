n = int(input())
def get_index_caps(word):
    count = 0
    index = 0
    for i in range(len(word)):
        if 'A' <= word[i] <= 'Z':
            index = i
            count += 1
    if count != 1:
        return -1
    return index
            
        
dictionary = {}

for i in range(n):
    word = input()
    udarenie = get_index_caps(word)
    word = word.lower()
    if word not in dictionary:
        dictionary[word] = {udarenie}
    else:
        dictionary[word].add(udarenie)
        
petya = input().split()
miss = 0
for word in petya:
    
    action = get_index_caps(word)
    word = word.lower()
    
    if action == -1:
        miss += 1
    else:
        if word in dictionary:
            if action not in dictionary[word]:
                miss += 1
print(miss)