import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

string = input()
counter = 0

max_id = 0
maximum = 0
min_id = 0
minimum = 0
for i in range(1, len(string) + 1):
    change = 1 if string[i - 1] == "R" else -1
    counter += change
    if counter > maximum:
        max_id = i
        maximum = counter
    if counter < minimum:
        min_id = i
        minimum = counter

output = sorted([min_id, max_id])
print(output[0] + 1, output[1])