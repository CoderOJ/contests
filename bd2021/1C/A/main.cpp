#include <bits/stdc++.h>

int main()
{
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, c, a, b;
    scanf("%d%d%d%d", &n, &c, &a, &b);
    if (a > b || b > c || a > c) { puts("no"); }
    else if (a == b && b == c) { puts("yes"); }
    else if (a == b || b == c) { puts("no"); }
    else if (n == 2 && a + c == b * 2) { puts("yes"); }
    else if (n < 3) { puts("no"); }
    else if (b * n <= a + c * (n-1) && b * n >= a * (n-1) + c) { puts("yes"); }
    else { puts("no"); }
  }
  return 0;
}
