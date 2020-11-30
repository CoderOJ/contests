#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 100005;
int n, w, h;

void preInit()
{

}

template <class T>
struct queue : private std::vector<T>
{
  using std::vector<T>::begin;
  using std::vector<T>::end;
  int st;
  T& operator [] (const int id) {
    return std::vector<T>::operator[](st+id); } 
  void pop_front() { st++; }
  void push(T a) { std::vector<T>::push_back(a); }
  std::size_t size() { return std::vector<T>::size() - st; }
};

int o[N], p[N], t[N];
std::map<int, queue<int>> que;
std::vector <int> cand;

void init()
{
  n = sc.n(); w = sc.n(); h = sc.n();
  rep (i,n) { 
    o[i] = sc.n(); p[i] = sc.n(), t[i] = sc.n();
    if (o[i] == 2) { cand.push_back(i); }
    else { que[p[i]-t[i]].push(i); } }
  auto pos_cmp = [](int a, int b) -> bool { return p[a] < p[b]; };
  auto pos_cmp_rev = [](int a, int b) -> bool { return p[a] > p[b]; };
  std::sort(cand.begin(), cand.end(), pos_cmp);
  for (auto& i: que) { std::sort(i.second.begin(), i.second.end(), pos_cmp_rev); }
}

int ans_x[N], ans_y[N];
void solve()
{
  for (int i: cand) {
    int bel = p[i] - t[i];
    if (!que.count(bel)) { ans_x[i] = p[i]; ans_y[i] = h; continue; }
    int top = que[bel][0]; que[bel].pop_front();
    ans_x[top] = p[i]; ans_y[top] = h;
    que[bel].push(i); 
  }
  std::vector<int> no_ans_pos;
  rep (i,n) if (o[i] == 1) { no_ans_pos.push_back(i); }
  auto cmp_pos = [](int a, int b) -> bool { return p[a] > p[b]; };
  std::sort(no_ans_pos.begin(), no_ans_pos.end(), cmp_pos);
  for (int i: no_ans_pos) {
    int bel = p[i] - t[i];
    int u = que[bel][0]; que[bel].pop_front();
    ans_x[u] = w; ans_y[u] = p[i]; }
  rep (i,n) printf("%d %d\n", ans_x[i], ans_y[i]);
}
