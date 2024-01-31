from itertools import permutations
def slow(g, n, s1, s2):
    possible = [''.join(i) for i in permutations(s1)]
    count = 0
    for i in range(g, n + 1):
        if s2[i - g: i] in possible:
            count += 1
    
    return count
    
def fast(g, n, s1, s2):
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

    # print(ht1, ht2, sep='\n')
    print(number_of_matching_letters)



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
    return count


def generate():
    from random import randint
    letters = 'qwertyuioplkjhgfdsazxcvbnmMNBVCXZASDFGHJKLPOIUYTREWQ'
    g = randint(2, 5)
    n = randint(g, 15)
    s1 = ''
    s2 = ''
    for i in range(g):
        s1 += letters[randint(0, 51)]
    for i in range(n):
        s2 += letters[randint(0, 51)]
    return g, n, s1, s2


def main():
    count = 1
    while True:
        data = generate()
        sl = slow(*data)
        fs = fast(*data)
        if sl != fs:
            print(f'Тест {count} не пройден, slow: {sl}, fast: {fs} \n g: {data[0]}\n n: {data[1]}\n s1: {data[2]}\n s2: {data[3]}\n')
            break
        print(count)
        count += 1
main()