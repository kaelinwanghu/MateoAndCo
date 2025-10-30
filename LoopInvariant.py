import sys
s=sys.stdin.readline().strip()
p=0
c=0
while True:
    c=c+1 if s[p]=="("else c-1
    p+=1
    if c==0:
        break
P=s[:p]
o=len(P)
l=len(s)
t="no"
for i in range(p,l,o):
    if l-p<o:
        t=s[o:]+P
        break
    for j in range(i,i+o):
        if s[j]!=P[j-i]:
            t=s[o:]+P
            break
print("no")