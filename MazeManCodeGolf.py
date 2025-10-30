import sys;sys.setrecursionlimit(10000);m,n=map(int, input().split());b=["X"]*(n+2);g=[b]
for _ in range(m):
 g.append(["X"]+list(input())+["X"])
g.append(b)
e = [0]
l=False
def f(r,c,a,t):
 if g[r][c]=="X":return
 elif g[r][c]=="."and a[0]==0:e[0]+=1;a[0]=1
 elif ord("A")<=ord(g[r][c])<=ord("W") and not t:return
 g[r][c]="X";f(r-1,c,a,l);f(r+1,c,a,l);f(r,c-1,a,l);f(r,c+1,a,l)
a=[0]
for i in range(1,m+1):
 for j in range(1,n+1):
  if ord("A")<=ord(g[i][j])<=ord("W"):
   f(i,j,a,True)
  a[0]=0
d=0
for i in range(1,m+1):
 for j in range(1,n+1):
  if g[i][j]==".":
   d+=1
print(e[0],d)