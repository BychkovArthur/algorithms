import random
import string

big_string_length, small_string_length, small_string_count, alphabet = input().strip().split()
big_string_length = int(big_string_length)
small_string_length = int(small_string_length)
small_string_count = int(small_string_count)

# Функция для генерации случайной строки из маленьких букв
def generate_random_string(length):
    return ''.join(random.choices(alphabet, k=length))

# Генератор файла
def generate_file(big_string_length, small_string_count, small_string_length, filename):
    # Генерируем большую строку
    big_string = generate_random_string(big_string_length)

    # Генерируем маленькие строки
    small_strings = [generate_random_string(small_string_length) for _ in range(small_string_count)]

    # Записываем в файл
    with open(filename, 'w') as file:
        # Записываем большую строку
        file.write(big_string + '\n')

        # Записываем маленькие строки
        for small_string in small_strings:
            file.write(small_string + '\n')

# Пример использования
generate_file(big_string_length=big_string_length, small_string_count=small_string_count, small_string_length=small_string_length, filename='output.txt')
