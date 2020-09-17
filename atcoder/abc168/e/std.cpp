#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
ll modpow(ll n, int k) {
	ll r = 1;
	while (k > 0) {
		if (k&1) (r *= n) %= mod;
		(n *= n) %= mod;
		k >>= 1;
	}
	return r;
}
ll f(int n) {
	return modpow(2, n);
}
int main() {
	int N;
	cin >> N;
	ll res = 1, res0 = 0;
	map<pair<ll,ll>,pair<int,int>> cnt;
	for (int i = 0; i < N; ++ i) {
		ll a, b;
		cin >> a >> b;
		if (b < 0) { a = -a; b = -b; }
		if (a == 0 && b == 0) {
			++ res0;
		} else {
			auto g = abs(gcd(a, b));
			a /= g;
			b /= g;
			if (a <= 0) {
				++ cnt[{b,-a}].second;
			} else {
				++ cnt[{a,b}].first;
			}
		}
	}
	for (auto p : cnt) {
		auto t = f(p.second.first) + f(p.second.second) + mod - 1;
		(res *= t) %= mod;
	}
	res = (res + res0 + mod - 1) % mod;
	cout << res << endl;
}

