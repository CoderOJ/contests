#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"
#include <cstring>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 10007;
constexpr size_t N = 205;
using int_t =  cm::intm<MOD>;
size_t n, k;
char s[N];

struct matrix_t
{
  static constexpr size_t N = 305;
  int_t a[N][N];

  matrix_t operator* (const matrix_t &rhs) const
  {
    static unsigned long long _res[N][N];
    memset(_res, 0, sizeof(_res));
    for (size_t i = 0; i < N; i++)
      for (size_t k = 0; k <= i; k++)
        for (size_t j = 0; j <= k; j++)
          _res[i][j] += static_cast<int>(a[i][k]) * 
                        static_cast<int>(rhs.a[k][j]);
    matrix_t result;
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        result.a[i][j] = _res[i][j];
    return result;
  }

  matrix_t pow(int k) const
  {
    matrix_t result, cur = *this;
    for (size_t i = 0; i < N; i++)
      result.a[i][i] = 1;
    for (; k; k >>= 1)
    {
      if (k & 1)
        result = result * cur;
      cur = cur * cur;
    }
    return result;
  }
};

int_t path_cnt[N][N][N];

int main()
{
  n = sc.next(s) - s;
  k = sc.next_int();

  for (size_t i = 0; i < n; i++)
  {
    path_cnt[i][i][0] = 1;
    path_cnt[i][i + 1][0] = 1;
  }
  for (size_t i = n - 1; i < n; i--)
    for (size_t j = i + 2; j <= n; j++)
    {
      char s = ::s[i], t = ::s[j - 1];
      see(i, j, s, t);
      if (s == t) {
        for (size_t k = 0; k <= j - i; k++)
          path_cnt[i][j][k] += path_cnt[i + 1][j - 1][k]; }
      else {
        for (size_t k = 0; k < j - i; k++)
          path_cnt[i][j][k + 1] += path_cnt[i + 1][j][k] + path_cnt[i][j - 1][k]; }
      see(path_cnt[i][j][0], path_cnt[i][j][1], path_cnt[i][j][2]);
    }
  
  matrix_t trans;
  const size_t p_s = 0, p_t = (n + 1) / 2 + n - 1;
  for (size_t i = 0; i < (n + 1) / 2; i++)
    trans.a[i][i] = 25;
  for (size_t i = (n + 1) / 2; i < p_t; i++)
    trans.a[i][i] = 24;
  trans.a[p_t][p_t] = 26;
  for (size_t i = 0; i + 1 < (n + 1) / 2; i++)
    trans.a[i + 1][i] = 1;
  for (size_t i = (n + 1) / 2; i < p_t; i++)
    trans.a[i + 1][i] = 1;
  for (size_t i = 0; i < n; i++)
  {
    asee(i, path_cnt[0][n][i]);
    trans.a[p_t - i][(n + 1 - i) / 2 - 1] = path_cnt[0][n][i];
  }

  for (size_t i = 0; i <= p_t; i++)
    see(std::vector<int_t>(trans.a[i], trans.a[i] + p_t + 1));

  int kth = static_cast<int>((n + k + 1) / 2);
  matrix_t init_state;
  init_state.a[p_s][0] = 1;

  auto ans_state = trans.pow(kth) * init_state;
  int_t ans = ans_state.a[p_t][0];

  if ((n + k) % 2 == 1)
  {
    memset(path_cnt, 0, sizeof(path_cnt));
    for (size_t i = 0; i < n; i++)
      path_cnt[i][i][0] = 1;
    for (size_t i = n - 1; i < n; i--)
      for (size_t j = i + 2; j <= n; j++)
      {
        char s = ::s[i], t = ::s[j - 1];
        if (s == t) {
          for (size_t k = 0; k <= j - i; k++)
            path_cnt[i][j][k] = path_cnt[i + 1][j - 1][k]; }
        else {
          for (size_t k = 0; k < j - i; k++)
            path_cnt[i][j][k + 1] = path_cnt[i + 1][j][k] + path_cnt[i][j - 1][k]; }
        see(path_cnt[i][j][0], path_cnt[i][j][1], path_cnt[i][j][2]);
      }

    matrix_t trans;
    const size_t p_s = 0, p_t = (n + 1) / 2 + n - 1;
    for (size_t i = 0; i < (n + 1) / 2; i++)
      trans.a[i][i] = 25;
    for (size_t i = (n + 1) / 2; i < p_t; i++)
      trans.a[i][i] = 24;
    for (size_t i = 0; i + 1 < (n + 1) / 2; i++)
      trans.a[i + 1][i] = 1;
    for (size_t i = (n + 1) / 2; i < p_t; i++)
      trans.a[i + 1][i] = 1;
    for (size_t i = 0; i < n; i++)
    {
      asee(i, path_cnt[0][n][i]);
      trans.a[p_t - i][(n + 1 - i) / 2 - 1] = path_cnt[0][n][i];
    }

    for (size_t i = 0; i <= p_t; i++)
      see(std::vector<int_t>(trans.a[i], trans.a[i] + p_t + 1));

    int kth = static_cast<int>((n + k + 1) / 2);
    matrix_t init_state;
    init_state.a[p_s][0] = 1;

    auto ans_state = trans.pow(kth) * init_state;
    see(ans);
    ans -= ans_state.a[p_t][0];
  }

  std::cout << ans << std::endl;

  return 0;
}

