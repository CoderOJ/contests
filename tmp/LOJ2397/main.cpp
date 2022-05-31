#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <string>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 500005, 105)

std::vector<int> b[N];
std::vector<int> bp[N];

std::string foo()
{
  return 0;
}

int c[N];
int n;

bool query(int l, int r, int c)
{
  auto it = std::lower_bound(bp[c].begin(), bp[c].end(), l);
  if (it == bp[c].end())
    return false;
  else
    return *it < r;
}

int sr[N], l[N], r[N];

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
    c[i] = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int k = sc.next_int();
    b[i].reserve(k);
    for (int j = 0; j < k; j++)
    {
      int c = sc.next_int();
      b[i].push_back(c);
      bp[c].push_back(i);
    }
  }

  sr[n - 1] = n;
  for (int i = n - 2; i >= 0; i--)
  {
    sr[i] = i + 1;
    while (sr[i] != n)
    {
      if (query(i, sr[i], c[sr[i]]))
        sr[i] = sr[sr[i]];
      else
        break;
    }
  }

  l[0] = 0;
  r[0] = sr[0];
  for (int i = 1; i < n; i++)
  {
    l[i] = i;
    r[i] = sr[i];
    while (l[i] != 0)
    {
      see(i, l[i], r[i]);
      if (query(l[i], r[i], c[l[i]]))
      {
        r[i] = std::max(r[i], r[l[i] - 1]);
        l[i] = l[l[i] - 1];
        while (r[i] != n)
        {
          if (query(l[i], r[i], c[r[i]]))
            r[i] = sr[r[i]];
          else
            break;
        }
      }
      else
        break;
    }
  }

  int q = sc.next_int();
  for (int i = 0; i < q; i++)
  {
    int x = sc.next_int() - 1;
    int y = sc.next_int() - 1;
    if (l[x] <= y && y < r[x])
      puts("YES");
    else
      puts("NO");
  }

  return 0;
}
