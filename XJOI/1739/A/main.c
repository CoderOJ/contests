#include <stdio.h>

const int modd[] = {0, 1, 0, 1, 2};

int main()
{
  int n;
  scanf("%d", &n);

  int ans = 0;
  for (int i=1; i<=n; ++i)
  {
    int x;
    scanf("%d", &x);

    if (i % 2 == 0)
    {
      int r = x % (i + 1);
      if (r == i)
        ans ^= 2;
      else 
        ans ^= r & 1;
    }
    else
      ans ^= x % 2;
  }

  puts(ans ? "tomato fish+1s" : "rainy day+1s");

  return 0;
}
