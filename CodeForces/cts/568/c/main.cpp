#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <string>
#define int long long

int n, e[405][405];
void floyd()
{
  for (int k = 1; k <= n + n; k++)
    for (int i = 1; i <= n + n; i++)
      for (int j = 1; j <= n + n; j++)
        e[i][j] |= (e[i][k] && e[k][j]);
}

int acv[405], tcv[405];
int mxp[2], vc[35], nxt[35], nxu[35];
std::string s;

int check(int pos, int now, int x, int id)
{
  int tmp;
  if (acv[pos] != -1 && acv[pos] != vc[now])
    return 0;
  for (int i = 1; i <= n; i++)
    if (e[x][i] && e[x][i + n])
      return 0;

  for (int i = 1; i <= n; i++)
  {
    tcv[i] = -1;
    if (e[x][i])
      tcv[i] = 0;
    if (e[x][i + n])
      tcv[i] = 1;
  }
  if (!id)
  {
    for (int i = 1; i <= n; i++)
    {
      if (pos + i > n)
        break;
      tmp = std::max(tcv[pos + i], acv[pos + i]);
      if (tmp == -1)
        break;
      if (mxp[tmp] < s[pos + i] - 'a' + 1)
        return 0;
      if (mxp[tmp] > s[pos + i] - 'a' + 1)
        break;
    }
  }
  for (int i = 1; i <= n; i++)
    acv[i] = std::max(acv[i], tcv[i]);
  return 1;
}

int ans[405];
signed main()
{
  int len, m, l1, l2, c1, c2, fla;
  char ch1, ch2;
  std::cin >> s;
  len = s.length();
  s = ' ' + s;
  for (int i = 1; i <= len; i++)
    vc[i] = (s[i] == 'C' ? 0 : 1);
  vc[len + 1] = -1; 
  mxp[0] = mxp[1] = -1;
  for (int i = 1; i <= len; i++)
    mxp[vc[i]] = i;

  for (int i = 1; i <= len; i++)
  {
    nxt[i] = 0;
    for (int j = i + 1; j <= len; j++)
      if (vc[i] != vc[j])
      {
        nxt[i] = j;
        break;
      }
  }
  for (int i = 1; i <= len; i++)
  {
    nxu[i] = 0;
    for (int j = i + 1; j <= len; j++)
      if (vc[i] == vc[j])
      {
        nxu[i] = j;
        break;
      }
  }

  memset(acv, -1, sizeof(acv));
  memset(tcv, -1, sizeof(tcv));
  std::cin >> n >> m;
  while (m--)
  {
    std::cin >> l1 >> ch1 >> l2 >> ch2;
    c1 = (ch1 == 'C') ? 0 : 1;
    c2 = (ch2 == 'C') ? 0 : 1;
    e[l1 + c1 * n][l2 + c2 * n] = 1;
    e[l2 + (!c2) * n][l1 + (!c1) * n] = 1;
  }
  floyd();

  std::cin >> s;
  s = ' ' + s;
  fla = 0;
  for (int i = 1; i <= n; i++)
  {
    int mi = fla ? 1 : s[i] - 'a' + 1;
    if (check(i, mi, i + vc[mi] * n, fla))
      ans[i] = mi;
    else if (vc[mi] == vc[mi + 1] && check(i, mi + 1, i + vc[mi + 1] * n, 1))
      ans[i] = mi + 1, fla = 1;
    else if (nxt[mi] && check(i, nxt[mi], i + vc[nxt[mi]] * n, 1))
      ans[i] = nxt[mi], fla = 1;
    else if (nxu[mi] > nxt[mi] && nxu[mi] && check(i, nxu[mi], i + vc[nxu[mi]] * n, 1))
      ans[i] = nxu[mi], fla = 1;
    else
    {
      std::cout << -1 << '\n';
      return 0;
    }
  }

  for (int i = 1; i <= n; i++)
    putchar(static_cast<signed>(ans[i] + 'a' - 1));
  return 0;

}
