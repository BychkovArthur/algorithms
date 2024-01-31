import sys
ht = {}
def change_balance(person, amount):
    if person in ht:
        ht[person] += amount
    else:
        ht[person] = amount

for line in sys.stdin:
    operation = line.split()
    if operation[0] == 'DEPOSIT':
        change_balance(operation[1], int(operation[2]))
    elif operation[0] == 'WITHDRAW':
        change_balance(operation[1], -int(operation[2]))
    elif operation[0] == 'BALANCE':
        if operation[1] in ht:
            print(ht[operation[1]])
        else:
            print('ERROR')
    elif operation[0] == 'TRANSFER':
        change_balance(operation[1], -int(operation[3]))
        change_balance(operation[2], int(operation[3]))
    elif operation[0] == 'INCOME':
        for person in ht:
            if ht[person] > 0:
                ht[person] = int(ht[person] * (1 + int(operation[1]) / 100))