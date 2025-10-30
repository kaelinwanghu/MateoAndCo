import sys
import bisect

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

N, H = list(map(int, input().split()))

mites = []
tites = []

for i in range(N):
    if i % 2 == 0:
        mites.append(int(input()))
    else:
        tites.append(int(input()))

mites.sort()
tites.sort()

heights = [0] * H

for i in range(0, H):
    heights[i] += N // 2 - bisect.bisect_left(mites, i + 1)
    heights[i] += N // 2 - bisect.bisect_left(tites, H - i)

min = min(heights)
print(min, heights.count(min))