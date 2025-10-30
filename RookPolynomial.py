'''
    WRITTEN BY: Emmet Southfield on 13, 14 October 2025
'''

import sys, copy, math, time

sys.stdin = open("input.txt", "r")
sys.setrecursionlimit(10**6)

superscripts = {1: "", 2: "\u00b2", 3: "\u00b3", 4: "\u2074", 5: "\u2075", 6: "\u2076", 7: "\u2077", 8: "\u2078", 9: "\u2079"}

m, n, k = map(int, sys.stdin.readline().strip().split())

board = list(map(lambda x: list(map(int, x.split(" "))), sys.stdin.read().splitlines()))

memo = {}

call_count = [0]

# def get_arbitrary_board():
#     size = (4, 4)

#     output = ""

#     for i in range(size[0]):
#         for j in range(size[1] - 1):
#             output += str(random.randint(0, 1)) + " "
#         output += str(random.randint(0, 1)) + "\n"

#     return list(map(lambda x: list(map(int, x.split(" "))), output.splitlines()))

def board_is_empty(board):
    for row in board:
        for square in row:
            if square != 0:
                return False
    return True

def place_rook_at(point, board):
    for i in range(len(board[point[0]])):
        board[point[0]][i] = 0
    for i in range(len(board)):
        board[i][point[1]] = 0
    return board

def eliminate_rook_at(point, board):
    board[point[0]][point[1]] = 0
    return board

def get_place_location(board):
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == 1:
                return (i, j)
    return (-1, -1)

def get_board_ID(board):
    ID = [[], []]
    for row in board:
        ID[0].append(sum(row))
    for i in range(len(board[0])):
        count = 0
        for j in range(len(board)):
            count += board[j][i]
        ID[1].append(count)
    ID[0] = " ".join(map(str, sorted(ID[0])))
    ID[1] = " ".join(map(str, sorted(ID[1])))
    ID = ID[0] + "|" + ID[1]
    return ID

def memoize_board(board_ID, rooks, output):
    memo[board_ID] = output[rooks:] + output[:rooks]

def board_in_memo(board):
    return board in memo

def board_is_rectangle(board_ID):
    board_ID = set(board_ID.replace("|", " ").split())
    if len(board_ID) <= 2 or (len(board_ID) == 3 and '0' in board_ID):
        return True
    return False
    
def rectangle_size(board_ID):
    board_ID = list(map(int, filter(lambda x: x != "0", set(board_ID.replace("|", " ").split()))))
    if len(board_ID) == 1:
        board_ID.append(board_ID[0])
    return sorted(board_ID)

def rook(board, rooks, output):
    call_count[0] += 1
    if board_is_empty(board):
        output[rooks] += 1
        return output
    board_ID = get_board_ID(board)
    if board_in_memo(board_ID):
        output = memo[board_ID]
        return output[-rooks:] + output[:-rooks]
    elif board_is_rectangle(board_ID):
        size = rectangle_size(board_ID)
        for i in range(size[0] + 1):
            coef = math.factorial(size[0]) / (math.factorial(size[0] - i) * math.factorial(i)) * math.factorial(size[1]) / math.factorial(size[1] - i)
            try:
                output[i + rooks] += int(coef)
            except:
                output[i + rooks] += coef
        memoize_board(board_ID, rooks, output)
        return output
    else:
        placement = get_place_location(board)
        left = rook(place_rook_at(placement, copy.deepcopy(board)), rooks + 1, copy.deepcopy(output))
        right = rook(eliminate_rook_at(placement, copy.deepcopy(board)), rooks, copy.deepcopy(output))
        for i in range(len(output)): output[i] += left[i] + right[i]
    memoize_board(board_ID, rooks, output)
    return output

start = time.time()
output = rook(copy.deepcopy(board), 0, [0] * (min(len(board), len(board[0])) + 1))

to_print = ""

for i in range(len(output)):
    if output[i] > 1 or i == 0:
        to_print += str(output[i])
    if output[i] != 0 and i != 0:
        to_print += "x"
    if output[i] >= 1 and i != 0:
        to_print += str(superscripts.get(i, "<" + str(i) + ">"))
    if i != len(output) - 1 and output[i + 1] != 0:
        to_print += " + "

print(to_print)
end = time.time()

print(end - start)

a = sum(output)
b = 2 ** (m * n - k)
common_factor = math.gcd(a, b)
print(int(((a * b) / common_factor) % 79841))