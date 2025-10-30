def ff(number):
    factors = []
    for i in range(1, int(number**0.5) + 1):
        if number % i == 0:
            factors.append(i)
            if i * i != number:
                factors.append(number // i)
    factors.sort()
    return factors

num = 17
add = 0
for i in range(1, 100):
    print(i, ff(num))
    add += 2
    num += add