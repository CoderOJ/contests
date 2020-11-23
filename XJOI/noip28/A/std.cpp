//愿你和你重要的人能够再次重逢！
#include <bits/stdc++.h>
using namespace std;
template<typename T>
inline void
read(T& x)
{
  x = 0;
  char c = getchar(), f = 0;
  for (; c < '0' || c > '9'; c = getchar())
    if (!(c ^ 45))
      f = 1;
  for (; c >= '0' && c <= '9'; c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  if (f)
    x = -x;
}
int n, m, Q, lg[805], a[805][805], st[2][805][805][10];
long long S[805][805];
inline void
SM(int a, int b, int c, int d)
{
  printf("%lld\n", S[c][d] - S[c][b - 1] - S[a - 1][d] + S[a - 1][b - 1]);
}
inline int
qwq(int a, int b, int tg)
{
  if (tg)
    return a > b ? a : b;
  else
    return a < b ? a : b;
}
inline void
MX(int x1, int y1, int x2, int y2, int tag)
{
  int res = tag ? 0 : 1e9 + 5, l = min(lg[x2 - x1 + 1], lg[y2 - y1 + 1]);
  // res=qwq(res,st[tag][x1][y1][l],tag);
  // res=qwq(res,st[tag][x1][y2-(1<<l)+1][l],tag);
  // res=qwq(res,st[tag][x2-(1<<l)+1][y1][l],tag);
  // res=qwq(res,st[tag][x2-(1<<l)+1][y2-(1<<l)+1][l],tag);
  // if(x1+(2<<l)-1<=x2)
  // res=qwq(res,st[tag][x1+(1<<l)-1][y1][l],tag),res=qwq(res,st[tag][x1+(1<<l)-1][y2-(1<<l)+1][l],tag);
  // if(y1+(2<<l)-1<=y2)
  // res=qwq(res,st[tag][x1][y1+(1<<l)-1][l],tag),res=qwq(res,st[tag][x2-(1<<l)+1][y1+(1<<l)-1][l],tag);
  for (int x = x1; x <= x2; x += (1 << l))
    for (int y = y1; y <= y2; y += (1 << l)) {
      int xx = min(x, x2 - (1 << l) + 1), yy = min(y, y2 - (1 << l) + 1);
      res = qwq(res, st[tag][xx][yy][l], tag);
    }
  printf("%d\n", res);
}
int
main()
{
  read(n), read(m), lg[0] = -1;
  char ch[5];
  for (int i = 1; i <= 800; i++)
    lg[i] = lg[i >> 1] + 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      read(a[i][j]), st[0][i][j][0] = st[1][i][j][0] = a[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + a[i][j];
  for (int k = 1; k <= 9; k++)
    for (int i = 1; i + (1 << (k - 1)) <= n; i++)
      for (int j = 1; j + (1 << (k - 1)) <= m; j++)
        st[0][i][j][k] =
          min(min(st[0][i][j][k - 1], st[0][i][j + (1 << (k - 1))][k - 1]),
              min(st[0][i + (1 << (k - 1))][j][k - 1],
                  st[0][i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1]));
  for (int k = 1; k <= 9; k++)
    for (int i = 1; i + (1 << (k - 1)) <= n; i++)
      for (int j = 1; j + (1 << (k - 1)) <= m; j++)
        st[1][i][j][k] =
          max(max(st[1][i][j][k - 1], st[1][i][j + (1 << (k - 1))][k - 1]),
              max(st[1][i + (1 << (k - 1))][j][k - 1],
                  st[1][i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1]));
  int a, b, c, d;
  for (read(Q); Q--;) {
    scanf("%s", ch), read(a), read(b), read(c), read(d), ++a, ++b, ++c, ++d;
    if (ch[1] == 'U')
      SM(a, b, c, d);
    else
      MX(a, b, c, d, ch[1] == 'A');
  }
  return 0;
}
