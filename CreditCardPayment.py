import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

input()
class Payment():
    def __init__(self, r, b, m):
        self.r = r
        self.b = b
        self.m = m
        self.nb = self.b

    def cycle(self):
        self.b = round(self.nb, 2)
        self.addInterest()
        self.makePayment()

    def addInterest(self):
        self.nb += self.nb * (self.r / 100)    
    
    def makePayment(self):
        self.nb -= self.m

    def balancePaid(self):
        return self.b <= 0

payment = input().split(" ")
while (payment):
    payment = Payment(float(payment[0]), float(payment[1]), float(payment[2]))
    for i in range (1, 1201):
        payment.cycle()
        if payment.balancePaid():
            print(i)
            break
        if i == 1200:
            print("impossible")
    payment = input().split()    