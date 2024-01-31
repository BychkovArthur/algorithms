n = int(input())

know_everyone = set()


for i in range(n):
    m = int(input())
    current = set()
    for j in range(m):
        current.add(input())
    if i == 0:
        know_atleastone = current
    else:
        know_atleastone &= current
    know_everyone |= current

print(len(know_atleastone), *know_atleastone, sep='\n')
print(len(know_everyone), *know_everyone, sep='\n')