from functools import reduce

T = int(input())
for i in range(T):
    input()
    xor_sum = reduce(lambda x, y : x ^ y, list(map(int, input().split()))[1::2], 0)
    print("first" if xor_sum else "second")
