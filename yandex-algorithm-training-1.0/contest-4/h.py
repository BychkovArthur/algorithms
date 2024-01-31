g, n = map(int, input().split())

s1 = input()
s2 = input()

sliced = s2[:g]

count = 0
last_ind = 0

letters = 'qwertyuioplkjhgfdsazxcvbnmMNBVCXZASDFGHJKLPOIUYTREWQ'

ht1 = {i : 0 for i in letters}
ht2 = {i : 0 for i in letters}

for i in range(g):
    ht1[s1[i]] += 1
    ht2[sliced[i]] += 1
    

count_of_different_letters_s1 = 0
number_of_matching_letters = 0

for letter in ht1:
    count_of_different_letters_s1 += 1
    if ht1[letter] == ht2[letter]:
        number_of_matching_letters += 1
        

if number_of_matching_letters == count_of_different_letters_s1:
    count += 1

for i in range(g, n):
    current_symb = s2[i]
    departed_character = s2[i - g]
    
    ht2[current_symb] += 1
    ht2[departed_character] -= 1
    

    if current_symb != departed_character:
        if ht2[current_symb] == ht1[current_symb]:
            number_of_matching_letters += 1
            
        elif ht2[current_symb] == ht1[current_symb] + 1:
            number_of_matching_letters -= 1
        
        
        if ht2[departed_character] == ht1[departed_character]:
            number_of_matching_letters += 1
        elif ht2[departed_character] == ht1[departed_character] - 1:
            number_of_matching_letters -= 1
    
    
    if number_of_matching_letters == count_of_different_letters_s1:
        count += 1

        
print(count)