from sys import stdin

def input():
    return stdin.readline().strip()

n, m, q = map(int, input().split())

class DSU:
    def __init__(self, n: int):
        self.parents = [i for i in range(n + 1)]
        self.ranks = [0 for _ in range(n + 1)]

    def find(self, x):
        if (x != self.parents[x]): x = self.find(self.parents[x])
        return self.parents[x]

    def share_set(self, x, y):
        return self.find(x) == self.find(y)

    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if self.ranks[x] > self.ranks[y]: self.parents[y] = x
        else:
            self.parents[x] = y
            if self.ranks[x] == self.ranks[y]: self.ranks[y] += 1
    
    def __str__(self):
        disjoint_sets = [set() for _ in range(n)]
        for i in range(1, len(self.parents)):
            disjoint_sets[self.parents[i] - 1].add(i)
        return ' '.join(map(str, filter(lambda x: x, disjoint_sets)))

distrust: dict[int, set[int]] = {a: set() for a in range(1, n + 1)}
for _ in range(m):
    u, v = map(int, input().split())
    distrust[u].add(v)
    distrust[v].add(u)

islands = DSU(n)
for _ in range(q):
    a, b = map(int, input().split())
    a = islands.find(a)
    b = islands.find(b)
    
    if a in distrust[b]:
        print('REFUSE')
    else:
        print('APPROVE')
        islands.union(a, b)
        rep = islands.find(a)
        old = a if rep == b else b
        for c in distrust[old]:
            distrust[c].remove(old)
            distrust[c].add(rep)
            distrust[rep].add(c)