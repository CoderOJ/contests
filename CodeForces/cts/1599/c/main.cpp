#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  double p = sc.next_double();

  const int all = n * (n - 1) * (n - 2) / 6;
  for (int i = 0; i < n; i++)
  {
    double s0p = 1.0 * ((n-i) * (n-i-1) * (n-i-2) / 6) / all;
    double w0p = 0;
    double s1p = 1.0 * ((n-i) * (n-i-1) / 2 * i) / all;
    double w1p = 0.5;
    double s2p = 1.0 * ((n-i) * i * (i-1) / 2) / all;
    double w2p = 1;
    double s3p = 1.0 * (i * (i-1) * (i-2) / 6) / all;
    double w3p = 1;
    see(i, s0p, w0p, s1p, w1p, s2p, w2p, s3p, w3p);
    see(s0p * w0p + s1p * w1p + s2p * w2p + s3p * w3p);
    if (
        s0p * w0p + 
        s1p * w1p + 
        s2p * w2p + 
        s3p * w3p >= p)
    {
      printf("%d\n", i);
      return 0;
    }
  }
  return 0;
}

