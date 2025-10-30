import sys
import math

sys.stdin = open("inputtxt", "r")

def input():
    return sys.stdin.readline().strip()

def dist(x1, y1, x2, y2):
    return math.hypot(x2 - x1, y2 - y1)

num_points = int(input())

points = [[0.0, 0.0, 0.0]]

for _ in range(num_points):
    x, y, t = map(float, input().split())
    points.append([x, y, t])

fastest_time = sys.maxint
tds = []

for i in range(1, num_points):
    distance = 0
    time = 0

    while (distance < 100):
        d = dist(points[i][0], points[i][1], points[i - 1][0], points[i - 1][1])

        if (distance + d >= 100):
            time += points[i][2] * (d - (distance - 100)) / d
        else:
            time += points[i][2]

        distance += d
        tds.append(points[i][2], d)

    

print(fastest_time)