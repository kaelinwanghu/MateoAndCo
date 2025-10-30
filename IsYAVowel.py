import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

s = list(filter(lambda x: x in ['a','e','i','o','u','y'],input()))
print(len(list(filter(lambda x: x != 'y', s))),len(s))