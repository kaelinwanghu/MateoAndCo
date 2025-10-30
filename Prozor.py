import sys, time

sys.stdin = open("input.txt", "r")
start = time.time()
R, S, K = map(int, input().split())

pane = list(map(list, sys.stdin.read().splitlines()));

memo = [[0 for _ in range(S - 2)] for _ in range(R - K + 1)]
output_memo = [[0 for _ in range(S - K + 1)] for _ in range (R - K + 1)]

vals = {'*': 1, '.': 0}

for i in range(len(memo)):
    for j in range(len(memo[i])):
        if i == 0:
            for k in range(1, K - 1):
                memo[i][j] += 1 if pane[k][j + 1] == "*" else 0
        else:
            memo[i][j] = memo[i - 1][j] - vals[pane[i][j + 1]] + vals[pane[i + K - 2][j + 1]]
        if len(memo[i]) - j == len(output_memo[i]):
            output_memo[i][0] = sum(memo[i][:j + 1])
        elif len(memo[i]) - j < len(output_memo[i]):
            output_memo[i][len(output_memo[i]) - len(memo[i]) + j] = output_memo[i][len(output_memo[i]) - len(memo[i]) + j - 1] - memo[i][j - K + 2] + memo[i][j]

maximum = 0
max_id = (0, 0)
for i in range(len(output_memo)):
    for j in range(len(output_memo[i])):
        if output_memo[i][j] > maximum:
            maximum = output_memo[i][j]
            max_id = (i, j)

for i in range(max_id[0], max_id[0] + K):
    for j in range(max_id[1], max_id[1] + K):
        if (i == max_id[0] or i == max_id[0] + K - 1):
            pane[i][j] = "-"
        if (j == max_id[1] or j == max_id[1] + K - 1):
            pane[i][j] = "|"
        if (i == max_id[0] or i == max_id[0] + K - 1) and (j == max_id[1] or j == max_id[1] + K - 1):
            pane[i][j] = "+"

print(maximum)
for p in pane:
    print("".join(p))

end = time.time()

print(end - start)