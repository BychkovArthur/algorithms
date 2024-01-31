codes = [None] * 4
numbers = [None] * 4

for i in range(4):
    number = input().replace('(', '').replace(')', '').replace('-', '')
    if (len(number)) == 7:
        codes[i] = '495'
        numbers[i] = number
    else:
        if number[0] == '8':
            codes[i] = number[1:4]
            numbers[i] = number[4:]
        else:
            codes[i] = number[2:5]
            numbers[i] = number[5:]

for i in range(1, 4):
    if codes[i] == codes[0] and numbers[i] == numbers[0]:
        print('YES')
    else:
        print('NO')