#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 200005;
const int inf = 0x3f3f3f3f;

int n, a[N], w[N], cnt[N];
char s[N];

struct sgt_t
{
  int maxv[N << 2];
  void pushup(int u)
  {
    maxv[u] = std::max(maxv[u + u], maxv[u + u + 1]);
  }
  void modify(int u, int l, int r, int p, int w)
  {
    if (l == r)
    {
      maxv[u] = w;
      return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
      modify(u + u, l, mid, p, w);
    else
      modify(u + u + 1, mid + 1, r, p, w);
    pushup(u);
  }
  int query(int u, int l, int r, int ql, int qr)
  {
    if (ql <= l && r <= qr)
      return maxv[u];
    int mid = (l + r) >> 1, res = -inf;
    if (ql <= mid)
      res = std::max(res, query(u + u, l, mid, ql, qr));
    if (qr > mid)
      res = std::max(res, query(u + u + 1, mid + 1, r, ql, qr));
    return res;
  }
} odd, even;

bool check(int p, int w)
{
  if (w < 0)
    return 0;
  if (w & 1)
    return odd.query(1, 1, n, p, n) >= w;
  else
    return even.query(1, 1, n, p, n) >= w;
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; ++i)
    a[i] = sc.next_int();
  for (int i = 1, mx = 0; i <= n; ++i)
  {
    if (a[i] > mx)
      w[i] = 2, mx = a[i];
    else
      w[i] = 1;
  }

  memset(odd.maxv, 0xcf, sizeof(odd.maxv));
  for (int i = n; i; i--)
  {
    int mxo = odd.query(1, 1, n, a[i], n), mxe = even.query(1, 1, n, a[i], n);
    if (w[i] & 1)
      odd.modify(1, 1, n, a[i], mxe + w[i]),
          even.modify(1, 1, n, a[i], mxo + w[i]);
    else
      odd.modify(1, 1, n, a[i], mxo + w[i]),
          even.modify(1, 1, n, a[i], mxe + w[i]);
  }
  for (int i = n; i; --i)
    cnt[i] = cnt[i + 1] + w[i] - 1;

  int cx = 0, cy = 0, mxx = 0, mxy = 0;
  for (int i = 1; i <= n; ++i)
  {
    odd.modify(1, 1, n, a[i], -inf), even.modify(1, 1, n, a[i], 0);
    if (check(mxy, cx + (a[i] > mxx) + cnt[i + 1] - cy) ||
        check(std::max(mxx, a[i]), cy + cnt[i + 1] - cx - (a[i] > mxx)))
      s[i] = '0', cx += (a[i] > mxx), mxx = std::max(mxx, a[i]);
    else
      s[i] = '1', cy += (a[i] > mxy), mxy = std::max(mxy, a[i]);
  }

  if (cx != cy)
    puts("-1");
  else
    puts(s + 1);

  return 0;
}
