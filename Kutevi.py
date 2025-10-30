import sys, bisect

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

N, K = map(int, input().split())

can_draw = sorted(list(map(int, input().split())))

can_construct = set()
for i in range(len(can_draw)):
    if 360 % can_draw[i] != 0 and can_draw[bisect.bisect_left(can_draw, can_draw[i] % 360)] != 360 % can_draw[i]:
        can_construct.add(360 % can_draw[i])

for angle in can_construct:
    can_draw.insert(bisect.bisect_left(can_draw, angle), angle)
can_construct = set()

while True:
    for i in range(len(can_draw) - 1, - 1, -1):
        for j in range(i - 1, -1, -1):
            target = can_draw[i] % can_draw[j]
            if target != 0 and can_draw[bisect.bisect_left(can_draw, target)] != target:
                can_construct.add(target)
    for i in range(1, 360 // can_draw[i]):
        for j in range(i, len(can_draw)):
            target = can_draw[j] + can_draw[i] * i
            insert_loc = bisect.bisect_left(can_draw, target)
            if target < 360 and (insert_loc == len(can_draw) or can_draw[insert_loc] != target):
                can_construct.add(target)
    for angle in can_construct:
        additive_angle = angle
        while additive_angle <= 360:
            insert_loc = bisect.bisect_left(can_draw, additive_angle)
            if insert_loc == len(can_draw) or can_draw[insert_loc] != additive_angle:
                can_draw.insert(insert_loc, additive_angle)
            additive_angle += angle
    if len(can_construct) == 0:
        break
    can_construct = set()

can_draw = set(can_draw)

to_draw = list(map(int, input().split()))

for num in to_draw:
    print("YES" if num in can_draw else "NO")