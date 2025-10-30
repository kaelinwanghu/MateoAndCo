import sys

sys.setrecursionlimit(10000)

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

m,n = map(int, input().split())

map = [["X"] * (n + 2)]

for _ in range(m):
    map.append(["X"] + list(input()) + ["X"])

map.append(["X"] * (n + 2))

entrances = [0]

def flood_fill(row, col, flag, start):
    if map[row][col] == "X":
        return
    elif map[row][col] == "." and flag[0] == 0:
        entrances[0] += 1
        flag[0] = 1
    elif ord("A") <= ord(map[row][col]) <= ord("W") and not start:
        return
    map[row][col] = "X"

    flood_fill(row - 1, col, flag, False)
    flood_fill(row + 1, col, flag, False)
    flood_fill(row, col - 1, flag, False)
    flood_fill(row, col + 1, flag, False)

flag = [0]

for i in range(1, m + 1):
    for j in range(1, n + 1):
        if ord("A") <= ord(map[i][j]) <= ord("W"):
            flood_fill(i, j, flag, True)
        flag[0] = 0

dots_left = 0
for i in range(1, m + 1):
    for j in range(1, n + 1):
        if map[i][j] == ".":
            dots_left += 1

print(entrances[0], dots_left)