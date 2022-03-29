#include <bits/stdc++.h>

template <class T> bool check_min(T &a, const T b) { return a > b ? a = b, true : false; }
template <class T> bool check_max(T &a, const T b) { return a < b ? a = b, true : false; }

const int N = 305;
const int M = 1005;
int n, m;

struct item_t
{
  int c;
  int w;
};

item_t a[N];
int ta, tb;

int f(int x)
{
  return x / ta + x / tb;
}

int _dp[2][N][M];
int (*dp[N])[M];
int ans[M];

int main()
{
  scanf("%d%d", &n, &m); scanf("%d%d", &ta, &tb);
  for (int i = 0; i < n; i++) scanf("%d", &a[i].w);
  for (int i = 0; i < n; i++) scanf("%d", &a[i].c);
  std::sort(a, a + n, [](item_t a, item_t b) { return a.c < b.c; });
  for (int i = 0; i <= n; i++) dp[i] = _dp[i % 2];
  memset(dp[0], 0xcf, sizeof(_dp[0]));
  dp[0][0][0] = 0;
  for (int i = 0; i < n; i++)
  {
    memcpy(dp[i + 1], dp[i], sizeof(_dp[0]));
    dp[i + 1][0][0] = 0;
    for (int j = 0; j <= i; j++)
      for (int k = 0; k + a[i].c <= m; k++)
        check_max(dp[i + 1][j + 1][k + a[i].c], dp[i][j][k] + a[i].w);

    std::vector<int> extras;
    for (int j = i + 1; j < n; j++) extras.push_back(a[j].w);
    std::sort(extras.begin(), extras.end(), std::greater<int>());
    while ((int)extras.size() <= n * 2) extras.push_back(0);
    extras.insert(extras.begin(), 0);
    std::partial_sum(extras.begin(), extras.end(), extras.begin());

    for (int j = 0; j <= i + 1; j++)
      for (int k = 0; k <= m; k++)
        check_max(ans[k], dp[i + 1][j][k] + extras[f(j)]);
  }

  for (int i = 1; i <= m; i++)
  {
    check_max(ans[i], ans[i - 1]);
    printf("%d ", ans[i]);
  }
  puts("");

  return 0;
}
