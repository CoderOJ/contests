#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

using int_t = cm::intm<998244353>;
constexpr int N = 100005;
int a[N], n;
int_t cnt[10];

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  cnt[a[0]] = 1;
  for (int i = 1; i < n; i++)
  {
    see(i, a[i]);
    int_t vcnt[10];
    for (int j = 0; j < 10; j++)
      vcnt[(j + a[i]) % 10] += cnt[j];
    for (int j = 0; j < 10; j++)
      vcnt[(j * a[i]) % 10] += cnt[j];
    std::copy(vcnt, vcnt + 10, cnt);
  }
  for (int i = 0; i < 10; i++)
    std::cout << cnt[i] << std::endl;
  return 0;
}

