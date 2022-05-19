#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <map>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct ngt_set
{
  std::multiset<int> st;
  int                cnt = 0;
  int                sum = 0;
  int                thr;

  ngt_set(int thr) : thr(thr) {}

  void insert(int x)
  {
    cnt += 1;
    sum += x;
    st.insert(x);
    while (sum > thr)
    {
      auto it = std::prev(st.end());
      cnt -= 1;
      sum -= *it;
      st.erase(it);
    }
  }

  int count()
  {
    return cnt;
  }
};

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    std::map<int, int> cnt;
    for (int i = 0; i < n; i++)
      cnt[a[i]] += 1;

    std::vector<int> emp_cnt(n + 1);
    {
      ngt_set st(k);
      int     all_cnt = 0;
      for (const auto &[k, v] : cnt)
        if (k >= n)
        {
          all_cnt += 1;
          st.insert(v);
        }

      emp_cnt[n] = all_cnt - st.count();
      for (int i = n - 1; i >= 0; i--)
      {
        if (cnt.count(i))
        {
          all_cnt += 1;
          st.insert(cnt[i]);
        }
        emp_cnt[i] = all_cnt - st.count();
      }
    }

    std::vector<int> hole_cnt(n + 1);
    {
      hole_cnt[0] = 0;
      for (int i = 0; i < n; i++)
        hole_cnt[i + 1] = hole_cnt[i] + !cnt.count(i);
    }

    int ans = n;
    for (int i = 0; i <= n; i++)
      if (hole_cnt[i] <= k)
        check_min(ans, (i + emp_cnt[i]) - i);

    printf("%d\n", ans);
  }
  return 0;
}
