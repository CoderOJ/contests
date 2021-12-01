#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#define rep(i, n) for (int i = 0; i < n; i++)

#ifdef CM_DEBUG
cm::scanner<cm::optimal_reader> sc(stdin);
FILE *                          out = stdout;
#else
cm::scanner<cm::optimal_reader> sc(fopen("ball.in", "r"));
FILE *                          out = fopen("ball.out", "w");
#endif

constexpr int    N = 55;
std::vector<int> a[N];
bool             done[N];
int              n, m;

std::vector<std::pair<int, int>> ops;

void move(int s, int t)
{
  see(s, t);

  cm_assert(s != t);
  cm_assert(!a[s].empty());
  cm_assert(static_cast<int>(a[t].size()) < m);

  ops.emplace_back(s, t);
  a[t].push_back(a[s].back());
  a[s].pop_back();
}

int count(int id, int val)
{
  int res = 0;
  for (int x : a[id])
    if (x == val)
      res++;
  return res;
}

std::tuple<int, int, int> popup(int ha, int ht, int he, int val)
{
  cm_assert(static_cast<int>(a[ha].size()) == m);
  cm_assert(static_cast<int>(a[ht].size()) == m);
  cm_assert(a[he].empty());

  int ca = count(ha, val);
  rep(i, ca) move(ht, he);
  rep(i, m)
  {
    if (a[ha].back() == val)
      move(ha, ht);
    else
      move(ha, he);
  }
  return std::make_tuple(ht, he, ha);
}

void popup_gaurd(int ha, int ht, int he, int val)
{
  see("popup_gaurd", ha, ht, he, val);
  cm_assert(static_cast<int>(a[ha].size()) == m);
  cm_assert(static_cast<int>(a[ht].size()) == m);
  cm_assert(a[he].empty());

  int ca = count(ha, val);
  rep(i, ca) move(ht, he);
  rep(i, m)
  {
    if (a[ha].back() == val)
      move(ha, ht);
    else
      move(ha, he);
  }
  rep(i, m - ca) move(he, ha);
  rep(i, ca) move(ht, ha);
  rep(i, ca) move(he, ht);
}

int make_trash(int ha, int hb, int he, int val)
{
  cm_assert(static_cast<int>(a[ha].size()) == m);
  cm_assert(static_cast<int>(a[hb].size()) == m);
  cm_assert(a[he].empty());

  popup_gaurd(ha, hb, he, val);
  popup_gaurd(hb, ha, he, val);
  int ca = count(ha, val);
  int cb = count(hb, val);
  rep(i, ca) move(ha, he);
  rep(i, cb) move(hb, he);
  rep(i, ca) move(hb, ha);
  rep(i, ca + cb) move(he, hb);
  return ha;
}

int gen_trash(int val, int he)
{
  see("gen_trash", val, he);
  std::vector<int> val_ids;
  for (int i = 0; i <= n; i++)
    if (!done[i] && i != he)
    {
      if (count(i, val) > 0)
        val_ids.emplace_back(i);
      else
      {
        see("using existing trash", i);
        return i;
      }
    }

  cm_assert(val_ids.size() >= 2);
  int ha = val_ids[0], hb = val_ids[1];
  see("make trash", ha, hb);
  return make_trash(ha, hb, he, val);
}

void gather(int val, int he)
{
  for (int i = 0; i <= n; i++)
    if (i != he)
      while (!a[i].empty() && a[i].back() == val)
        move(i, he);
}

int make_empty()
{
  int he = -1;
  for (int i = 0; i <= n; i++)
    if (!done[i])
      he = i;

  cm_assert(he != -1);

  for (int i = 0; i <= n; i++)
    if (!done[i] && i != he)
      while (static_cast<int>(a[i].size()) < m)
        move(he, i);

  cm_assert(a[he].empty());
  return he;
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i].push_back(sc.next_int());

  for (int c = 1; c < n; c++)
  {
    see("round", c);
    int he = make_empty();
    see("initial", he);
    int ht = gen_trash(c, he);
    see("initial", ht);
    for (int i = 0; i <= n; i++)
      if (i != ht && i != he && !done[i])
      {
        int ha               = i;
        std::tie(ha, ht, he) = popup(ha, ht, he, c);
      }
    gather(c, he);
    done[he] = true;
  }

  fprintf(out, "%zu\n", ops.size());
  for (const auto &[x, y] : ops)
    fprintf(out, "%d %d\n", x + 1, y + 1);

  return 0;
}
