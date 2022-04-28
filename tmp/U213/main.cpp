#include <bits/stdc++.h>

const int N = 1000005;
int a[N], n;
int pre[N], suf[N];
std::stack<int> st;

int64_t ans[N];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);

  for (int i = 0; i < n; i++)
  {
    while (!st.empty() && a[st.top()] <= a[i])
    {
      suf[st.top()] = i;
      st.pop();
    }
    if (st.empty())
      pre[i] = -1;
    else
      pre[i] = st.top();
    st.push(i);
  }
  while (!st.empty())
  {
    suf[st.top()] = n;
    st.pop();
  }

  for (int i = 0; i < n; i++)
  {
    int lp = i - pre[i], rp = suf[i] - i;
    // printf("i = %d: lp = %d, rp = %d\n", i, lp, rp);
    if (lp > rp) std::swap(lp, rp);
    ans[1] += a[i];
    ans[1 + lp] -= a[i];
    ans[1 + rp] -= a[i];
    ans[1 + lp + rp] += a[i];
  }

  std::partial_sum(ans + 1, ans + n + 1, ans + 1);
  std::partial_sum(ans + 1, ans + n + 1, ans + 1);

  int64_t o = 0;
  for (int i = 1; i <= n; i++)
  {
    // printf("ans[%d] = %ld\n", i, ans[i]);
    o ^= (ans[i] % 998244353);
  }
  printf("%" SCNi64 "\n", o);

  return 0;
}
