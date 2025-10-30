import sys
sys.stdin = open("input.txt")
sys.stdin.readline().strip()
print(sum(map(int, sys.stdin.read().split("\n"))))