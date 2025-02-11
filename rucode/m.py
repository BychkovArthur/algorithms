st = set()
st.add((8, 1, 8, 7))
st.add((2, 0, 0, 0))
st.add((11, 0, 0, 0))
st.add((7, 0, 0, 0))
st.add((6, 0, 0, 0))
st.add((3, 4, 0, 0))
st.add((17, 0, 0, 0))
st.add((8, 7, 0, 0))
st.add((5, 10, 0, 0))

n = int(input())


for i in range(n):
    tp = tuple(map(len, input().split()))
    if (len(tp) > 4): 
        print(0)
        continue
    if (len(tp) < 4): 
        tp += (0, ) * (4 - len(tp))
    if tp in st:
        print(1)
    else:
        print(0)