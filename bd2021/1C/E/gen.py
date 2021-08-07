print(10000)
for a in range(10):
    for b in range(10):
        for c in range(10):
            for d in range(10):
                # print(a * 1000 + b * 100 + c * 10 + d, end = " ")
                if a and b and c and d:
                    print(a, b, c, d)
                else:
                    print("1 1 1 1")
