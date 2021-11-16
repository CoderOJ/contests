#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
#include <cstring>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

template <class T, int N>
struct matrix_t
{
  T a[N][N];
  matrix_t()
  {
    memset(a, 0x3f, sizeof(a));
  }

  matrix_t operator* (const matrix_t &rhs) const 
  {
    matrix_t r; 
    for (int i = 0; i < N; i++)
      for (int k = 0; k < N; k++)
        for (int j = 0; j < N; j++)
          check_min(r.a[i][j], a[i][k] + rhs.a[k][j]);
    return r;
  }

  template <class Integer>
  matrix_t pow(Integer k)
  {
    matrix_t a = *this;
    matrix_t r = a;
    k--;
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
  using mat = matrix_t<long long, 100>;

  mat e;
  int n = sc.next_int();
  int m = sc.next_int();
  int k = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    long long w = sc.next_int();
    check_min(e.a[v][u], w);
  }

  e = e.pow(k);
  long long ans = e.a[n - 1][0];
  std::cout << (ans == 0x3f3f3f3f3f3f3f3f ? -1 : ans) << std::endl;

  return 0;
}

