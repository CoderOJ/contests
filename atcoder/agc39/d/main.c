#include <math.h>
#include <stdio.h>

#define N 3005
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int n, l;
int a[N];

int main()
{
  scanf("%d%d", &n, &l);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);

  double ans_x = 0;
  double ans_y = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    {
      int    cnt = j - i - 1;
      int    mul = n - (cnt + 1) * 2;
      double arc = M_PI * (a[i] + a[j]) / l;
      ans_x += cos(arc) * mul;
      ans_y += sin(arc) * mul;
    }

  double cnt = 1.0 * n * (n - 1) * (n - 2) / 6;
  printf("%.15f %.15f\n", ans_x / cnt, ans_y / cnt);

  return 0;
}
