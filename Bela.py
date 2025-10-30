import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

vals = {"A": (11, 11), "K": (4, 4), "Q": (3, 3), "J": (20, 2), "T": (10, 10), "9": (14, 0), "8": (0, 0), "7": (0, 0)}

trump = input().split()[1]

card = input()
score = 0
while card:
    if card[1] == trump:
        score += vals[card[0]][0]
    else:
        score += vals[card[0]][0]
    card = input()

print(score)