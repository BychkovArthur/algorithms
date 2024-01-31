import sys
result = set()
for i in sys.stdin:
    for word in i.split():
        result.add(word)
print(len(result))