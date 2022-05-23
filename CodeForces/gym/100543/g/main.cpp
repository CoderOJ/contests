#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 100005;
const int C = 4;

struct pam_t
{
  struct node_t
  {
    int next[C];
    int fail;
    int len;
    int pre;
    int dp, min_dp;
  };

  node_t p[N];
  int    s[N];
  int    len;
  int    cur;
  int    odd_r, even_r;
  int    last;

  void init()
  {
    memset(p, 0, sizeof(*p) * cur);
    len              = 0;
    cur              = 0;
    even_r           = cur++;
    odd_r            = cur++;
    p[odd_r].len     = -1;
    p[odd_r].fail    = odd_r;
    p[odd_r].pre     = odd_r;
    p[even_r].len    = 0;
    p[even_r].fail   = odd_r;
    p[even_r].pre    = odd_r;
    p[even_r].dp     = 1;
    p[even_r].min_dp = 1;
    last             = odd_r;
  }

  int get_next(int u, int c)
  {
    while (len == p[u].len || c != s[len - p[u].len - 1])
      u = p[u].fail;
    return u;
  }

  void extend(int c)
  {
    s[len]  = c;
    int pos = get_next(last, c);
    if (!p[pos].next[c])
    {
      int q          = cur++;
      p[q].len       = p[pos].len + 2;
      p[q].fail      = p[get_next(p[pos].fail, c)].next[c];
      p[pos].next[c] = q;
      {
        int f = p[get_next(p[pos].pre, c)].next[c];
        while (p[f].len * 2 > p[q].len)
          f = p[f].fail;

        p[q].pre = f;
        // see(p[q].len, p[p[q].pre].len);
      }
      if (p[q].len % 2 == 1)
        p[q].dp = 0;
      else
        p[q].dp =
            std::min(p[pos].dp - 1, p[p[q].pre].min_dp - p[q].len / 2 + 1);
      p[q].min_dp = std::min(p[q].dp, p[p[q].fail].min_dp);

      // see(pos, q, p[q].fail, p[q].dp);
    }
    last = p[pos].next[c];
    len++;
  }
};

pam_t pam;

int decode(char c)
{
  if (c == 'A')
    return 0;
  else if (c == 'C')
    return 1;
  else if (c == 'G')
    return 2;
  else
    return 3;
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    static char s[N];
    int         n = static_cast<int>(sc.next_token(s) - s);

    pam.init();
    for (int i = 0; i < n; i++)
      pam.extend(decode(s[i]));

    int ans = n;
    for (int i = 1; i < pam.cur; i++)
      check_min(ans, n + pam.p[i].dp);

    std::cout << ans << std::endl;
  }
  return 0;
}
