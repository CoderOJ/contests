#include <cmath>
#include <ios>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

const double k1 = 1.2;
const double k3 = 2;
const double b  = 0.75;

std::vector<std::string> split(const std::string &s, char dem = ' ')
{
  std::vector<std::string> res;

  std::string cur;
  for (char c : s)
  {
    if (c == dem)
    {
      if (!cur.empty())
      {
        res.emplace_back("");
        std::swap(res.back(), cur);
      }
    }
    else
    {
      cur += c;
    }
  }
  if (!cur.empty())
  {
    res.emplace_back(std::move(cur));
  }
  return res;
}

struct trie_node_t
{
  int next[26];
  int cnt, last;
};

#ifndef CM_DEBUG
const int T = 4200000;
#else
const int T = 1000;
#endif

trie_node_t tr[T];
using index_t = int;

int tr_cur = 1;

int allocate_index()
{
  tr[tr_cur] = trie_node_t();
  return tr_cur++;
}

void trie_insert(index_t u, const char *s, int last_id = -1)
{
  for (; *s; s++)
  {
    int c = *s - 'a';
    if (tr[u].next[c] == 0)
      tr[u].next[c] = allocate_index();
    u = tr[u].next[c];
  }
  if (last_id == -1 || last_id > tr[u].last)
  {
    tr[u].cnt += 1;
    tr[u].last = last_id;
  }
}

index_t build_index(const std::vector<std::string> &sv)
{
  index_t u = allocate_index();
  for (const auto &s : sv)
    trie_insert(u, s.c_str());
  return u;
}

int index_query(index_t u, const std::string &k)
{
  const char *s = k.c_str();
  for (; *s && u; s++)
  {
    int c = *s - 'a';
    u     = tr[u].next[c];
  }
  return tr[u].cnt;
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::cin.get();
  std::vector<std::vector<std::string>> docs_v(n);
  std::vector<index_t>                  docs(n);
  std::vector<int>                      docs_len(n);
  double                                avg_len = 0;

  for (int i = 0; i < n; i++)
  {
    std::string ss;
    std::getline(std::cin, ss);
    auto sv     = split(ss);
    docs[i]     = build_index(sv);
    docs_len[i] = static_cast<int>(sv.size());
    avg_len += docs_len[i];
    docs_v[i] = std::move(sv);
  }
  avg_len /= n;

  std::vector<std::vector<double>>      idfs(m), sds(m), sqs(m);
  std::vector<std::vector<std::string>> svs;

  for (int i = 0; i < m; i++)
  {
    int x;
    std::cin >> x;
    x -= 1;

    std::cin.get();
    std::string ss;
    std::getline(std::cin, ss);
    auto sv = split(ss);
    auto si = build_index(sv);

    const double K = k1 * (1 - b + b * (docs_len[x] / avg_len));

    for (const auto &q : sv)
    {
      // double idf = [&] {
      //   int dfi = 0;
      //   for (int i = 0; i < n; i++)
      //     if (index_query(docs[i], q) > 0)
      //       dfi += 1;
      //   return std::log((n - dfi + 0.5) / (dfi + 0.5));
      // }();
      double sd = [&] {
        int tftd = index_query(docs[x], q);
        return (k1 + 1) * tftd / (K + tftd);
      }();
      double sq = [&] {
        int tftq = index_query(si, q);
        return (k3 + 1) * tftq / (k3 + tftq);
      }();
      sds[i].push_back(sd);
      sqs[i].push_back(sq);
    }

    svs.emplace_back(std::move(sv));
  }

  tr_cur = 1;
  int gu = allocate_index();
  for (int i = 0; i < n; i++)
    for (const auto &s : docs_v[i])
      trie_insert(gu, s.c_str(), i + 1);
  for (int i = 0; i < m; i++)
  {
    for (const auto &q : svs[i])
    {
      double idf = [&] {
        int dfi = index_query(gu, q);
        return std::log((n - dfi + 0.5) / (dfi + 0.5));
      }();
      idfs[i].push_back(idf);
    }
  }

  for (int i = 0; i < m; i++)
  {
    double ans = 0;
    for (size_t j = 0; j < idfs[i].size(); j++)
    {
      // printf("%d %d: %f %f %f\n", i, j, idfs[i][j], sds[i][j], sqs[i][j]);
      ans += idfs[i][j] * sds[i][j] * sqs[i][j];
    }
    printf("%.4f\n", ans);
  }

  return 0;
}