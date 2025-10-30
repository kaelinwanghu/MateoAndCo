import sys

sys.stdin = open("input.txt", "r")

n = int(input())

nums = sorted(list(map(int, sys.stdin.read().splitlines())))

sum_of_nums = sum(nums)

num = 0
sum_temp = sum_of_nums - n * nums[0]
for i in range(1, n):
    num += sum_temp
    sum_temp -= (n - i) * (nums[i] - nums[i - 1])

den = n * sum_of_nums

print(num / den)