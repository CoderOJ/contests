#include <bits/stdc++.h>

using namespace std;

#include "graph.h"

vector<int> check_bipartite(int vsize)
{
	vector<pair<int, int> > to_query;
	to_query.push_back(make_pair(0, 1));
	vector<int> ret;
	if (query(to_query)) ret.push_back(vsize - 1);
	return ret;
}
