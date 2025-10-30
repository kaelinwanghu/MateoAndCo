import sys
import math

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

n,k,p=map(int,input().split())

fac = []

for i in range(1, int(n ** 0.5) + 1):
    if n % i == 0:
        if i * p >= n:
            fac.append(i)
        if n // i <= k and n // i * p >= n:
            fac.append(n // i)

fac.sort()
print(len(fac))
for i in range(len(fac)):
    print(fac[i])