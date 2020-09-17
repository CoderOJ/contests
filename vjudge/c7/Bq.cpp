#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define multitest int T;scanf("%d",&T);while (T--)
#define fast ios::sync_with_stdio(0),cin.tie(0)
int n,ans=0;
string a;
struct node {
	int l,r;
	string s;
	node() {
	}
	node(int l,int r,string s):l(l),r(r),s(s) {
	}
};
vector <node> v;
void get_l_r(string a) {
	for (int i=0; i<(int)a.size(); ++i) {
		if (i&&a[i]==')'&&a[i-1]=='(') {
			ans+=2;
			a=a.substr(0,i-1)+a.substr(i+1);
			i-=2;
		}
	}
	int p=0;
	for (int i=0; i<(int)a.size(); ++i) {
		if (a[i]==')') {
			++p;
		}
	}
	v.push_back(node(a.size()-p,p,a));
}

bool cmp(node a,node b) {
	if (a.l>a.r) {
		return b.l>b.r ? a.r<b.r : 1;
	} else {
		return b.l<=b.r ? a.l>b.l : 0;
	}
}

void solve() {
    cin >> n;
	ans=0,v.clear();
	for (int i=1; i<=n; ++i) {
		cin>>a;
		get_l_r(a);
	}
	sort(v.begin(),v.end(),cmp);
	string S="";
	for (int i=0;i<n;++i)
	{
		S+=v[i].s;
	}
	get_l_r(S);
	printf("%d\n",ans);
}

int main() {
	fast;
	multitest {
		solve();
	}
	return 0;
}
