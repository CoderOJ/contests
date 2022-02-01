#include <bits/stdc++.h>

constexpr int N = 200005;

FILE *in;
FILE *out;

char s[N];
char t[N];

int n, k;

int match[N * 2];

void init_match(char *s)
{
  std::stack<int> st;
  for (int i = 0; i < n * 2; i++)
  {
    if (s[i] == '(')
      st.push(i);
    else
    {
      int pre = st.top();
      st.pop();
      match[pre] = i;
      match[i]   = pre;
    }
  }
}

void opt_1(int pos)
{
  init_match(s);

}

void rmain(int c)
{
  fscanf(in, "%d%d", &n, &k);
  fscanf(in, "%s", s);
  fscanf(in, "%s", t);

  int ops;
  fscanf(out, "%d", &ops);
  for (int i = 0; i < ops; i++)
  {
    int type, pos;
    fscanf(out, "%d%d", &type, &pos);
    if (type == 1)
      opt_1(pos);
    else if (type == 2)
      opt_2(pos);
    else if (type == 3)
      opt_3(pos);
    else if (type == 4)
      opt_4(pos);
    else if (type == 5)
      opt_5(pos);
    else
      opt_6(pos);
  }
}

int main(int argc, char **argv)
{
  assert(argc == 3);
  in  = fopen(argv[1], "r");
  out = fopen(argv[2], "r");

  int t;
  fscanf(in, "%*d%d", &t);
  for (int i = 0; i < t; i++)
    rmain(i);

  return 0;
}
