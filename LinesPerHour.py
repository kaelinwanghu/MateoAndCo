import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

n,lph=map(int,input().split())

lph*=5

problems=[]
for _ in range(n):
    problems.append(int(input()))

problems.sort()

total = 0

i = 0
while total < lph and i < len(problems):
    if lph - total - problems[i] >= 0:
        total += problems[i]
        i += 1
    else:
        break

print(i)