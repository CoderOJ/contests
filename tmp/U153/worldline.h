#ifndef __WORLDLINE_H__
#define __WORLDLINE_H__

#ifdef __cplusplus
extern "C" {
#endif
	void new_round();
	void next_step();
	void addedge(int u,int v);
	int query(int u,int v);
	int query_permutation(int n,int ans[]);
#ifdef __cplusplus
}
#endif

#endif
