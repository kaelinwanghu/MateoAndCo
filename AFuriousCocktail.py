import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

drinkingTime = int(input().split(" ")[1])
potion = input()
potions = []
while potion:
    potion = int(potion)
    potions.append(potion)
    potion = input()

potions.sort()

while potions:
    potion = potions.pop()
    if potion <= len(potions) * drinkingTime:
        print("NO")
        exit(0)

print("YES")