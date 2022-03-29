#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

#include "graph.h"

static const int maxn = 210;

static int _n;
static bool _adj[maxn + 5][maxn + 5];

void init(int n) 
{
	_n = n;
	int m;
	assert(scanf("%d", &m) == 1);
	memset(_adj, 0, sizeof _adj);
	REP(i, 0, m)
	{
		int u, v;
		assert(scanf("%d%d", &u, &v) == 2);
		_adj[u][v] = _adj[v][u] = 1;
	}
}

static int _pa[maxn + 5];

static int _get(int x) { return _pa[x] == x ? x : _pa[x] = _get(_pa[x]); }

bool query(vector<pair<int, int> > banned_edges)
{
	static bool banned[maxn + 5][maxn + 5];
	memset(banned, 0, sizeof banned);
	REP(i, 0, SZ(banned_edges)) 
	{
		banned[banned_edges[i].x][banned_edges[i].y] = 1;
		banned[banned_edges[i].y][banned_edges[i].x] = 1;
	}
	REP(i, 0, _n) _pa[i] = i;
	REP(i, 0, _n) REP(j, 0, _n - 1)
		if (_adj[i][j] && !banned[i][j]) _pa[_get(i)] = _get(j);
	REP(i, 1, _n) if (_get(i) != _get(0)) return 0;
	return 1;
}
