#include <stdio.h>
#include <string.h>

size_t max(size_t a, size_t b)
{
  return a > b ? a : b;
}

size_t cnt[128];
char   s[100005];

int main()
{
  scanf("%s", s);
  size_t n = strlen(s);
  for (size_t i = 0; i < n; i++)
    cnt[(int)s[i]]++;

  size_t max_cnt = 0;
  for (int i = 0; i < 128; i++)
    max_cnt = max(max_cnt, cnt[i]);

  puts(max_cnt * 3 <= n + 2 ? "YES" : "NO");

  return 0;
}
