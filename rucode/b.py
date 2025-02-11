n = int(input())
k = int(input())

ab = set()
cd = set()
ef = set()

a = input()
for i in range(n):
    for j in a.split(' '):
        ab.add(int(j))
a = input()
for i in range(n):
    for j in a.split(' '):
        cd.add(int(j))
a = input()
for i in range(n):
    for j in a.split(' '):
        ef.add(int(j))

ans = 0

ab_cd_ef = ab & cd & ef
sab_cd_ef = len(ab_cd_ef)

ab_cd = ab & cd
cd_ef = cd & ef
sab_cd = len(ab_cd) - sab_cd_ef
scd_ef = len(cd_ef) - sab_cd_ef

_1 = 0
_2 = 0
_3 = 0

while _1 != k or _2 != k or _3 != k:
    ans += 1
    if sab_cd_ef > 0 and _1 < k and _2 < k and _3 < k:
        sab_cd_ef -= 1
        _1 += 1
        _2 += 1
        _3 += 1
    elif sab_cd > 0 and _1 < k and _2 < k:
        sab_cd -= 1
        _1 += 1
        _2 += 1
    elif scd_ef > 0 and _2 < k and _3 < k:
        scd_ef -= 1
        _2 += 1
        _3 += 1
    elif _1 < k:
        _1 += 1
    elif _2 < k:
        _2 += 1
    elif _3 < k:
        _3 += 1

print(ans)
