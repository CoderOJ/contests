#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm_alpha"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

using int_t = cm::intm<1'000'000'007>;

struct matrix_t
{
  int_t a[2][2] = {{0, 0}, {0, 0}};
  constexpr matrix_t() = default;
  constexpr matrix_t(int_t a, int_t b, int_t c, int_t d) : a{{a, b}, {c, d}} {}
  constexpr matrix_t operator*(const matrix_t &rhs) const
  {
    return matrix_t{a[0][0] * rhs.a[0][0] + a[0][1] * rhs.a[1][0],
                    a[0][0] * rhs.a[0][1] + a[0][1] * rhs.a[1][1],
                    a[1][0] * rhs.a[0][0] + a[1][1] * rhs.a[1][0],
                    a[1][0] * rhs.a[0][1] + a[1][1] * rhs.a[1][1]};
  }
  template <class Integer> constexpr matrix_t pow(Integer k) const
  {
    matrix_t r{1, 0, 0, 1}, a = *this;
    for (; k; k >>= 1)
    {
      if (k & 1)
        r = r * a;
      a = a * a;
    }
    return r;
  }
};

int main()
{
  constexpr matrix_t a{1, 1, 1, 0};
  long long n = sc.next_long();
  if (n == 0)
    std::cout << 0 << std::endl;
  else
    std::cout << a.pow(n - 1).a[0][0] << std::endl;
  return 0;
}
