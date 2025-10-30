import sys
sys.stdin = open("input.txt", "r")
def input():
    return sys.stdin.readline().strip()

try:
    while True:
        C, n = map(int, input().split())

        memo = [[-1] * C] * n

        nums = [tuple(map(int, input().split())) for i in range(n)]

        def dp(id, remW):
            if id == n or remW == 0:
                return 0
            ans = memo[id][remW - 1]
            if ans != -1:
                return ans
            if nums[id][1] > remW:
                ans = dp(id + 1, remW)
                memo[id][remW - 1] = ans
                return ans
            ans = max(dp(id + 1, remW), nums[id][0] + dp(id + 1, remW - nums[id][1]))
            memo[id][remW - 1] = ans
            return ans
        output = dp(0, C)
        for el in memo:
            print(el)
        print(output)
except:
    pass