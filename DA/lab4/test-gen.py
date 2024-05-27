from random import randint
from sys import argv

with open("benchmark_input.txt", "w") as file:
    pattern_len = randint(int(argv[1]), int(argv[2]))
    for _ in range(pattern_len):
        file.write(str(randint(0, 2)))
        file.write(" ")
    file.write("\n")
    
    for _ in range(1_000_000):
        file.write(str(randint(0, 2)))
        file.write(" ")
        if randint(1, 10) == 1:
            file.write("\n")
        
    