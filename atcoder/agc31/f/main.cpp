#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node
{
  node *fa = this;
  node *find()
  {
    return this == fa ? this : fa = fa->find();
  }
} A[50005][2][3];

void merge(node *x, node *y)
{
  node *fax = x->find(), *fay = y->find();
  if (fax == fay)
    return;
  fax->fa = fay;
}

struct edge
{
  int u, v, c;
} G[50005];

int n, m_, q_, p, g, B;
bool check[2][1000005];

int gcd(int a, int b)
{
  return b == 0 ? a : gcd(b, a % b);
}

int main()
{
  n = sc.next_int();
  m_ = sc.next_int();
  q_ = sc.next_int();
  p = sc.next_int();
  g = p;

  for (int i = 0; i < m_; i++)
  {
    G[i].u = sc.next_int();
    G[i].v = sc.next_int();
    G[i].c = sc.next_int();
    g = gcd(g, abs(G[i].c - G[0].c));
  }

  p = gcd(3 * g, p);
  B = G[0].c % g;
  for (int i = 0; i < m_; i++)
  {
    int k = G[i].c / g;
    for (int l = 0; l < 2; l++)
      for (int m = 0; m < 3; m++)
      {
        merge(A[G[i].u][l] + m, A[G[i].v][l ^ 1] + (2 * m + k) % 3);
        merge(A[G[i].v][l] + m, A[G[i].u][l ^ 1] + (2 * m + k) % 3);
      }
  }

  for (int i = 0, pB = B; i < p * 2; i++, pB = (pB + pB) % p)
    check[i & 1][pB] = true;

  while (q_--)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    bool ans = false;
    for (int l = 0; l < 2; l++)
      for (int m = 0; m < 3; m++)
        if (check[l][((3 - m) * g + w + B) % p])
          if (A[v][0][0].find() == A[u][l][m].find())
          {
            ans = true;
            break;
          }
    puts(ans ? "YES" : "NO");
  }
}
