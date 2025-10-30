import sys

def input():
    return sys.stdin.readline().strip()

s = input()

print("? 0")

lowest_quack = int(input())

print("? " + str((pow (10,9) + 1)))

highest_quack = int(input())

if lowest_quack == highest_quack:
    print("! 1")
    print(lowest_quack)
    exit(0)

list_of_quacks = [lowest_quack, highest_quack]

squack = [(lowest_quack, highest_quack)]

while squack:
    l_quack, h_quack = squack.pop()
    mid = (h_quack + l_quack + 1) // 2

    print("? " + str(mid))

    new_quack = int(input())

    if new_quack in list_of_quacks or new_quack < l_quack or new_quack > h_quack:
        continue

    list_of_quacks.append(new_quack)


    print(list_of_quacks)
    print(squack)

print("! " + str(len(list_of_quacks)))

for q in list_of_quacks:
    print(q, end = " ")
    sys.stdout.flush()

print()
exit(0)