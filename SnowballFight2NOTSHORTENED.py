import sys

def input():
    return sys.stdin.readline().strip()

input()
sweeds = list(map(int, input().split(" ")))
finns = list(map(int, input().split(" ")))

count = 0

spointer = 0
fpointer = 0

while spointer < len(sweeds) and fpointer < len(finns):
    if sweeds[spointer] > finns[fpointer]:
        count += 1
        fpointer += 1
    spointer += 1

spointer = 0
fpointer = 0

while spointer < len(sweeds) and fpointer < len(finns):
    if sweeds[spointer] < finns[fpointer]:
        count += 1
        spointer += 1
    fpointer += 1

print(count)