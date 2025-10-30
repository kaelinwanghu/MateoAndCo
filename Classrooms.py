import sys

sys.stdin = open("input.txt", "r")

def input():
    return sys.stdin.readline().strip()

n, k = map(int, input().split())

activities = [0] * n
for i in range(n):
    activities[i] = tuple(map(int, input().split()))

activities.sort(key=lambda x: (x[1], x[0]))

classrooms = [(0, 0)] * k

count = 0

for activity in activities:
    for i in range(len(classrooms)):
        if activity[0] > classrooms[i][1]:
            classrooms[i] = activity
            classrooms.sort(key=lambda x: x[1], reverse = True)
            count += 1
            break

print(count)