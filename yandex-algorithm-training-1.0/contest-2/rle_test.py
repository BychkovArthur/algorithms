def encode(s):
    
    if len(s) == 0:
        return ''

    if len(s) == 1:
        return s
    
    result = []
    last = s[0]
    current_cnt = 1
    
    for i in s[1:]:
        
        if i == last:
            current_cnt += 1
        else:
            if current_cnt > 1:
                result += [last + str(current_cnt)]
            else:
                result += [last]
            current_cnt = 1
            last = i
    
    if current_cnt == 1:
        result += [last]
    else:
        result += [last + str(current_cnt)]
    
    return ''.join(result)

assert encode('a') == 'a'
assert encode('') == ''
assert encode('aa') == 'a2'
assert encode('aaa') == 'a3'
assert encode('aaabbbc') == 'a3b3c'
assert encode('abc') == 'abc'
assert encode('abcc') == 'abc2'
assert encode('abbcbbc') == 'ab2cb2c'
assert encode('aeeeeeeeeee') == 'ae10'
# print(encode('abc'))
