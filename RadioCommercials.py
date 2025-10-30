import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

N, P = map(int, input().split())

nums = map(int, input().split())

max = 0
count = 0
for num in nums:
    count += num - P
    max = count if count > max else max
    count = 0 if count < 0 else count

print(max)