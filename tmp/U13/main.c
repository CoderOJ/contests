#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 500005
#define C 27

struct trie_node_t
{
  struct trie_node_t *next[C];
  struct trie_node_t *parent;
};

void *allocate(size_t size)
{
  static char pool[N * sizeof(struct trie_node_t)];
  static char *p = pool;
  void *res = (void *)(p);
  p += size;
  return res;
}

struct trie_node_t root;

int encode_char(char c)
{
  if (isalpha(c))
    return c - 'a';
  else
    return 26;
}

char decode_char(int c)
{
  if (c < 26)
    return (char)('a' + c);
  else
    return '/';
}

int trie_get_eid(const struct trie_node_t *p, const struct trie_node_t *q)
{
  for (int i = 0; i < C; i++)
    if (p->next[i] == q)
      return i;
  return -1;
}

struct trie_node_t *trie_at(struct trie_node_t *p, char *s)
{
  while (*s)
  {
    int c = encode_char(*s); 
    if (p->next[c] == NULL)
    {
      p->next[c] = (struct trie_node_t *)(allocate(sizeof(struct trie_node_t)));
      p->next[c]->parent = p;
    }
    p = p->next[c];
    s++;
  }
  return p;
}

size_t trie_trace(char *s, const struct trie_node_t *p)
{
  if (p->parent != NULL)
  {
    size_t parent_len = trie_trace(s, p->parent);
    s[parent_len] = decode_char(trie_get_eid(p->parent, p));
    s[parent_len + 1] = '\0';
    return parent_len + 1;
  }
  else
  {
    return 0;
  }
}

int n, m;
char s[N], t[N], ans[N];

void format_path(char *s)
{
  if (s[1] == '\0')
  {
    s[0] = '\0';
  }
}

void restruct_path(char *s)
{
  if (s[0] == '\0')
  {
    s[0] = '/';
    s[1] = '\0';
  }
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
  {
    scanf("%s%s", s, t);
    format_path(s);
    format_path(t);
    struct trie_node_t *p;
    p = trie_at(&root, t);
    p = trie_at(p, "/");
    struct trie_node_t *q;
    q = trie_at(&root, s);
    q->next[encode_char('/')] = p;
  }
  for (int i = 0; i < m; i++)
  {
    scanf("%s", s);
    format_path(s);
    struct trie_node_t *p;
    p = trie_at(&root, s);
    p = trie_at(p, "/");
    trie_trace(ans, p->parent);
    restruct_path(ans);
    puts(ans);
  }
  return 0;
}
