#ifndef graph_h
#define graph_h

#include<vector>
#include<stdio.h>

bool query(std::vector<std::pair<int, int> > banned_edges);
std::vector<int> check_bipartite(int vsize);

#endif
