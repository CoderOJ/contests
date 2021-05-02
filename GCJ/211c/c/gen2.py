lim = 256

print(lim * lim)
for i in range(lim):
    for j in range(lim):
        print(bin(i)[2:], bin(j)[2:])
