import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

n, m = map(int, input().split())

candidates = [0] * m
votes = [0] * n

for i in range(m):
    candidates[i] = input()

for i in range(n):
    votes[i] = list(map(int, input().split()))

print(votes, candidates)