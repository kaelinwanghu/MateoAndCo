input()
def q():return list(map(int,input().split()))
s=q();f=q();c=w=i=0
while w<len(s)and i<len(f):c+=s[w]>f[i];i+=s[w]>f[i];w+=1
w=i=0
while w<len(s)and i<len(f):c+=s[w]<f[i];w+=s[w]<f[i];i+=1
print(c)