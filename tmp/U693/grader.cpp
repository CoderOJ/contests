#include "subway.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
namespace grader {
	void invalid() {
		printf("Invalid input\n");
		exit(0);
	}
	void gg(int id) {
		printf("Wrong Answer [%d]\n", id);
		exit(0);
	}
	std::vector < int > fa;
	std::vector < std::pair < int, int > > sta;
	std::vector < std::pair < int, int > > e;
	std::vector < int > ans;
	const int LIMIT = 20000000;
	int n, m, limit, cnt;
	int cur, curl, able;
	int gf(int a) {
		while (fa[a] > 0) a = fa[a];
		return a;
	}
	void graderInit() {
		if (3 != scanf("%d%d%d", &n, &m, &limit)) invalid();
		if (n < 2 || m < 2) invalid();
		init(n, m, limit);
		e.resize(m + 1);
		for (int i = 1; i <= m; i++) if (2 != scanf("%d%d", &e[i].first, &e[i].second)) invalid();
		fa = std::vector < int > (n + 1, -1);
	}
	void merge(int x) {
	  printf("grader: merge: %d\n", x);
		if (!able) gg(1);
		if (x <= 0 || x > m) gg(2);
		if (x < curl) gg(3);
		if (++cnt > LIMIT) gg(4);
		cur = std::max(cur, x);
		int u = gf(e[x].first), v = gf(e[x].second);
		if (u == v) gg(5);
		if (fa[u] > fa[v]) std::swap(u, v);
		sta.emplace_back(u, fa[u]);
		sta.emplace_back(v, fa[v]);
		fa[u] += fa[v];
		fa[v] = u;
	}
	bool check(int x) {
		if (x <= 0 || x > m) gg(6);
		int u = gf(e[x].first), v = gf(e[x].second);
		return u != v;
	}
	void undo() {
	  printf("grader: undo:\n");
		if (sta.empty()) gg(7);
		fa[sta.back().first] = sta.back().second;
		sta.pop_back();
		fa[sta.back().first] = sta.back().second;
		sta.pop_back();
	}
	void main() {
		graderInit();
		ans.resize(m + 1);
		for (int i = 1; i <= m; i++) {
			cur = i, curl = i;
			able = 1;
			ans[i] = solve(i);
			able = 0;
			if (cur > ans[i]) gg(8);
		}
		if (cnt <= limit) printf("Success\n");
		else printf("Too many merge\n");
		printf("Count of merge: %d\n", cnt);
		for (int i = 1; i <= m; i++) printf("%d%c", ans[i], " \n"[i == m]);
	}
}
void undo() {
	grader::undo();
}
bool check(int x) {
	return grader::check(x);
}
void merge(int x) {
	grader::merge(x);
}
int main() {
	grader::main();
}
