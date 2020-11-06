#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
template <class T> inline bool checkMin(T &a, T b) { return b<a ? a=b,1 : 0; }
template <class T> inline bool checkMax(T &a, T b) { return a<b ? a=b,1 : 0; }

const int N = 500005;
int sq[N];
int a[N];
int n;

double ans1[N], ans2[N];

void solve1(int l, int r, int sl, int sr) {
	if (l > r) { return; }
	int mid = (l+r)/2;
	int pos = 0;
	ans1[mid] = -1;
	for (int i=sl; i<=min(mid,sr); i++) {
		double cur = a[i] + sqrt( (double)(mid-i) );
		if (checkMax(ans1[mid], cur)) { pos = i; } }
	ans1[mid] -= a[mid];
	solve1(l,mid-1,sl,pos); solve1(mid+1,r,pos,sr); }

void solve2(int l, int r, int sl, int sr) {
	if (l > r) { return; }
	int mid = (l+r)/2;
	int pos = 0;
	ans2[mid] = -1;
	for (int i=max(mid,sl); i<=sr; i++) {
		double cur = a[i] + sqrt( (double)(i-mid) );
		if (checkMax(ans2[mid], cur)) { pos = i; } }
	ans2[mid] -= a[mid];
	solve2(l,mid-1,sl,pos); solve2(mid+1,r,pos,sr); }

int main() {
	rep (i,N) sq[i] = sqrt(i);
	scanf("%d",&n);
	rep (i,n) scanf("%d",&a[i]);
	solve1(0,n-1,0,n-1); solve2(0,n-1,0,n-1);
	rep (i,n) printf("%d\n", int( ceil( max(ans1[i], ans2[i]) )));
	return 0;
}
