#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define N 100005

struct node_t
{
  struct node_t *s[2], *f;
  int rev, vt, at;
};

struct node_t node_null, *node_null_p = &node_null;

struct node_t make_node()
{
  struct node_t res = 
  {
    .s   = {node_null_p, node_null_p},
    .f   = node_null_p,
    .rev = 0,
    .vt  = 1,
    .at  = 1
  };
  return res;
}

struct node_t p[N];

bool is_root(struct node_t *const this)
{
  // assert(this != node_null_p);
  return this->f == node_null_p || (this->f->s[0] != this && this->f->s[1] != this);
}

void push_up(struct node_t *this)
{
  this->at = this->vt;
  this->at += this->s[0]->at;
  this->at += this->s[1]->at;
}

void push_rev(struct node_t *const this)
{
  this->rev ^= 1;
  struct node_t *const tmp = this->s[0];
  this->s[0] = this->s[1];
  this->s[1] = tmp;
}

void push_down(struct node_t *const this)
{
  if (this->rev)
  {
    push_rev(this->s[0]);
    push_rev(this->s[1]);
  }
  this->rev = 0;
}

void push(struct node_t *const this)
{
  if (!is_root(this)) push(this->f);
  push_down(this);
}

void rotate(struct node_t *const this)
{
  struct node_t *const uu=this, *const ff=this->f, *const aa=this->f->f;
  bool ss = this->f->s[1] == this;
  if (!is_root(ff)) aa->s[aa->s[1] == ff] = uu;
  ff->f = uu; ff->s[ss] = uu->s[!ss];
  uu->f = aa; uu->s[!ss] = ff;
  if (ff->s[ss] != node_null_p) ff->s[ss]->f = ff;
  push_up(ff); push_up(uu);
}

void _splay(struct node_t *this)
{
  if (is_root(this)) return;
  if (is_root(this->f))
  {
    rotate(this);
    return;
  }
  if ((this->f->s[1] == this) == (this->f->f->s[1] == this->f))
    rotate(this->f);
  else 
    rotate(this);
  rotate(this);
  _splay(this);
}

void splay(struct node_t *this)
{
  push(this);
  _splay(this);
}

void access(struct node_t *this)
{
  struct node_t *uu=this, *ss=node_null_p;
  while (uu != node_null_p)
  {
    splay(uu);
    uu->vt += uu->s[1]->at;
    uu->s[1] = ss;
    uu->vt -= uu->s[1]->at;
    push_up(uu);
    ss = uu, uu = uu->f;
  }
}

void make_root(struct node_t *this)
{
  access(this);
  splay(this);
  push_rev(this);
}

void link(struct node_t *u, struct node_t *v)
{
  make_root(u);
  make_root(v);
  v->f = u;
  u->vt += v->at;
  push_up(u);
}

void split(struct node_t *u, struct node_t *v)
{
  make_root(u);
  access(v);
}

int n, q;

int main()
{
  scanf("%d%d", &n, &q);
  for (int i=1; i<=n; ++i)
    p[i] = make_node();

  for (int i=0; i<q; ++i)
  {
    char opt;
    int u, v;
    scanf(" %c %d%d", &opt, &u, &v);
    if (opt == 'A')
    {
      link(&p[u], &p[v]);
    }
    else
    {
      int usize, vsize;
      split(&p[v], &p[u]);
      usize = p[u].vt; 
      split(&p[u], &p[v]);
      vsize = p[v].vt; 
      // printf("usize = %d, visze = %d\n", usize, vsize);
      printf("%lld\n", 1ll * usize * vsize);
    }
  }
  return 0;
}
