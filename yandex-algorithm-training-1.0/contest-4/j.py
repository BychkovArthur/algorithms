import sys
def word_to_bool(word):
    if word == 'yes':
        return True
    if word == 'no':
        return False
    
data = input().split()
n = int(data[0])
capital = word_to_bool(data[1])
start_with_digit = word_to_bool(data[2])

key_words = set()
for _ in range(n):
    if capital:
        key_words.add(input())
    else:
        key_words.add(input().lower())

id_chars_str = 'qwertyuioplkjhgfdsazxcvbnmMNBVCXZASDFGHJKLPOIUYTREWQ_0123456789'
id_chars = set(id_chars_str)

identificators = {}
current_line_number = 0
for line in sys.stdin:
    current_line_number += 1
    current_id = ''
    
    for i in range(len(line)):
        symb = line[i]
        if symb in id_chars:
            current_id += symb

        else:
            if current_id == '': continue
            if not start_with_digit and current_id[0].isdigit() or not ( any(not j.isdigit() for j in current_id) ):
                current_id = ''
                continue
            # print(current_id)
            
            if capital:
                if current_id in key_words:
                    pass
                else:
                    if current_id not in identificators:
                        identificators[current_id] = [current_line_number, i, 1]
                    else:
                        identificators[current_id][2] += 1
            else:
                if current_id.lower() in key_words:
                    pass
                else:
                    if current_id.lower() not in identificators:
                        identificators[current_id.lower()] = [current_line_number, i, 1]
                    else:
                        identificators[current_id.lower()][2] += 1
            current_id = ''
            # print(identificators)


max = sorted(list(identificators.values()), key=lambda x: x[1])

max = sorted(max, key=lambda x: x[0])

max = sorted(max, key=lambda x: -x[2])

max = max[0]

for key in identificators:
    if identificators[key] == max:
        print(key)
        break

