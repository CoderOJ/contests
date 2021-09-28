#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 305;

int n, k;
long long m;

long long ncr[N][N], t[N][N];
void init() {
	for(int i = 0; i <= n; ++i) {
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j)
			ncr[i][j] = (ncr[i - 1][j] + ncr[i - 1][j - 1]) % m;
	}
	for(int i = 1; i <= n; ++i)
		for(int k = 1; k <= i; ++k)
			for(int p = i - k + 1; p <= i; ++p)
				t[i][k] = (t[i][k] + ncr[p - 1][i - k]) % m;
}

long long dp[N][N];
void calc() {
	dp[0][0] = 1;
	for(int j = 1; j <= k; ++j) {
		dp[0][j] = 1;
		for(int i = 1; i <= n; ++i) {
			for(int k = 1; k <= i; ++k) {
				long long tmp = dp[k - 1][j - 1] * dp[i - k][j] % m;
				dp[i][j] = (dp[i][j] + tmp * t[i][k]) % m;
			}
			dp[i][j] = (dp[i][j] + dp[i][j - 1]) % m;
		}
	}
}


int main()
{
  n = sc.next_int();
  k = sc.next_int();
  m = sc.next_int(); 

  init();
  calc();
  std::cout << dp[n][k] << std::endl;

  return 0;
}

