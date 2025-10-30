import sys
import math

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

num, type = input().split()
num = int(num)

deck = list(range(num))

def shuffle(deck):
    if type == "out":
        newDeck = [item for tpl in zip(deck[:math.floor(num / 2)], deck[math.ceil(num / 2):]) for item in tpl]
        if num % 2 != 0:
            newDeck.append(deck[math.floor(num / 2)])
    if type == "in":
        newDeck = [item for tpl in zip(deck[math.floor(num / 2):], deck[:math.floor(num / 2)]) for item in tpl]
        if num % 2 != 0:
            newDeck.append(deck[-1])
    return newDeck

count = 1
deck = shuffle(deck)
while not deck == sorted(deck):
    deck = shuffle(deck)
    count += 1

print(count)