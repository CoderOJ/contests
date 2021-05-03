#include <stdio.h>
#include <assert.h>
#include <string.h>

#define this t

int min(int a, int b)
{
  return a < b ? a : b;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

#define N 100005
#define B 20
#define C 26

int n;

struct edge_t
{
  struct edge_t *next;
  int v;
  char w;
};

struct edge_t *e[N], ep[N * 2], *ep_top = ep;

void add_edge(int u, int v, char c)
{
  ep_top->v    = v;
  ep_top->w    = c;
  ep_top->next = e[u];
  e[u] = ep_top++;
  ep_top->v    = u;
  ep_top->w    = c;
  ep_top->next = e[v];
  e[v] = ep_top++;
}

struct sgt_node_t
{
  struct sgt_node_t *l, *r;
  int sum;
};

struct sgt_node_t sgt_pool[N * 80], *sgt_top = sgt_pool;
int sgt_l, sgt_r;

void sgt_push_up(struct sgt_node_t *this)
{
  this->sum = 0;
  if (this->l) this->sum += this->l->sum;
  if (this->r) this->sum += this->r->sum;
}

void sgt_modify(
  struct sgt_node_t **t, int l, int r, int p, int val)
{
  if (*t == NULL)
    *t = sgt_top++;
  if (r - l == 1)
  {
    (*t)->sum += val;
    return;
  }
  int mid = (l + r) / 2;
  if (p < mid) sgt_modify(&(*t)->l, l, mid, p, val);
  else         sgt_modify(&(*t)->r, mid, r, p, val);
  sgt_push_up(*t);
}

struct sgt_node_t 
*sgt_merge(struct sgt_node_t *l, struct sgt_node_t *r)
{
  if (l == NULL) return r;
  if (r == NULL) return l;
  struct sgt_node_t *u = sgt_top++;
  u->l = sgt_merge(l->l, r->l);
  u->r = sgt_merge(l->r, r->r);
  sgt_push_up(u);
  return u;
}

int sgt_query(const struct sgt_node_t *const pos, 
  int l, int r, int ql, int qr)
{
  if (pos == NULL)
    return 0;
  if (ql <= l && r <= qr)
    return pos->sum;
  int mid = (l + r) / 2;
  int ans = 0;
  if (ql < mid) ans += sgt_query(pos->l, l, mid, ql, qr);
  if (qr > mid) ans += sgt_query(pos->r, mid, r, ql, qr);
  return ans;
}

struct sam_node_t
{
  struct sam_node_t *next[C];
  struct sam_node_t *link;
  struct sgt_node_t *sgt;
  int len;
  int ref_cnt;
};

struct sam_node_t sam_pool[N * 2];
struct sam_node_t *sam_root = sam_pool;
struct sam_node_t *sam_top = sam_pool + 1;
struct sam_node_t *t2sam[N];

struct sam_node_t 
*sam_insert(struct sam_node_t *last, const size_t c)
{
  if (last->next[c])
  {
    struct sam_node_t *const q = last->next[c];
    assert(q->len > last->len);
    if (q->len == last->len + 1)
      return q;
    struct sam_node_t *const clone = sam_top++;
    *clone = *q, clone->len = last->len + 1;
    q->link = clone;
    while (last && last->next[c] == q)
      last->next[c] = clone, last = last->link;
    return clone;
  }
  struct sam_node_t *cur = sam_top++;
  cur->len = last->len + 1;
  struct sam_node_t *pos = last;
  while (pos && pos->next[c] == NULL)
    pos->next[c] = cur, pos = pos->link;
  if (pos == NULL)
    cur->link = sam_root;
  else
  {
    struct sam_node_t *const q = pos->next[c];
    assert(q->len > pos->len);
    if (q->len == pos->len + 1)
      cur->link = q;
    else
    {
      struct sam_node_t *const clone = sam_top++;
      *clone = *q, clone->len = pos->len + 1;
      q->link = cur->link = clone;
      while (pos && pos->next[c] == q)
        pos->next[c] = clone, pos = pos->link;
    }
  }
  return cur;
}

void bfs(int root)
{
  t2sam[root] = sam_root;
  static int que[N];
  int *que_front = que, *que_back = que;
  *que_back++ = root;

  while (que_front != que_back)
  {
    int u = *que_front++;
    for (struct edge_t *i = e[u]; i; i = i->next)
    {
      int v = i->v;
      if (t2sam[v] == NULL)
      {
        t2sam[v] = sam_insert(t2sam[u], (size_t)(i->w - 'a'));
        *que_back++ = v;
      }
    }
  }
}

int dl[N], dr[N], d_top=0;
void get_d(int u, int f)
{
  dl[u] = d_top++;
  for (struct edge_t *i = e[u]; i; i = i->next)
    if (i->v != f) get_d(i->v, u);
  dr[u] = d_top++;
}

void build_sgt()
{
  sgt_l = 0;
  sgt_r = d_top;
  for (int u=1; u<=n; ++u)
  {
    sgt_modify(&t2sam[u]->sgt, sgt_l, sgt_r, dl[u], 1);
    sgt_modify(&t2sam[u]->sgt, sgt_l, sgt_r, dr[u], -1);
  }

  for (struct sam_node_t *i = sam_pool + 1; i < sam_top; ++i)
    i->link->ref_cnt++;
  static struct sam_node_t *topic_que[N * 2];
  struct sam_node_t **que_front = topic_que, **que_back = topic_que;
  for (struct sam_node_t *i = sam_pool + 1; i < sam_top; ++i)
    if (i->ref_cnt == 0) *que_back++ = i;
  while (*que_front != sam_root)
  {
    struct sam_node_t *u = *que_front++;
    /* printf("sgt_merge %p <- %p\n", u->link->sgt, u->sgt); */
    /* printf("sgt_merge len = %d <- %d\n", u->link->len, u->len); */
    u->link->sgt = sgt_merge(u->link->sgt, u->sgt);
    u->link->ref_cnt--;
    if (u->link->ref_cnt == 0)
      *que_back++ = u->link;
  }
}

struct sgt_node_t *get_sgt_node(const char *src)
{
  struct sam_node_t *cur = sam_root;
  while (*src) 
  {
    size_t c = (size_t)(*src - 'a');
    if (cur->next[c] == NULL)
      return NULL;
    cur = cur->next[c];
    src++;
  }
  return cur->sgt;
}

int fa[N][B], dep[N];
char fa_w[N];
void init_lca(int u, int f)
{
  dep[u] = dep[f] + 1;
  fa[u][0] = f;
  for (int i=0; i+1<B; ++i)
    fa[u][i + 1] = fa[fa[u][i]][i];
  for (struct edge_t *i = e[u]; i; i = i->next)
    if (i->v != f) fa_w[i->v] = i->w, init_lca(i->v, u);
}

int get_up(int u, int d)
{
  if (d <= 0)
    return u;
  for (int i=0; i<B; ++i)
    if (d & (1 << i)) u = fa[u][i];
  return u;
}

int lca(int u, int v)
{
  if (dep[u] < dep[v]) 
    return lca(v, u);
  u = get_up(u, dep[u] - dep[v]);
  for (int i=B-1; i>=0; --i)
    if (fa[u][i] != fa[v][i])
      u = fa[u][i], v = fa[v][i];
  return u == v ? u : fa[u][0];
}

char str[N], r_str[N];
char bf_str[N];

int kmp(const char *const src, const char *const pat)
{
  /* printf("kmp(\"%s\", \"%s\")\n", src, pat); */
  static int next[N];
  const char *pat_pos = pat + 1;
  for (int i=1; *pat_pos; i++, pat_pos++)
  {
    int j = next[i - 1];
    while (j > 0 && pat[j] != pat[i])
      j = next[j - 1];
    if (pat[j] == pat[i])
      j++;
    next[i] = j;
  }

  int pos = 0;
  int ans = 0;
  for (const char *i = src; *i; ++i)
  {
    while (pos > 0 && *i != pat[pos])
      pos = next[pos - 1];
    if (*i == pat[pos])
      pos++;
    if (pat[pos] == '\0')
    {
      ans++;
      pos = next[pos - 1];
    }
  }
  return ans;
}

int main()
{
  /* printf("%d\n", kmp("abaabaaabaaaab", "aab")); */

  scanf("%d", &n);
  for (int i=1; i<n; ++i)
  {
    int u, v;
    char c;
    scanf("%d %d %c ", &u, &v, &c);
    add_edge(u, v, c);
  }

  bfs(1);
  get_d(1, 0);
  build_sgt();
  init_lca(1, 0);

  int q;
  scanf("%d", &q);
  for (int i=0; i<q; ++i)
  {
    int u, v;
    scanf("%d %d %s", &u, &v, str);
    int len = (int)strlen(str);
    for (int i=0; i<len; ++i)
      r_str[len - i - 1] = str[i];
    r_str[len] = '\0';

    int ans = 0;
    int l = lca(u, v);
    int du = dep[u] - dep[l];
    int dv = dep[v] - dep[l];

    /* while (u != l) { printf("%d %d %c\n", u, fa[u][0], fa_w[u]); u = fa[u][0]; } */
    /* while (v != l) { printf("%d %d %c\n", v, fa[v][0], fa_w[v]); v = fa[v][0]; } */
    /* return 0; */

    /* printf("l=%d du=%d dv=%d\n", l, du, dv); */
    if (du > len)
      ans += sgt_query(get_sgt_node(r_str), sgt_l, sgt_r,
                       dl[get_up(u, du - len - 1)], dr[u]);
    /* printf("after sam query: ans = %d\n", ans); */
    if (dv > len)
      ans += sgt_query(get_sgt_node(str), sgt_l, sgt_r,
                       dl[get_up(v, dv - len - 1)], dr[v]);

    /* printf("query str: %s %p\n", str, get_sgt_node(str)); */
    /* printf("query %d %d\n", dl[get_up(v, dv - len - 1)], dr[v]); */
    /* printf("after sam query: ans = %d\n", ans); */

    char *bf_str_top = bf_str;
    int bu = get_up(u, du - len);
    int bv = get_up(v, dv - len);
    while (bu != l)
    {
      *bf_str_top++ = fa_w[bu];
      bu = fa[bu][0];
    }
    bf_str_top += min(dv, len);
    *bf_str_top = '\0';
    while (bv != l)
    {
      *--bf_str_top = fa_w[bv];
      bv = fa[bv][0];
    }
    ans += kmp(bf_str, str);
    
    printf("%d\n", ans);
  }

  return 0;
}
