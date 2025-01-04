import struct

file_name = input("Введите имя файла: ")
values = map(int, input("Введите значения: ").split())

# Открываем файл для записи в бинарном режиме
with open(file_name, 'wb') as file:
    for value in values:
        # Записываем каждое число как 2-байтовое целое (формат 'h' для short)
        # file.write(struct.pack('h', value))
        file.write(struct.pack('B', value))

print(f"Значения записаны в файл {file_name}")
