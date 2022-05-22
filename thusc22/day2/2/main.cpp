#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int m, n;
  std::cin >> m >> n;

  std::vector<std::string> init(n);
  for (int i = 0; i < n; i++)
    std::cin >> init[i];
  std::cin.get();

  std::vector<std::string>              id_url(m);
  std::map<std::string, int>            url_id;
  std::vector<std::vector<std::string>> e_url(m);
  for (int i = 0; i < m; i++)
  {
    std::string url;
    std::getline(std::cin, url, ',');
    id_url[i] = url;
    url_id.emplace(url, i);

    std::string ss;
    std::getline(std::cin, ss);

    e_url[i].push_back("");
    for (char c : ss)
    {
      if (c == ' ')
        e_url[i].push_back("");
      else
        e_url[i].back() += c;
    }
    if (e_url[i].back() == "")
      e_url[i].pop_back();
  }

  std::vector<std::vector<int>> e(m);
  for (int i = 0; i < m; i++)
    for (const auto &s : e_url[i])
      e[i].push_back(url_id[s]);

  std::vector<std::stack<int>> st(n);
  for (int i = 0; i < n; i++)
    st[i].push(url_id[init[i]]);

  std::vector<bool> vis(m, false);

  std::vector<std::vector<int>> ans(n);

  while (true)
  {
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
      int top = [&] {
        while (!st[i].empty() && vis[st[i].top()])
          st[i].pop();
        if (st[i].empty())
          return -1;
        else
          return st[i].top();
      }();

      if (top != -1)
      {
        flag = true;
        ans[i].push_back(top);
        vis[top] = true;
        st[i].pop();
        for (int v : e[top])
          st[i].push(v);
      }
    }
    if (!flag)
      break;
  }

  for (int i = 0; i < n; i++)
  {
    bool first = true;
    for (int id : ans[i])
    {
      if (!first)
        std::cout << ',';
      else
        first = false;
      std::cout << id_url[id];
    }
    std::cout << '\n';
  }

  return 0;
}