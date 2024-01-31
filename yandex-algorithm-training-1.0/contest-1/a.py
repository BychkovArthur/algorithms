t_room, t_cond = map(int, input().split())
action = input()

if action == 'freeze':
    print(min(t_room, t_cond))
elif action == 'heat':
    print(max(t_room, t_cond))
elif action == 'auto':
    print(t_cond)
else:
    print(t_room)
