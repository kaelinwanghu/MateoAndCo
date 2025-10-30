import sys
def i():
    return sys.stdin.readline().strip()
n=list(map(int,i().split()))
n.sort()
r=list(i())
o=""
while r:
    o=str(n[ord(r.pop())-65])+" "+o
print(o[:len(o)])