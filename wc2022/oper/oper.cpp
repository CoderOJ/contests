// #include "/home/jack/cm/debug"
#include <bits/stdc++.h>

constexpr int N = 100005;

std::vector<std::pair<int, int>> ops;
std::vector<std::pair<int, int>> ops_r;

char s[N * 2], t[N * 2];
int  n, k;

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

std::string s_flat;

void flat(int l, int r, int offset)
{
  if (r - l + 1 <= 4)
  {
    for (int i = l; i <= r; i++)
      s_flat += s[i];
    return;
  }

  // ( ((...)...) ... )
  if (s[l + 2] == '(')
  {
    ops.emplace_back(1, offset + l);
    flat(l + 1, match[l + 1], offset - 1);

    // hack
    l        = match[l + 1];
    s[l]     = '(';
    match[l] = r;
    match[r] = l;

    flat(l, r, offset);
  }
  else
  {
    ops.emplace_back(2, offset + l);

    int sr = match[l + 3];

    // hack
    s[l + 2]     = '(';
    s[l + 3]     = ')';
    match[l + 2] = l + 3;
    match[l + 3] = l + 2;
    match[l + 1] = sr;
    match[sr]    = l + 1;

    flat(l + 1, sr, offset - 1);

    // hack
    s[sr]     = '(';
    match[sr] = r;
    match[r]  = sr;

    flat(sr, r, offset);
  }
}

void final_flat(int len)
{
  if (len <= 4)
    return;

  if (s[len - 2] == '(')
    final_flat(len - 2);
  else
  {
    if (s[len - 6] == '(')
    {
      // ()(()) -> (())()
      ops.emplace_back(3, len - 6);

      s[len - 6] = '(';
      s[len - 5] = '(';
      s[len - 4] = ')';
      s[len - 3] = ')';
      s[len - 2] = '(';
      s[len - 1] = ')';

      final_flat(len - 2);
    }
    else
    {
      // (())(()) -> ((()))()
      ops.emplace_back(3, len - 8);
      // ((()))() -> (())()()
      ops.emplace_back(1, len - 8);

      s[len - 8] = '(';
      s[len - 7] = '(';
      s[len - 6] = ')';
      s[len - 5] = ')';
      s[len - 4] = '(';
      s[len - 3] = ')';
      s[len - 2] = '(';
      s[len - 1] = ')';

      final_flat(len - 4);
    }
  }
}

void adjust_flat()
{
  if (s[1] == '(')
  {
    // (())... -> ()...
    ops.emplace_back(6, 1);
    // ()... -> ()()...
    ops.emplace_back(5, 0);

    s[0] = '(';
    s[1] = ')';
    s[2] = '(';
    s[3] = ')';
  }
}

void build_r(int l, int r, int offset)
{
  if (r - l + 1 <= 2)
    return;

  ops_r.emplace_back(4, l + offset);

  int sr = match[l + 1];

  // hack
  t[sr]     = '(';
  match[sr] = r;
  match[r]  = sr;

  build_r(sr, r, offset);

  // unhack
  t[sr]        = ')';
  match[l + 1] = sr;
  match[sr]    = l + 1;

  build_r(l + 1, sr, offset - 1);
}

void rmain()
{
  ops.clear();
  ops_r.clear();
  s_flat.clear();

  scanf("%d%d", &n, &k);
  scanf("%s", s);
  scanf("%s", t);

  init_match(s);

  for (int i = 0; i < n * 2;)
  {
    int next_i = match[i] + 1;
    flat(i, match[i], 0);
    i = next_i;
  }
  // see("finish flat");
  // see(ops);

  std::copy(s_flat.begin(), s_flat.end(), s);

  final_flat(n * 2);
  // see("finish final flat");
  // see(ops);

  adjust_flat();
  // see("finish adjust_flat");
  // see(ops);

  init_match(t);

  ops.emplace_back(5, 2 * n);
  ops_r.emplace_back(6, 2 * n);

  for (int i = n * 2 - 1; i >= 0;)
  {
    int prev_i = match[i] - 1;
    build_r(match[i], i, 0);
    i = prev_i;
  }

  std::reverse(ops_r.begin(), ops_r.end());
  ops.insert(ops.end(), ops_r.begin(), ops_r.end());

  printf("%zu\n", ops.size());
  for (const auto &x : ops)
    printf("%d %d\n", x.first, x.second);
}

int main()
{
  freopen("oper.in", "r", stdin);
  freopen("oper.out", "w", stdout);

  int id, t;
  scanf("%d%d", &id, &t);
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
