import random

def generate_random_letter():
    frequencies = [
        ("a", 0.25), ("g", 0.25), ("t", 0.25), ("c", 0.25)
    ]
    letters, weights = zip(*frequencies)
    return random.choices(letters, weights=weights, k=1)[0]

with open('input.txt', 'w') as file:
    for i in range(1000000):
        file.write(generate_random_letter())
