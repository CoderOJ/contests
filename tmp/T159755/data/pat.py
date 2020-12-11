from random import *

pa = 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaa'
pb = 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaa'

sa = ""
na = 990000
while len(sa) < na:
    lim = randrange(1, 10)
    for i in range(lim):
        sa = sa + pa
    sa = sa + 'cc'

sb = ""
nb = 999000
while len(sb) < nb:
    sb = sb + pb

print(sa)
print(sb)
