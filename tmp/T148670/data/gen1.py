# Chain generator: for 17,20

n,m,c = 500000,1000000,1
print(n,m,c)
for i in range(1,n):
    print(i,i+1)
for i in range(1,n,2):
    print(i,i+1)
for i in range(2,n,2):
    print(i,i+1)
print(1,n)
print(1,n)
