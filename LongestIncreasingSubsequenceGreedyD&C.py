from bisect import bisect_left
import sys
import time

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

output = []

def build_indices(start, p):
    output = [str(start)]
    index = start
    while p[index] != -1:
        output.append(str(p[index]))
        index = p[index]
    return list(reversed(output))

while input():
    A = list(map(int,input().split()))
    L = []
    L_id = []
    p = [-1] * len(A)

    for i in range(len(A)):
        a = A[i]
        index = bisect_left(L, a)
        if index == len(L):
            L.append(a)
            L_id.append(i)
            p[i] = L_id[index - 1] if index != 0 else -1
        elif a < L[index]:
            L[index] = a
            L_id[index] = i
            p[i] = L_id[index - 1] if index != 0 else -1
    output.append(len(L))
    output.append(" ".join(build_indices(L_id[len(L_id) - 1], p)))

print("\n".join(map(str,output)))