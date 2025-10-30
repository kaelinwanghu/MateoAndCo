import sys

sys.stdin = open("input.txt", "r")

total_nums = int(sys.stdin.readline().strip())
list_of_nums = list(map(float, sys.stdin.read().split("\n")))

if len(list_of_nums) == 2:
    print(0)
    exit()

dp = {}
rc = [0]

def calcfreemium(m, e):
    output1 = list_of_nums[e]
    output2 = 1 - list_of_nums[e]
    for j in range(total_nums):
        if e != j and m & (1<<j) != 0:
            output1 *= 1 - list_of_nums[j]
            output2 *= list_of_nums[j]
    return output1 + output2

def calc(m):
    output = 0
    for i in range(len(list_of_nums)):
        output += calcfreemium(m, i)
    return 1 / output

def gross_logic(m, ms):
    rc[0] += 1
    if rc[0] % 100000 == 0:
        print("Repeat!", rc[0])
    if m in dp.keys():
        return dp[m]
    elif ms == 3:
        dp[m] = calc(m)
        return dp[m]
    else:
        child_sum = 0
        this_size = calc(m)
        for i in range(total_nums):
            if m & (1<<i) != 0:
                child_sum += gross_logic(m & ~(1<<i), ms - 1) * (calcfreemium(m, i) * this_size)
        dp[m] = child_sum + this_size
        return dp[m]

print(gross_logic((1<<total_nums) - 1, total_nums))