import random
import string

# Функция для генерации случайной строки из маленьких букв
def generate_random_string(length):
    return ''.join(random.choices('abcdefgh', k=length))

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
generate_file(big_string_length=100000, small_string_count=10000, small_string_length=5, filename='output.txt')
