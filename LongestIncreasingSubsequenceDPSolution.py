import sys
sys.stdin = open("input.txt", "r")
def input():
    return sys.stdin.readline().strip()

nums = []
memo = []

def get_indices(indices, longest):
    output = [indices.index(longest)]
    for i in range(output[0], -1, -1):
        if indices[i] == longest - 1:
            longest -= 1
            output.append(i)
    return reversed(output)

def LIS(index):
    output = memo[index]
    if output != -1:
        return output
    output = 1

    for j in range(index):
        memo[j] = LIS(j)
        if nums[j] < nums[index]:
            output = max(output, LIS(j) + 1)

    return output

while input():
    nums = list(map(int, input().split()))
    memo = [-1] * len(nums)
    memo[0] = 1
    memo[len(memo) - 1] = LIS(len(memo) - 1)
    longest = max(memo)
    indices = get_indices(memo, longest)

    print(max(memo))
    for el in indices:
        print(el, end=" ")
    print()
    