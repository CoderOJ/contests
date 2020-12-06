#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)
template <class T> inline bool checkMin(T& a, T b) { return a>b ? a=b,1 : 0; }
template <class T> inline bool checkMax(T& a, T b) { return a<b ? a=b,1 : 0; }

const int N = 55;
const int M = 405;
int a[N][M], n, m;
std::vector< std::pair<int,int> > ans;

int find_color(int r) {
  static int ans[N], la[N], ex[N];
  memset(ans, 0, sizeof(ans));  memset(ex, 0, sizeof(ex));
  repa (i,r) rep (j,m) {
    memset(la, 0, sizeof(la));
    if (!la[a[i][j]]) { ans[ a[i][j] ] += m-j; la[a[i][j]] = 1; ex[a[i][j]] = 1; } }
  int min_cost=0x3f3f3f3f, min_id=1;
  repa (i,n) if (ex[i]) if (checkMin(min_cost, ans[i])) { min_id = i; } 
  return min_id;
}

void mv(int from, int relay, int to, int col) {
	int pos_col = 0, max_dep = 0;
	repa (i,m) if (a[from][m-i] == col) { pos_col ++; max_dep=i; }
	if (pos_col == 0) { return; }
	int from_top = m;
	int relay_top = m;
	int to_top = 0;
	rep (i,pos_col) { 
		ans.push_back( std::make_pair(relay, to) );
		a[to][to_top++] = a[relay][--relay_top]; }
	rep (i,max_dep) {
		if (a[from][--from_top] == col) {
			ans.push_back( std::make_pair(from, relay) );
			a[relay][relay_top++] = a[from][from_top]; }
		else {
			ans.push_back( std::make_pair(from, to) );
			a[to][to_top++] = a[from][from_top]; } }
	rep (i,max_dep - pos_col) {
		ans.push_back( std::make_pair(to, from) );
		a[from][from_top++] = a[to][--to_top]; }
	rep (i,pos_col) {
		ans.push_back( std::make_pair(relay, from) );
		a[from][from_top++] = a[relay][--relay_top]; }
	rep (i,pos_col) {
		ans.push_back( std::make_pair(to, relay) );
		a[relay][relay_top++] = a[to][--to_top]; }
}

int top[N];
int main() {
	scanf("%d%d", &n,&m);
	repa (i,n) { rep (j,m) scanf("%d", &a[i][j]); }
	repa (i,n) top[i] = m;
	for (int col=n; col>=2; col--) {
    int cho = find_color(col);
		for (int i=1; i<=col; ++i) {
			mv(i, i%col+1, col+1, cho); }
		for (int i=1; i<=col; ++i) {
			while (top[i] && a[i][top[i]-1] == cho) {
				ans.push_back( std::make_pair(i, col+1) );
				a[col+1][top[col+1]] = a[i][top[i]-1]; top[col+1]++; top[i]--; } }
		for (int i=1; i<col; ++i) {
			while (top[i] < m) {
				ans.push_back( std::make_pair(col, i) );
				a[i][top[i]] = a[col][top[col]-1]; top[i]++; top[col]--; } }
	}
	int sz = ans.size();
	printf("%d\n", sz);
	rep (i,sz) {
		printf("%d %d\n", ans[i].first, ans[i].second); }
	return 0;
}
