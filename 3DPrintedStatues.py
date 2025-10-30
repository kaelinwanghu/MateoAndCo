import sys
import math

sys.stdin = open("input.txt", "r")

numStatues = int(sys.stdin.readline().strip())

print(math.ceil(math.log(numStatues, 2)) + 1)