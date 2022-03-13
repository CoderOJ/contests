#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;
constexpr int B = 18;

int cnt[B + 1][1 << (B + 1)];
int len_cnt[B];
int n, q;

int8_t a[N];

void update(int ll, int rr, int d)
{
  check_max(ll, 0);
  check_min(rr, n);

  for (int l = ll; l < rr; l++)
  {
    int cur = 0;
    for (int r = l + 1; r <= std::min(l + B, rr); r++)
    {
      cur = cur << 1 | a[r - 1];
      len_cnt[r - l] -= (cnt[r - l][cur] > 0);
      cnt[r - l][cur] += d;
      len_cnt[r - l] += (cnt[r - l][cur] > 0);
    }
  }
}

int ans()
{
  for (int i = 1; i < B; i++)
    if (len_cnt[i] != (1 << i))
      return i;
  return B;
}

int main()
{
  n = sc.next_int();
  q = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_char() - '0';

  update(0, n, 1);
  std::cout << ans() << std::endl;

  for (int i = 0; i < q; i++)
  {
    int p = sc.next_int() - 1;
    update(p - B, p + B, -1);
    a[p] = !a[p];
    update(p - B, p + B, 1);
    std::cout << ans() << std::endl;
  }

  return 0;
}
