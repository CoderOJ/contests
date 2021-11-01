#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <bitset>
#include <memory>
#include <stack>
#include <string>
#include <utility>
#include <vector>
// #include "/home/jack/cm/string"

using std::cin;
using std::cout;
using std::forward;
using std::move;

constexpr int MOD = 1'000'000'007;
using int_t = cm::intm<MOD>;
using poly_t = std::vector<int_t>;

struct expr_node_t
{
  virtual poly_t eval() const = 0;
  virtual ~expr_node_t() = default;
};

struct expr_node_symbol_t : public expr_node_t
{
  char sym;
  expr_node_symbol_t(char sym) : sym(sym)
  {
  }

  virtual poly_t eval() const override
  {
    if (sym == '?')
    {
      poly_t result(1 << 16);
      for (int cat = 0; cat < 2; cat++)
        for (int id = 0; id < 4; id++)
        {
          int mask = 0;
          for (int i = 0; i < 16; i++)
            if (((i >> id) & 1) == cat)
              mask |= (1 << i);
          result[mask] += 1;
        }
      return result;
    }
    else
    {
      int cat = sym <= 'D';
      int id = cat ? sym - 'A' : sym - 'a';
      poly_t result(1 << 16);
      int mask = 0;
      for (int i = 0; i < 16; i++)
        if (((i >> id) & 1) == cat)
          mask |= (1 << i);
      result[mask] = 1;
      return result;
    }
  }
};

poly_t &&poly_or(poly_t &&lhs, poly_t &&rhs)
{
  auto fwt = [](poly_t &a) {
    for (int i = 0; i < 16; i++)
      for (int j = 0; j < (1 << 16); j++)
        if ((j & (1 << i)))
          a[j] += a[j ^ (1 << i)];
  };
  auto ifwt = [](poly_t &a) {
    for (int i = 0; i < 16; i++)
      for (int j = 0; j < (1 << 16); j++)
        if ((j & (1 << i)))
          a[j] -= a[j ^ (1 << i)];
  };
  fwt(lhs);
  fwt(rhs);
  for (int i = 0; i < (1 << 16); i++)
    lhs[i] *= rhs[i];
  ifwt(lhs);
  return move(lhs);
}

struct expr_node_or_t : public expr_node_t
{
  std::unique_ptr<expr_node_t> ls, rs;
  expr_node_or_t(std::unique_ptr<expr_node_t> &&ls,
                 std::unique_ptr<expr_node_t> &&rs)
      : ls(forward<std::unique_ptr<expr_node_t>>(ls)),
        rs(forward<std::unique_ptr<expr_node_t>>(rs))
  {
  }

  virtual poly_t eval() const override
  {
    return poly_or(ls->eval(), rs->eval());
  }
};

poly_t &&poly_and(poly_t &&lhs, poly_t &&rhs)
{
  auto fwt = [](poly_t &a) {
    for (int i = 0; i < 16; i++)
      for (int j = 0; j < (1 << 16); j++)
        if (!(j & (1 << i)))
          a[j] += a[j ^ (1 << i)];
  };
  auto ifwt = [](poly_t &a) {
    for (int i = 0; i < 16; i++)
      for (int j = 0; j < (1 << 16); j++)
        if (!(j & (1 << i)))
          a[j] -= a[j ^ (1 << i)];
  };
  fwt(lhs);
  fwt(rhs);
  for (int i = 0; i < (1 << 16); i++)
    lhs[i] *= rhs[i];
  ifwt(lhs);
  return move(lhs);
}

struct expr_node_and_t : public expr_node_t
{
  std::unique_ptr<expr_node_t> ls, rs;
  expr_node_and_t(std::unique_ptr<expr_node_t> &&ls,
                  std::unique_ptr<expr_node_t> &&rs)
      : ls(forward<std::unique_ptr<expr_node_t>>(ls)),
        rs(forward<std::unique_ptr<expr_node_t>>(rs))
  {
  }

  virtual poly_t eval() const override
  {
    return poly_and(ls->eval(), rs->eval());
  }
};

struct expr_node_both_t : public expr_node_t
{
  std::unique_ptr<expr_node_t> ls, rs;
  expr_node_both_t(std::unique_ptr<expr_node_t> &&ls,
                   std::unique_ptr<expr_node_t> &&rs)
      : ls(forward<std::unique_ptr<expr_node_t>>(ls)),
        rs(forward<std::unique_ptr<expr_node_t>>(rs))
  {
  }

  virtual poly_t eval() const override
  {
    auto ls0 = ls->eval(), ls1 = ls0;
    auto rs0 = rs->eval(), rs1 = rs0;
    auto por = poly_or(move(ls1), move(rs1));
    auto pand = poly_and(move(ls0), move(rs0));
    for (int i = 0; i < (1 << 16); i++)
      pand[i] += por[i];
    return pand;
  }
};

std::string s;
std::vector<size_t> match;
std::unique_ptr<expr_node_t> parse(size_t l, size_t r)
{
  if (l + 1 == r)
    return std::unique_ptr<expr_node_t>(new expr_node_symbol_t(s[l]));

  size_t op_i = match[l] + 1;
  auto ls = parse(l + 1, op_i - 1);
  auto rs = parse(op_i + 2, r - 1);
  if (s[op_i] == '&')
    return std::unique_ptr<expr_node_t>(
        new expr_node_and_t(move(ls), move(rs)));
  else if (s[op_i] == '|')
    return std::unique_ptr<expr_node_t>(new expr_node_or_t(move(ls), move(rs)));
  else
    return std::unique_ptr<expr_node_t>(
        new expr_node_both_t(move(ls), move(rs)));
}

int main()
{
  cin >> s;
  std::stack<size_t> brackets;
  match.resize(s.length());
  for (size_t i = 0; i < s.length(); i++)
  {
    if (s[i] == '(')
      brackets.push(i);
    else if (s[i] == ')')
    {
      size_t l = brackets.top();
      brackets.pop();
      match[l] = i, match[i] = l;
    }
  }

  auto res = parse(0, s.length())->eval();

  std::vector<int> limits(16, -1);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int a, b, c, d, v;
    cin >> a >> b >> c >> d >> v;
    limits[d << 3 | c << 2 | b << 1 | a] = v;
  }

  int_t ans = 0;
  for (int i = 0; i < (1 << 16); i++)
  {
    bool valid_state = true;
    for (int j = 0; j < 16; j++)
      if (limits[j] != -1 && limits[j] != ((i >> j) & 1))
      {
        valid_state = false;
        break;
      }
    if (valid_state)
    {
      // see(std::bitset<16>(i), res[i]);
      ans += res[i];
    }
    // if (res[i] != 0)
    //   see(i, res[i]);
  }

  cout << ans << std::endl;

  return 0;
}
