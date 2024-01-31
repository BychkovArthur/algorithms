const = 1
asc = 1
wasc = 1
desc = 1
wdesc = 1

cnt = 0
last_number = None

while True:
    num = int(input())
    
    if num == -2 * 1e9:
        break
    
    if last_number is None:
        last_number = num
        cnt += 1
        continue
    
    if last_number != num:
        const = 0
    if last_number >= num:
        asc = 0
    if last_number > num:
        wasc = 0
    if last_number <= num:
        desc = 0
    if last_number < num:
        wdesc = 0
    
    last_number = num
    cnt += 1

if cnt <= 1:
    print('CONSTANT')
elif const:
    print('CONSTANT')
elif asc:
    print('ASCENDING')
elif wasc:
    print('WEAKLY ASCENDING')
elif desc:
    print('DESCENDING')
elif wdesc:
    print('WEAKLY DESCENDING')
else:
    print('RANDOM')