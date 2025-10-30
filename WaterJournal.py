import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

n,a,b=map(int,input().split())

drinks=[]
for _ in range(n - 1):
    drinks.append(int(input()))

ain = a in drinks
bin = b in drinks

if not ain and not bin:
    print(-1)
elif not ain:
    print(a)
elif not bin:
    print(b)
else:
    for i in range(a, b + 1):
        print(i)