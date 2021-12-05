#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/lambda"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/string"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
#include <string_view>
#include <type_traits>

template <typename BidirectionalIterator, typename Predicate>
bool is_palindrome(BidirectionalIterator begin,
                   BidirectionalIterator end,
                   Predicate             p)
{
  if (begin == end)
  {
    return true;
  }

  --end;
  while (begin != end)
  {
    if (!p(*begin, *end))
    {
      return false;
    }
    ++begin;
    if (begin == end)
    {
      break;
    }
    --end;
  }
  return true;
}
template <typename BidirectionalIterator>
bool is_palindrome(BidirectionalIterator begin, BidirectionalIterator end)
{
  using namespace lambda::placehoders;
  return is_palindrome(begin, end, _0 == _1);
}

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
constexpr int N   = 2005;
using int_t       = cm::intm<MOD>;

char s[2][N], t[N];
int  n, k;

int_t cnt[N][2], cur[N][2];

int main()
{
  n = static_cast<int>(sc.next_token(s[0]) - s[0]);
  n = static_cast<int>(sc.next_token(s[1]) - s[1]);
  k = static_cast<int>(sc.next_token(t) - t);
  cm::string::hash_u64<2333333> hs[2]{{s[0], s[0] + n}, {s[1], s[1] + n}};

  if (k == 1)
  {
    int_t ans = 0;
    for (int i = 0; i < n; i++)
      ans += (s[0][i] == t[0]) + (s[1][i] == t[0]);
    std::cout << ans << std::endl;
  }
  else if (k == 2)
  {
    int_t ans = 0;
    for (int i = 0; i < n; i++)
    {
      if (s[0][i] == t[0] && s[1][i] == t[1])
        ans += 1;
      if (s[1][i] == t[0] && s[0][i] == t[1])
        ans += 1;
    }
    for (int i = 0; i + 1 < n; i++)
    {
      if (s[0][i] == t[0] && s[0][i + 1] == t[1])
        ans += 1;
      if (s[0][i] == t[1] && s[0][i + 1] == t[0])
        ans += 1;
      if (s[1][i] == t[0] && s[1][i + 1] == t[1])
        ans += 1;
      if (s[1][i] == t[1] && s[1][i + 1] == t[0])
        ans += 1;
    }
    std::cout << ans << std::endl;
  }
  else
  {

    auto calc = [&]() -> int_t {
      std::string_view              vt(t, k);
      cm::string::hash_u64<2333333> ht(vt.begin(), vt.end());
      cm::string::hash_u64<2333333> htr(vt.rbegin(), vt.rend());

      int_t ans = 0;
      memset(cnt, 0, sizeof(cnt));

      for (int i = 0; i <= n; i++)
      {
        memset(cur, 0, sizeof(cur));
        cur[0][0] += 1;
        cur[0][1] += 1;
        for (int j = 2; j <= i && j * 2 <= k; j++)
        {
          if (ht.get_hash(j, j + j) == hs[0].get_hash(i - j, i) &&
              htr.get_hash(k - j, k) == hs[1].get_hash(i - j, i))
            cur[j * 2][0] += 1;
          if (ht.get_hash(j, j + j) == hs[1].get_hash(i - j, i) &&
              htr.get_hash(k - j, k) == hs[0].get_hash(i - j, i))
            cur[j * 2][1] += 1;
        }
        for (int j = 0; j + 1 <= k && j <= 2 * (i - 1); j++)
        {
          if (s[0][i - 1] == t[j])
            cur[j + 1][0] += cnt[j][0];
          if (s[1][i - 1] == t[j])
            cur[j + 1][1] += cnt[j][1];
        }
        for (int j = 0; j + 2 <= k && j <= 2 * (i - 1); j++)
        {
          if (s[0][i - 1] == t[j] && s[1][i - 1] == t[j + 1])
            cur[j + 2][1] += cnt[j][0];
          if (s[1][i - 1] == t[j] && s[0][i - 1] == t[j + 1])
            cur[j + 2][0] += cnt[j][1];
        }

        ans += cur[k][0];
        ans += cur[k][1];
        for (int j = 2; i + j <= n && j * 2 <= k; j++)
        {
          if (ht.get_hash(k - j - j, k - j) == hs[0].get_hash(i, i + j) &&
              htr.get_hash(0, j) == hs[1].get_hash(i, i + j))
            ans += cur[k - j * 2][0];
          if (ht.get_hash(k - j - j, k - j) == hs[1].get_hash(i, i + j) &&
              htr.get_hash(0, j) == hs[0].get_hash(i, i + j))
            ans += cur[k - j * 2][1];
        }

        see(i, ans);
        memcpy(cnt, cur, sizeof(cnt));
      }

      return ans;
    };

    auto calc_same = [&]() -> int_t {
      if (k % 2 == 1)
        return 0;

      std::string_view              vt(t, k);
      cm::string::hash_u64<2333333> ht(vt.begin(), vt.end());
      cm::string::hash_u64<2333333> htr(vt.rbegin(), vt.rend());

      int_t ans = 0;
      for (int i = 0; i + k / 2 <= n; i++)
      {
        int j = k / 2;
        if (ht.get_hash(k - j - j, k - j) == hs[0].get_hash(i, i + j) &&
            htr.get_hash(0, j) == hs[1].get_hash(i, i + j))
          ans += 1;
        if (ht.get_hash(k - j - j, k - j) == hs[1].get_hash(i, i + j) &&
            htr.get_hash(0, j) == hs[0].get_hash(i, i + j))
          ans += 1;
      }
      for (int i = k / 2; i <= n; i++)
      {
        int j = k / 2;
        if (ht.get_hash(j, j + j) == hs[0].get_hash(i - j, i) &&
            htr.get_hash(k - j, k) == hs[1].get_hash(i - j, i))
          ans += 1;
        if (ht.get_hash(j, j + j) == hs[1].get_hash(i - j, i) &&
            htr.get_hash(k - j, k) == hs[0].get_hash(i - j, i))
          ans += 1;
      }
      return ans;
    };

    int_t ans = calc();
    std::reverse(t, t + k);
    ans += calc();
    ans -= calc_same();
    std::cout << ans << std::endl;
  }

  return 0;
}
