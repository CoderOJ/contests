#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int M = 10;
struct Node
{
  std::vector<Node*> next[M + 1];
  std::vector<Node*> back[M + 1];
};

size_t find_match(const std::string& s)
{
  int top = 0;
  for (size_t i = 0; i < s.length(); i++)
  {
    if (s[i] == '(') top++;
    if (s[i] == ')') 
    {
      top--;
      if (top == 0)
        return i;
    }
  }
  assert(false);
}

size_t find_sep(const std::string& s)
{
  int top = 0;
  for (size_t i = 0; i < s.length(); i++)
  {
    if (s[i] == '(') top++;
    if (s[i] == ')') top--;
    if (top == 1 && s[i] == '|')
      return i;
  }
  assert(false);
}

int ans = 0;
Node *build_regex(Node *root, const std::string &s)
{
  if (s.length() == 0)
    return root;
  if (s[0] == '(') 
  {
    size_t r = find_match(s);
    if (r + 1 != s.length() && s[r + 1] == '*')
    {
      Node *ur = build_regex(root, s.substr(1, r - 1));
      ur->next[M].push_back(root);
      root->back[M].push_back(ur);
      return build_regex(ur, s.substr(r + 2));
    }
    else
    {
      size_t sp = find_sep(s);
      Node *ed = new Node();

      Node *ul = new Node();
      root->next[M].push_back(ul);
      ul->back[M].push_back(root);
      Node *el = build_regex(ul, s.substr(1, sp - 1));
      el->next[M].push_back(ed);
      ed->back[M].push_back(el);

      Node *ur = new Node();
      root->next[M].push_back(ur);
      ur->back[M].push_back(root);
      Node *er = build_regex(ur, s.substr(sp + 1, r - sp - 2));
      er->next[M].push_back(ed);
      ed->back[M].push_back(er);

      return build_regex(ed, s.substr(r + 1));
    }
  }

  size_t c = (size_t)(s[0] - 'a');
  Node *ur = new Node();
  root->next[c].push_back(ur);
  ur->back[c].push_back(root);
  return build_regex(ur, s.substr(1));
}

std::set<Node*> vis;
size_t m;
std::string s;

void preInit() { } 
void init() 
{
  std::cin >> m;
  std::cin >> s;
} 

void solve() 
{
  Node *root = new Node();
  Node *end = build_regex(root, s);
  
  int ans = 0;
  std::queue<std::vector<Node*>> st;
  st.push({end});
  vis.insert(end);

  while (!st.empty()) 
  {
    std::vector<Node*> cur = std::move(st.front());
    st.pop();

    for (size_t i = 0; i < cur.size(); i++)
      for (const auto v : cur[i]->back[M])
        if (!vis.count(v))
        {
          cur.push_back(v);
          vis.insert(v);
        }

    for (size_t i = 0; i < m; i++)
    {
      std::vector<Node*> vn;
      for (const auto u: cur)
        for (const auto v: u->back[i])
          if (!vis.count(v))
          {
            vn.push_back(v);
            vis.insert(v);
          }
      if (!vn.empty())
      {
        st.push(vn);
      }
    }
    ans++;
  }

  std::cout << ans - 1 << std::endl;
}
