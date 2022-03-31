#include"meeting.h"
#include<vector>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<algorithm>

static const int M = 3000;
static int n, m;
static int x[M], y[M];

static unsigned long long in[16];
static unsigned long long * ptr_x[M], * ptr_y[M];
static long long cnt, sum_size;

bool meeting(std::vector<int> set) {
	cnt += 1;
	sum_size += set.size();
	memset(in, 0, sizeof in);
	for(int i = 0;i < (int) set.size();++i) {
		in[set[i] >> 6] |= 1ull << (set[i] & 63);
	}
	int i = 0;
	for(;i < m;++i) 
		if(*ptr_x[i] >> x[i] & *ptr_y[i] >> y[i] & 1)
			return 0;
	return 1;
}

int main() {
	assert(fscanf(stdin, "%d%d", &n, &m) == 2);
	std::vector<std::pair<int, int> > sol;
	for(int i = 0;i < m;++i) {
		assert(fscanf(stdin, "%d%d", x + i, y + i));
		if(x[i] > y[i]) std::swap(x[i], y[i]);
		sol.push_back(std::pair<int, int>(x[i], y[i]));
		ptr_x[i] = in + (x[i] >> 6), x[i] &= 63;
		ptr_y[i] = in + (y[i] >> 6), y[i] &= 63;
	}
	std::vector<std::pair<int, int> > ans = solve(n);
	for(int i = 0;i < (int) ans.size();++i)
		if(ans[i].first > ans[i].second)
			std::swap(ans[i].first, ans[i].second);
	sort(ans.begin(), ans.end());
	sort(sol.begin(), sol.end());
	if(ans != sol) {
		fprintf(stdout, "wrong answer\n");
	} else {
		fprintf(stdout, "%lld %lld\n", cnt, sum_size);
	}
}
