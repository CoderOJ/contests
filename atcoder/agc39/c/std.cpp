#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define mod 998244353

using namespace std;
typedef long long ll;
const int MAXN = 400005;
int n,a[MAXN],b[MAXN];
char str[MAXN];
ll f[MAXN];
inline void solve(int x)
{
	ll res = 0;
	for(int i = 1; i<=x/2; i++)
		res = (res*2+a[i])%mod;
	res = (res+1)%mod;
	for(int i = 1, j = 0; i<=n; i += x/2, j++)
		for(int k = i; k<=i+x/2-1; k++)
			b[k] = a[k-i+1]^(j&1);
	bool flag = true;
	for(int i = 1; i<=n; i++)
	{
		if(b[i]>a[i])
			flag = false;
	    else if(b[i]<a[i])
	    	break;
	}
	if(!flag)
		res = (res+mod-1)%mod;
	f[x] = res;
}

int main()
{
	cin >> n >> str+1;
	for(int i = 1; i<=n; i++)
		a[i] = str[i]-'0';
	for(int i = 1; i<=2*n; i++)
		if(2*n%i==0&&n%i!=0)
			solve(i);
	for(int i = 1; i<=2*n; i++)
		if(2*n%i==0&&n%i!=0)
			for(int j = 2*i; j<=2*n; j += i)
				if(2*n%j==0&&n%j!=0)
					f[j] = (f[j]-f[i]+mod)%mod;
	ll ans = 0;
	for(int i = 1; i<=2*n; i++)
		ans = (ans+f[i]*i)%mod;
	cout << ans << endl;
	return 0;
}
