n = int(input())
s = input()

if n < 2:
    print("Yes")
elif n == 2:
    print("Yes" if s[0] == s[1] else "No")
elif s[0] == 'B':
    print("Yes")
elif s[0] != s[-1]:
    print("No")
elif s == s[::-1]:
    print("Yes")
elif n == 4:
    print("No")
else:
    print("Yes")
