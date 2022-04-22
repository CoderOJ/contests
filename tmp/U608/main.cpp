#include <bits/stdc++.h>

const int N = 100005;
const int C = 26;

struct sam_t
{
  struct node_t
  {
    int next[C], link = -1, len = 0;
    node_t() { memset(next, -1, sizeof(next)); }
  };

  node_t p[N * 2];
  static const int root = 0;
  int last = root, cnt = root + 1;

  int extend(size_t c)
  {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    for (; pos != -1 && p[pos].next[c] == -1; pos = p[pos].link)
      p[pos].next[c] = cur;
    if (pos == -1)
      p[cur].link = root;
    else
    {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1)
        p[cur].link = q;
      else
      {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[q].link = p[cur].link = clone;
        for (; pos != -1 && p[pos].next[c] == q; pos = p[pos].link)
          p[pos].next[c] = clone;
      }
    }
    last = cur;
    return cur;
  }
};

struct node_t
{
  node_t *f = nullptr, *s[2] = {nullptr, nullptr};
  int val = -1, assign = -1;

  bool is_root() const
  {
    return f == nullptr || (f->s[0] != this && f->s[1] != this);
  }

  bool get_son() const
  {
    return f->s[1] == this;
  }

  void push_assign(int v)
  {
    val = v;
    assign = v;
  }

  void push_down()
  {
    if (assign != -1)
    {
      if (s[0]) s[0]->push_assign(assign);
      if (s[1]) s[1]->push_assign(assign);
      assign = -1;
    }
  }

  void push()
  {
    if (!is_root())
      f->push();
    push_down();
  }

  void rotate()
  {
    node_t *uu = this, *ff = uu->f, *aa = ff->f;
    const bool ss = uu->get_son();
    if (!ff->is_root()) aa->s[ff->get_son()] = uu;
    ff->f = uu, ff->s[ss] = uu->s[!ss];
    uu->f = aa, uu->s[!ss] = ff;
    if (ff->s[ss]) ff->s[ss]->f = ff;
  }

  void splay()
  {
    push();
    while (!is_root())
    {
      if (f->is_root())
      {
        rotate();
        break;
      }
      else
      {
        if (get_son() == f->get_son())
          f->rotate();
        else
          rotate();
        rotate();
      }
    }
  }

  void access(int);
};

struct query_t
{
  int l, r, id;
  int ans;
};

int n, q;
char s[N];
query_t qs[N];

sam_t sam;
node_t p[N * 2];
int sp[N];

int b0[N], b1[N];
void check_max(int l, int v)
{
  for (int p = l + 2; p > 0; p -= p & -p)
    b0[p] = std::max(b0[p], v);
  for (int p = l + 2; p < N; p += p & -p)
    b1[p] = std::max(b1[p], l + v);
}
int query_max(int l)
{
  int res = 0;
  for (int p = l + 2; p < N; p += p & -p)
    res = std::max(res, b0[p]);
  for (int p = l + 2; p > 0; p -= p & -p)
    res = std::max(res, b1[p] - l);
  return res;
}

void node_t::access(int x)
{
  node_t *uu = this, *ss = nullptr;
  for (; uu; ss = uu, uu = uu->f)
  {
    uu->splay();
    uu->s[1] = nullptr;

    if (uu->val != -1)
    {
      int up = static_cast<int>(uu - p);
      int ul = sam.p[up].len;
      // printf("u_pos, ul = %d, %d\n", uu->val, ul);
      check_max(uu->val - ul + 1, ul);
    }

    uu->push_assign(x);
    uu->push_down();
    uu->s[1] = ss;
  }
}

int main()
{
  scanf("%d%d", &n, &q);
  scanf("%s", s);
  for (int i = 0; i < n; i++)
    sp[i] = sam.extend(s[i] - 'a');
  for (int i = 1; i < sam.cnt; i++)
    p[i].f = &p[sam.p[i].link];

  for (int i = 0; i < q; i++)
  {
    qs[i].id = i;
    scanf("%d%d", &qs[i].l, &qs[i].r);
    qs[i].l--;
  }

  std::sort(qs, qs + q, [](query_t x, query_t y) {
    return x.r < y.r;
  });
  query_t *qi = qs;
  for (int r = 0; r < n; )
  {
    // printf("c = %d\n", r);
    p[sp[r]].access(r);
    r += 1;
    for (; qi != qs + q && qi->r == r; qi++)
      qi->ans = (qi->r - qi->l) - query_max(qi->l);
  }

  std::sort(qs, qs + q, [](query_t x, query_t y) {
    return x.id < y.id;
  });
  for (int i = 0; i < q; i++)
    printf("%d\n", qs[i].ans);

  return 0;
}
