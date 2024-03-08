from random import randint, choices
from string import ascii_lowercase, ascii_uppercase

with open("input", "w") as file:
    
    alphabet = ascii_lowercase + ascii_uppercase
    
    for i in range(1_000_000):
        if (i % 1000 == 0):
            print(i)
    
        day = randint(1, 31)
        month = randint(1, 12)
        year = randint(1, 3000)
        
        file.write(f'{day}.{month}.{year}\t')
        
        strlen = randint(1, 2048)
        string = ''.join(choices(alphabet, k=strlen))
        file.write(string)
        file.write('\n')
    