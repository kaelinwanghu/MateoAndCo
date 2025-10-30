import sys

def input():
    return sys.stdin.readline().strip()

r, c = map(int, input().split())
start = tuple(map(lambda x: int(x), input().split()))
end = tuple(map(lambda x: int(x), input().split()))

maze = [[1 for _ in range(c + 2)]] + list(map(lambda x: list(map(int, ['1'] + list(x) + ['1'])), (sys.stdin.read().splitlines()))) + [[1 for _ in range(c + 2)]]

visited = set()
loc = [start[0], start[1]]
dirs = ((0, 1), (-1, 0), (0, -1), (1, 0))
dir = 0
while not tuple(loc + [dir]) in visited and maze[loc[0]][loc[1]] != 1:
    if maze[loc[0] + dirs[(dir + 1) % 4][0]][loc[1] + dirs[(dir + 1) % 4][1]] == 0:
        visited.add(tuple(loc + [dir]))
        loc[0] += dirs[(dir + 1) % 4][0]
        loc[1] += dirs[(dir + 1) % 4][1]
        dir += 1
        dir %= 4
    elif maze[loc[0] + dirs[dir][0]][loc[1] + dirs[dir][1]] == 0:
        visited.add(tuple(loc + [dir]))
        loc[0] += dirs[dir][0]
        loc[1] += dirs[dir][1]
    else:
        visited.add(tuple(loc + [dir]))
        dir += 3
        dir %= 4
    if tuple(loc) == end:
        print(1)
        exit()
print(0)