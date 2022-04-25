#include <bits/stdc++.h>

using uint128_t = __uint128_t;

uint128_t read_uint128()
{
  static char buf[100];
  scanf("%s", buf);
  uint128_t res = 0;
  for (int i = 0; buf[i]; ++i)
    res = res << 4 | (buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10);
  return res;
}

void print_uint128(uint128_t res)
{
  if (res >= 16)
    print_uint128(res / 16);
  putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
}

const uint128_t uint128_full = static_cast<uint128_t>(-1);

template <int N>
struct number_t : public std::array<uint128_t, N>
{
  uint128_t get_sum() const
  {
    uint128_t r = 0;
    for (int i = 0; i < N; i++)
      r += this->at(i) << i;
    return r;
  }
  void push_and(uint128_t v)
  {
    for (int i = 0; i < N; i++)
      this->at(i) &= v;
  }
};

template <int N>
number_t<N + 1> operator+(const number_t<N> &lhs, const number_t<N> &rhs)
{
  uint128_t       c = 0;
  number_t<N + 1> r;
  for (int i = 0; i < N; i++)
  {
    uint128_t lxr = lhs[i] ^ rhs[i];
    r[i]          = lxr ^ c;
    c             = (lhs[i] & rhs[i]) | (lxr & c);
  }
  r[N] = c;
  return r;
}

template <int N>
struct sgt_t
{
  sgt_t<N - 1>    ls, rs;
  number_t<N + 1> num;
  bool            sor;
  uint128_t       tag_and;

  void push_up()
  {
    num = ls.num + rs.num;
    sor = ls.sor || rs.sor;
  }

  void push_and(uint128_t v)
  {
    tag_and &= v;
    num.push_and(v);
  }

  void push_down()
  {
    if (tag_and != uint128_full)
    {
      ls.push_and(tag_and);
      rs.push_and(tag_and);
      tag_and = uint128_full;
    }
  }

  void build(int l, int r, uint128_t v[])
  {
    tag_and = uint128_full;
    int m   = l + (r - l) / 2;
    ls.build(l, m, v);
    rs.build(m, r, v);
    push_up();
  }

  void range_and(int l, int r, int ml, int mr, uint128_t v)
  {
    if (sor)
    {
      if (ml <= l && r <= mr)
      {
        push_and(v);
      }
      else
      {
        push_down();
        int m = l + (r - l) / 2;
        if (ml < m)
          ls.range_and(l, m, ml, mr, v);
        if (mr > m)
          rs.range_and(m, r, ml, mr, v);
        push_up();
      }
    }
  }

  void range_div(int l, int r, int ml, int mr, uint128_t v)
  {
    push_down();
    int m = l + (r - l) / 2;
    if (ml < m && ls.sor)
      ls.range_div(l, m, ml, mr, v);
    if (mr > m && rs.sor)
      rs.range_div(m, r, ml, mr, v);
    push_up();
  }

  uint128_t query(int l, int r, int ql, int qr)
  {
    if (ql <= l && r <= qr)
    {
      return num.get_sum();
    }
    else
    {
      push_down();
      int m = l + (r - l) / 2;
      if (qr <= m)
        return ls.query(l, m, ql, qr);
      else if (ql >= m)
        return rs.query(m, r, ql, qr);
      else
        return ls.query(l, m, ql, qr) + rs.query(m, r, ql, qr);
    }
  }
};

template <>
struct sgt_t<0>
{
  number_t<0 + 1> num;
  bool            sor;

  void push_and(uint128_t v)
  {
    num.push_and(v);
  }

  void push_assign(uint128_t v)
  {
    num[0] = v;
    sor    = v > 0;
  }

  void build(int l, int, uint128_t v[])
  {
    push_assign(v[l]);
  }

  void range_and(int, int, int, int, uint128_t v)
  {
    push_and(v);
  }

  void range_div(int, int, int, int, uint128_t v)
  {
    switch (v)
    {
    case 2:
      push_assign(num[0] / 2);
      break;
    case 3:
      push_assign(num[0] / 3);
      break;
    case 4:
      push_assign(num[0] / 4);
      break;
    default :
      push_assign(num[0] / v);
      break;
    }
  }

  uint128_t query(int, int, int, int)
  {
    return num[0];
  }
};

const int B = 19;
const int N = 1 << B;
sgt_t<B>  sgt;

int       n, m;
uint128_t a[N];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    a[i] = read_uint128();
  sgt.build(0, N, a);

  for (int i = 0; i < m; i++)
  {
    int opt;
    scanf("%d", &opt);
    if (opt == 1)
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;

      uint128_t v = read_uint128();
      if (v > 1)
        sgt.range_div(0, N, l, r, v);
    }
    else if (opt == 2)
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;

      uint128_t v = read_uint128();
      sgt.range_and(0, N, l, r, v);
    }
    else
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;

      uint128_t ans = sgt.query(0, N, l, r);
      print_uint128(ans);
      putchar_unlocked('\n');
    }
  }

  return 0;
}
