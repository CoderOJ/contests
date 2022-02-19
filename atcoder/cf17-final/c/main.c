#include <stdio.h>
#include <stdlib.h>

int d[55];
int n;

int int_cmp(const void *a, const void *b)
{
  return *(const int *)a - *(const int *)b;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &d[i]);
  d[n] = 0;

  qsort(d, n + 1, sizeof(int), int_cmp);

  for (int i = 0; i <= n; i += 2)
    d[i] *= -1;

  qsort(d, n + 1, sizeof(int), int_cmp);

  int s = 50;
  for (int i = 0; i < n; i++)
    if (s > d[i + 1] - d[i])
      s = d[i + 1] - d[i];
  if (s > d[0] + 24 - d[n])
    s = d[0] + 24 - d[n];
  printf("%d\n", s);

  return 0;
}
