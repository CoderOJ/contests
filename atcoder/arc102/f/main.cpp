#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

template <class RandomAcessIterator>
size_t calc_inverse(RandomAcessIterator begin, RandomAcessIterator end)
{
  if (begin + 1 == end)
    return 0;

  RandomAcessIterator mid = std::next(begin, std::distance(begin, end) / 2);

  size_t res = 0;
  res += calc_inverse(begin, mid);
  res += calc_inverse(mid, end);

  RandomAcessIterator mr    = mid;
  size_t              r_cnt = 0;
  for (RandomAcessIterator i = begin; i != mid; i++)
  {
    while (mr != end && *mr < *i)
    {
      mr++;
      r_cnt++;
    }
    res += r_cnt;
  }

  std::inplace_merge(begin, mid, end);

  return res;
}

int main()
{
  int              n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int() - 1;

  for (int i = 0; i < n; i++)
    if (i % 2 != a[i] % 2)
    {
      puts("No");
      return 0;
    }

  std::vector<int> odd;
  std::vector<int> even;
  for (int i = 0; i < n; i++)
    (i % 2 == 1 ? odd : even).push_back(a[i]);

  size_t odd_inv  = calc_inverse(odd.begin(), odd.end());
  size_t even_inv = calc_inverse(even.begin(), even.end());
  size_t all_inv  = calc_inverse(a.begin(), a.end());
  // see(odd_inv, even_inv, all_inv);

  if ((odd_inv + even_inv) * 3 != all_inv)
    puts("No");
  else
    puts("Yes");

  return 0;
}
