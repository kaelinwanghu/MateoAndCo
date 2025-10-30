import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

i=input;print(i()*int(i()))