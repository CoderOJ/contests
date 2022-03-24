#include <bits/stdc++.h>

int main()
{
  int t; std::cin >> t;
  for (int i = 0; i < t; i++)
  {
    size_t n; std::cin >> n;
    std::vector<int> a(n);
    for (size_t i = 0; i < n; i++) std::cin >> a[i];

    std::reverse(a.begin(), a.end());
    std::vector<size_t> a_min_id(n);
    a_min_id[0] = 0;
    for (size_t i = 1; i < n; i++)
      a_min_id[i] = a[i] <= a[a_min_id[i - 1]] ? i : a_min_id[i - 1];

    std::deque<int> stack;
    std::vector<int> answer;

    while (!a.empty())
    {
      if (stack.empty())
      {
        stack.push_back(a.back());
        a.pop_back(); a_min_id.pop_back();
      }
      else
      {
        int sl = stack.front();
        int sr = stack.back();
        int sa = a[a_min_id.back()];
        if (sl <= sr && sl <= sa)
        {
          answer.push_back(sl);
          stack.pop_front();
        }
        else if (sr <= sl && sr <= sa)
        {
          answer.push_back(sr);
          stack.pop_back();
        }
        else
        {
          stack.push_back(a.back());
          a.pop_back(); a_min_id.pop_back();
        }
      }
    }
    while (!stack.empty())
    {
      int sl = stack.front();
      int sr = stack.back();
      if (sl <= sr)
      {
        answer.push_back(sl);
        stack.pop_front();
      }
      else
      {
        answer.push_back(sr);
        stack.pop_back();
      }
    }
    for (int x : answer)
      std::cout << x << " ";
    std::cout << std::endl;
  }
  return 0;
}
