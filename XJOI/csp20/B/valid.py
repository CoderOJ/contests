s = ""
a = []

while True:
    try:
        s = input()
    except:
        break
    a.append(int( ''.join( s.split() ) , 5))

a.sort()

for i in range( len(a) ):
    if i != a[i]:
        print("ERROR at " + str(i) + " and " + str(a[i]))
