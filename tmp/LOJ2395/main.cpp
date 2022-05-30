#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstdio>
#include <stack>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 100005, 105)
CONSTRAINT(B, 18, 6)

int a[N];
int l[N][B], r[N][B];
int n, q;

int main()
{
  n = sc.next_int();
  sc.next_int();
  q = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::stack<int> st;
  for (int i = 0; i < n; i++)
  {
    while (!st.empty() && a[st.top()] < a[i])
    {
      r[st.top()][0] = i;
      st.pop();
    }
    if (st.empty())
      l[i][0] = 0;
    else
      l[i][0] = st.top();
    if (!st.empty() && a[st.top()] == a[i])
    {
      r[st.top()][0] = i;
      st.pop();
    }
    st.push(i);
  }
  while (!st.empty())
  {
    r[st.top()][0] = n - 1;
    st.pop();
  }

  for (int b = 0; b + 1 < B; b++)
    for (int i = 0; i < n; i++)
    {
      l[i][b + 1] = std::min(l[l[i][b]][b], l[r[i][b]][b]);
      r[i][b + 1] = std::max(r[l[i][b]][b], r[r[i][b]][b]);
    }

  for (int i = 0; i < q; i++)
  {
    int x = sc.next_int() - 1;
    int y = sc.next_int() - 1;
    if (x > y)
      std::swap(x, y);

    int ans = 0;

    int xl = x, xr = x;
    int yl = y, yr = y;
    for (int i = B - 1; i >= 0; i--)
    {
      int vl = std::min(l[xl][i], l[xr][i]);
      int vr = std::max(r[xl][i], r[xr][i]);
      if (vr < yl)
      {
        ans += (1 << i);
        xl = vl;
        xr = vr;
      }
    }
    for (int i = B - 1; i >= 0; i--)
    {
      int vl = std::min(l[yl][i], l[yr][i]);
      int vr = std::max(r[yl][i], r[yr][i]);
      if (vl > xr)
      {
        ans += (1 << i);
        yl = vl;
        yr = vr;
      }
    }
    
    printf("%d\n", ans);
  }

  return 0;
}