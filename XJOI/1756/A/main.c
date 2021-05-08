#include <stdio.h>
#include <string.h>
#include <stdbool.h>


long long max(long long a, long long b)
{
  return a > b ? a : b;
}

#define N 500005
#define C 26

struct lct_node_t
{
  struct lct_node_t *f, *s[2];
  long long  max, val;
};

struct lct_node_t t[N * 2];
struct lct_node_t null_val, *null = &null_val;

bool is_root(const struct lct_node_t *const this)
{
  return this->f == null || 
         (this->f->s[0] != this && this->f->s[1] != this);
}

bool get_son(const struct lct_node_t *const this)
{
  return this->f->s[1] == this;
}

void push_up(struct lct_node_t *const this)
{
  this->max = max(this->val, max(this->s[0]->max, this->s[1]->max));
}

void rotate(struct lct_node_t *const uu)
{
  struct lct_node_t *const ff=uu->f, *const aa=ff->f;
  bool const ss = get_son(uu);
  if (!is_root(ff)) aa->s[get_son(ff)] = uu;
  ff->f = uu, ff->s[ss] = uu->s[!ss];
  uu->f = aa; uu->s[!ss] = ff;
  ff->s[ss]->f = ff;
  push_up(ff);
}

void splay(struct lct_node_t *this)
{
  while (!is_root(this))
  {
    if (is_root(this->f)) 
    {
      rotate(this);
      break;
    }
    rotate(get_son(this) == get_son(this->f) ? this->f : this);
    rotate(this);
  }
  push_up(this);
}

void access(struct lct_node_t *uu)
{
  struct lct_node_t *ss = null;
  while (uu != null)
  {
    splay(uu);
    uu->s[1] = ss;
    push_up(uu);
    ss = uu, uu = uu->f;
  }
}


struct sam_node_t
{
  int next[C];
  int link, len;
};

struct sam_node_t p[N * 2];

#define sam_root 1
int sam_last = sam_root, sam_cnt = sam_root + 1;

void sam_reset()
{
  sam_last = sam_root;
}

void sam_insert(size_t c)
{
  if (p[sam_last].next[c])
  {
    int q = p[sam_last].next[c];
    if (p[q].len == p[sam_last].len + 1)
      sam_last = q;
    else 
    {
      int clone = sam_cnt++;
      p[clone] = p[q], p[clone].len = p[sam_last].len + 1;
      p[q].link = clone;
      while (sam_last && p[sam_last].next[c] == q)
        p[sam_last].next[c] = clone, sam_last = p[sam_last].link;
      sam_last = clone;
    }
    return;
  }
  int cur = sam_cnt++;
  p[cur].len = p[sam_last].len + 1;
  int pos = sam_last;
  while (pos && p[pos].next[c] == 0)
    p[pos].next[c] = cur, pos = p[pos].link;
  if (pos == 0)
    p[cur].link = sam_root;
  else
  {
    int q = p[pos].next[c];
    if (p[q].len == p[pos].len + 1)
      p[cur].link = q;
    else 
    {
      int clone = sam_cnt++;
      p[clone] = p[q], p[clone].len = p[pos].len + 1;
      p[q].link = p[cur].link = clone;
      while (pos && p[pos].next[c] == q)
        p[pos].next[c] = clone, pos = p[pos].link;
    }
  }
  sam_last = cur;
}

char s[N * 2];
char *str[N];
int val[N], n;

int main()
{
  for (int i=0; i<N * 2; ++i)
    t[i].f = t[i].s[0] = t[i].s[1] = null;

  str[0] = s;
  scanf("%d", &n);
  for (int i=0; i<n; ++i)
  {
    sam_reset();
    scanf("%s%d", str[i], &val[i]);
    str[i + 1] = str[i] + strlen(str[i]);
    for (char *j = str[i]; j < str[i + 1]; ++j)
      sam_insert((size_t)(*j - 'a'));
  }

  for (int i=1; i<sam_cnt; ++i)
    t[i].f = &t[p[i].link];

  long long ans = 0;
  for (int i=0; i<n; ++i)
  {
    int pos = sam_root;
    long long max_pre = 0;
    for (char *j = str[i]; j < str[i + 1]; ++j)
    {
      pos = p[pos].next[*j - 'a'];
      access(&t[pos]), splay(&t[pos]);
      max_pre = max(max_pre, t[pos].max);
    }
    long long this_val = max_pre + val[i];
    ans = max(ans, this_val);
    t[pos].val = max(t[pos].val, this_val);
    push_up(&t[pos]);
  }

  printf("%lld\n", ans);
  return 0;
}
