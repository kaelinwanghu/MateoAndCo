import random

size = (6, 7)

output = ""

for i in range(size[0]):
    for j in range(size[1] - 1):
        output += str(random.randint(0, 1)) + " "
    output += str(random.randint(0, 1)) + "\n"

print(output[:len(output) - 1])