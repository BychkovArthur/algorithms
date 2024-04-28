from random import randint, choices, choice
from string import ascii_lowercase, ascii_uppercase, digits

def string_gen(strlen : int = 10, alphabet : str = ascii_lowercase):
    return ''.join(choices(alphabet, k=strlen))

with open("benchmark_input.txt", "w") as file:
    
    for _ in range(10_000):
        operation_type = choice(['?', '+', '-'])
        
        strlen = randint(1, 5)
        string = string_gen(strlen)
        
        if operation_type == '?':
            file.write(f'? {string}')
            
        elif operation_type == '+':
            value = randint(0, 1000)
            file.write(f'+ {string} {value}')
            
        elif operation_type == '-':
            file.write(f'- {string}')
        file.write('\n')