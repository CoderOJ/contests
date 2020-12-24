n = 3000000
bs = 2000001

print(n)
for i in range(1,n+1):
    print( max(1, (i-bs) * 3), end=' ' )

