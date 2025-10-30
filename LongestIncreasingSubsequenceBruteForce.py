import sys
sys.stdin = open("input.txt", "r")
def input():
    return sys.stdin.readline().strip()

def is_increasing(nums):
    for i in range(1, len(nums)):
        if nums[i] <= nums[i - 1]:
            return False
    return True

while input():
    max_indices = []

    nums = list(map(int, input().split()))
    for i in range(0, 2 ** len(nums)):
        j = 0
        subset = []
        indices = []
        while j < len(nums):
            if i & 2 ** j:
                subset.append(nums[j])
                indices.append(j)
            j += 1
        if is_increasing(subset) and len(subset) > len(max_indices):
            max_indices = indices
    print(len(max_indices))
    for item in max_indices:
        print(item, end=" ")
    print()