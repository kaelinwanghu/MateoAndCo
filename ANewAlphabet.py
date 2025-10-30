import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

alphabet = {'a': '@', 'b': '8', 'c': '(', 'd': '|)', 'e': '3', 'f': '#', 'g': '6', 'h': '[-]', 'i': '|', 'j': '_|', 'k': '|<', 'l': '1', 'm': '[]\\/[]', 'n': '[]\\[]', 'o': '0', 'p': '|D', 'q': '(,)', 'r': '|Z', 's': '$', 't': "']['", 'u': '|_|', 'v': '\\/', 'w': '\\/\\/', 'x': '}{', 'y': '`/', 'z': '2'}

string = input()

output = ""
for i in range(len(string)):
    char = alphabet.get(string[i].lower())
    if char == None:
        output += string[i]
    else:
        output += char
print(output)