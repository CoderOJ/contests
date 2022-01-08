#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 400005;

int       n, l, tot;
int       a[N], now[N], pres[N], pre[N];
int       val[N], v_l[N], v_r[N], sum_l[N], sum_r[N];
long long ans;

struct set_cmp_f
{
  bool operator()(int a, int b) const
  {
    if (val[a] != val[b])
      return val[a] < val[b];
    return v_l[a] < v_l[b];
  }
};

std::set<int, set_cmp_f> poss;

int main()
{
  n = sc.next_int();
  l = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    a[i] = sc.next_int();
    tot++;
    v_l[tot]   = i;
    v_r[tot]   = i;
    val[tot]   = a[i];
    sum_l[tot] = 1;
    sum_r[tot] = 1;
    poss.insert(tot);
  }

  while (!poss.empty())
  {
    int len    = 0;
    now[++len] = *poss.begin();
    poss.erase(poss.begin());

    while (!poss.empty() && val[*poss.begin()] == val[now[1]] &&
           v_l[*poss.begin()] == v_r[now[len]] + 1)
    {
      now[++len] = *poss.begin();
      poss.erase(poss.begin());
    }
    pre[0] = 0;
    for (int i = 1; i <= len; i++)
      pre[i] = pre[i - 1] + sum_l[now[i]];

    for (int i = 1; i <= len; i++)
    {
      ans += (long long)sum_l[now[i]] * sum_r[now[i]];
      if (i - l + 1 >= 1)
        ans += (long long)sum_r[now[i]] * pre[i - l + 1];
    }

    int nlen = 0, last = 0;
    for (int i = 1; i <= len / l; i++)
    {
      int tmpl = (i - 1) * l + 1, tmpr = i * l;
      if (i == len / l)
        tmpr = len;
      tot++;
      v_l[tot] = v_l[now[tmpl]];
      v_r[tot] = v_r[now[tmpr]];
      val[tot] = val[now[1]] + 1;
      for (int j = i * l; j <= (i + 1) * l - 1 && j <= len; j++)
        sum_r[tot] += sum_r[now[j]];
      sum_l[tot] = pre[len % l + 1 + (i - 1) * l] - pre[last];
      last       = len % l + 1 + (i - 1) * l;
      poss.insert(tot);
      pres[++nlen] = tot;
    }
    pre[0] = 0;
    for (int i = 1; i <= nlen; i++)
      pre[i] = pre[i - 1] + sum_l[pres[i]];

    for (int i = 1; i <= nlen; i++)
    {
      ans -= (long long)sum_l[pres[i]] * sum_r[pres[i]];
      if (i - l + 1 >= 1)
        ans -= (long long)sum_r[pres[i]] * pre[i - l + 1];
    }
  }
  printf("%lld\n", ans);
}
