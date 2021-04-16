n = 18
m = n * (n-1) // 2
print(n,m)
for i in range(1,n):
    for j in range(i+1,n+1):
        print(i, j, 1000000000)
