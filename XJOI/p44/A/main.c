#include <stdio.h>
#define N 500010

int mod;
int power(int a, int b) {
  int r = 1;
  for(; b; b >>= 1) {
    if(b & 1) r = 1ll * r * a % mod;
    a = 1ll * a * a % mod; }
  return r; }

struct list_node_t
{
  struct list_node_t *next;
  int val;
};

struct list_t
{
  struct list_node_t *head;
  int size;
};

static struct list_node_t list_pool[N * 40], *list_pool_pos = list_pool;
void list_insert(struct list_t *t, int val)
{
  t->size++;
  list_pool_pos->val = val;
  list_pool_pos->next = t->head;
  t->head = list_pool_pos;
  list_pool_pos++;
}

int d[N], f[N], s[N], w[N];
struct list_t g[N];

int main() {
  int n;
  scanf("%d%d", &n, &mod);

  for(int i = 1; i <= n; i++) 
  {
    d[i] = power(g[i].size, mod - 2);
    f[i] = 1ll * f[i] * d[i] % mod;
    for(int j = i * 2; j <= n; j += i) 
    {
      list_insert(&g[j], i);
      f[j] = (f[j] + f[i] + 1) % mod; 
    } 
  }

  int ans = 0;
  s[1] = 1;

  for(int i = n; i > 1; i--) 
  {
    int sum = 1;
    for(int j = 2; i * j <= n; j++) 
    {
      int res = 0;
      for(struct list_node_t *k = g[j].head; k; k = k->next) 
        res = (res + s[k->val]) % mod;
      s[j] = 1ll * res * d[i * j] % mod; sum = (sum + s[j]) % mod; 
    }

    w[i] = 1ll * sum * sum % mod;
    for(int j = 2; i * j <= n; j++) 
      w[i] = (w[i] - 1ll * s[j] * s[j] % mod * w[i * j] % mod + mod) % mod;

    ans = (ans + 2ll * n * f[i] - 2ll * f[i] * w[i] % mod + mod) % mod; 
  }

  printf("%d\n", ans);
  return 0; }
