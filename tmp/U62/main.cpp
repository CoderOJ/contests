#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 100005;
using Int = Temps::Intm<MOD>;
Int inv[N], pwa[N], pwb[N], b[N], mu[N];
Int u[N], v[N], f[N], g[N];
int is_prime[N], prime[N], prime_top = 0;
int n, A, B, q;

void preInit()
{
  n = sc.n(), A = sc.n(), B = sc.n();
  A -= B;

	inv[1] = 1; 
  for (int i = 2; i <= n; ++i) 
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
	for (int i = 1; i <= n; ++i) 
    pwb[i] = Int(i).pow(B);
	for (int i = 1; i <= n; ++i) 
    pwa[i] = A < 0 ? Int(inv[i]).pow(-A) : Int(i).pow(A);

	mu[1] = 1;
	for (int i = 2; i <= n; ++i) 
    is_prime[i] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (is_prime[i])
		{
			prime[++prime_top] = i;
			mu[i] = MOD - 1;
		}
		for (int j = 1; j <= prime_top && i * prime[j] <= n; ++j)
		{
			is_prime[i * prime[j]] = 0;
			if (i % prime[j] == 0) break;
			mu[i * prime[j]] = 0 - mu[i];
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i, k = 1; j <= n; j += i, ++k)
			f[j] += mu[i] * pwb[i] * pwa[k] * pwb[k];
}

void init()
{
	for (int i = 1; i <= n; ++i) b[i] = sc.n() / pwb[i];
	for (int i = 1; i <= n; ++i) g[i] = b[i];
	for (int i = 1; i <= n; ++i) 
    for (int j = i + i; j <= n; j += i) 
      g[j] -= g[i];
	for (int i = 1; i <= n; ++i) g[i] *= pwb[i];
}

void solve()
{
	for (int i = 1; i <= n; ++i)
	{
		if (f[i] != 0) g[i] /= f[i];
		else if (g[i] != 0)
		{
			printf("-1\n");
			return;
		}
	}
	for (int i = n; i >= 1; --i) 
    for (int j = i + i; j <= n; j += i) 
      g[i] -= g[j];
	for (int i = 1; i <= n; ++i) 
    g[i] /= pwb[i];
	for (int i = 1; i <= n; ++i) 
    printf("%d%c", static_cast<int>(g[i]), " \n"[i == n]);
}

