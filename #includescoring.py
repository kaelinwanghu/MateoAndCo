import sys

sys.stdin = open("input.txt", "r")

n = int(sys.stdin.readline().strip())

points_per_rank = [100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1] + [0] * (n - 30)

scores = list(map(lambda x: list(map(int, x.split())), sys.stdin.read().splitlines()))

for i in range(len(scores)):
    scores[i] += [i, 0]

scores.sort(key= lambda x: (-x[0], x[1], x[2]))

output = [0] * n

def average_rounded_up(nums):
    return (sum(nums) + len(nums) - 1) // len(nums)

def compares_scores(s1, s2):
    if s1[0] == s2[0] and s1[1] == s2[1] and s1[2] == s2[2]:
        return True
    return False

ties = []
for i in range(0, n - 1):
    ties.append(scores[i])
    if not compares_scores(scores[i], scores[i + 1]):
        points = average_rounded_up(points_per_rank[i - len(ties) + 1:i + 1])
        for score in ties:
            output[score[4]] = points + score[3]
        ties = []

ties.append(scores[n - 1])
points = average_rounded_up(points_per_rank[(n - 1) - len(ties) + 1:(n - 1) + 1])
for score in ties:
    output[score[4]] = points + score[3]


for score in output:
    print(score)