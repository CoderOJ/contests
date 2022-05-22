#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

std::string read_lines()
{
  std::string r;
  int         c = getchar();
  while (c != EOF)
  {
    r += static_cast<char>(c);
    c = getchar();
  }
  return r;
}

using token_t      = std::string;
using token_list_t = std::vector<token_t>;

token_list_t tokenlize(const std::string &s)
{
  token_list_t res = {""};
  for (char c : s)
  {
    if (c == '<' && !res.back().empty())
      res.push_back("");
    res.back() += c;
    if (c == '>')
      res.push_back("");
  }
  return res;
}

std::string wrap_string(const std::string &s)
{
  std::string r;
  r += '"';
  for (char c : s)
  {
    if (c == '\n')
      r += "\\n";
    else
      r += c;
  }
  r += '"';
  return r;
}

bool is_tag(const token_t &t)
{
  return !t.empty() && t.front() == '<' && t.back() == '>';
}

bool is_tagchar(char c)
{
  return std::isalpha(c) || std::isdigit(c) || c == '/';
}

std::string get_tagname(const token_t &t)
{
  std::string r = "";
  for (auto it = t.begin() + 1; is_tagchar(*it); it++)
    r += *it;
  return r;
}

bool is_invisible(char c)
{
  return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

bool is_invisible_tag(const std::string &t)
{
  return t == "style" || t == "script" || t == "img";
}

bool is_selfclosing(const std::string &t)
{
  return t == "img";
}

std::string trim(const std::string &s)
{
  auto l = s.begin(), r = s.end();
  while (l != r && is_invisible(*l))
    l++;
  while (l != r && is_invisible(*std::prev(r)))
    r--;
  return {l, r};
}

void dump_env(const std::vector<std::string> &env)
{
  bool first = true;
  for (const auto &t : env)
  {
    if (!first)
      std::cout << '>';
    else
      first = false;
    std::cout << t;
  }
}

void dump(const std::vector<std::string> &env, const token_t &text)
{
  auto t = trim(text);
  if (!t.empty() && std::none_of(env.begin(), env.end(), is_invisible_tag))
  {
    dump_env(env);
    std::cout << ':' << t << '\n';
  }
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cout.tie(nullptr);

  auto s      = read_lines();
  auto tokens = tokenlize(s);

  std::vector<std::string> env;
  for (const auto &t : tokens)
  {
    if (is_tag(t))
    {
      auto tagname = get_tagname(t);
      if (!is_selfclosing(tagname))
      {
        if (tagname[0] == '/')
        {
          if (tagname != "/img")
            env.pop_back();
        }
        else
        {
          env.push_back(tagname);
        }
      }
    }
    else
    {
      dump(env, t);
    }
  }

  return 0;
}
