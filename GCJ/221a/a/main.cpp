#include <bits/stdc++.h>

const int N = 1005;
char s[N];
int n;

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++)
  {
    printf("Case #%d: ", i);
    scanf("%s", s);
    n = (int)strlen(s);
    for (int i = 0; i < n; i++)
    {
      bool smaller = [i]{
        for (int j = i + 1; ; j++)
          if (s[j] != s[i])
            return s[j] < s[i];
      }();
      if (smaller) putchar(s[i]);
      else putchar(s[i]), putchar(s[i]);
    }
    puts("");
  }
  return 0;
}
