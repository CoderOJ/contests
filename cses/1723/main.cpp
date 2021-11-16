#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;

template <class T, int N>
struct matrix_t
{
  T a[N][N];

  matrix_t operator* (const matrix_t &rhs) const 
  {
    matrix_t r; 
    for (int i = 0; i < N; i++)
      for (int k = 0; k < N; k++)
        for (int j = 0; j < N; j++)
          r.a[i][j] += a[i][k] * rhs.a[k][j];
    return r;
  }

  template <class Integer>
  matrix_t pow(Integer k)
  {
    matrix_t r;
    for (int i = 0; i < N; i++)
      r.a[i][i] = 1;
    matrix_t a = *this;
    for (; k; k >>= 1)
    {
      if (k & 1)
        r = r * a;
      a = a * a;
    }
    return r;
  }
};

template<class T, int N>
std::ostream &operator<< (std::ostream &out, const matrix_t<T,N> &a)
{
  for (int i = 0; i < N; i++)
  {
    out << std::endl;
    for (int j = 0; j < N; j++)
      out << a.a[i][j] << " " ;
  }
  out << std::endl;
  return out;
}

int main()
{
  using int_t = cm::intm<MOD>;
  using mat = matrix_t<int_t, 100>;

  mat e;
  int n = sc.next_int();
  int m = sc.next_int();
  int k = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e.a[v][u] += 1;
  }

  e = e.pow(k);
  std::cout << e.a[n - 1][0] << std::endl;

  return 0;
}

