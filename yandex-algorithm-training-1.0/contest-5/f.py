n = int(input())
classes = sorted(map(int, input().strip().split()))
m = int(input())
conditioners = []
for i in range(m):
    conditioners += [tuple(map(int, input().split()))]
conditioners.sort(key=lambda x : x[1])
sm = 0

class_pointer = 0
cond_pointer = 0
while class_pointer != n:
    if conditioners[cond_pointer][0] >= classes[class_pointer]:
        sm += conditioners[cond_pointer][1]
        class_pointer += 1
    else:
        cond_pointer += 1
print(sm)
