#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 105;
bool      mp[N * 2][N * 2];

void set_pixel_to_black(int x, int y)
{
  mp[N + x][N + y] = true;
}

void draw_circle_perimeter(int r)
{
  for (int x = -r; x <= r; x++)
  {
    int y = static_cast<int>(round(sqrt(r * r - x * x)));
    set_pixel_to_black(x, y);
    set_pixel_to_black(x, -y);
    set_pixel_to_black(y, x);
    set_pixel_to_black(-y, x);
  }
}

int main()
{
  for (int i = 0; i < N; i++)
    draw_circle_perimeter(i);

  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    printf("Case #%d: ", i + 1);

    int n = sc.next_int();
    int ans = 0;
    for (int i = -n; i <= n; i++)
      for (int j = -n; j <= n; j++)
        if (round(sqrt(i * i + j * j)) <= n)
          if (!mp[N + i][N + j])
            ans += 1;
    printf("%d\n", ans);
  }
  return 0;
}
