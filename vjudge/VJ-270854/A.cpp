#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define int long long

const int N = 200005;
int sum[N << 2];
int mx[N << 2];
int add[N << 2];

void init_tree(){
	memset(add,0,sizeof(add));
	memset(sum,0,sizeof(sum));
	memset(mx,0,sizeof(mx));
}

inline void pushUp(int x){
	sum[x] = sum[x << 1] + sum[x << 1 | 1];
	mx[x] = max(mx[x << 1],mx[x << 1 | 1]);
}

void build(int arr[],int f,int t,int r = 1){
	//cout << f << ' ' << t << ' ' << r << endl;
	if (f == t){
		sum[r] = mx[r] = arr[f];
		return;
	}
	int mid = (f + t) >> 1;
	build(arr,f,mid,r << 1);
	build(arr,mid + 1,t, r << 1 | 1);
	pushUp(r);
}

inline void pushDown(int r,int f,int t){
	if (add[r]){
		int m = (f + t) >> 1;
		add[t << 1] = add[r];
		sum[t << 1] += add[r] * (m - f + 1);
		mx [t << 1] += add[r];
		add[t << 1 | 1] = add[r];
		sum[t << 1 | 1] += add[r] * (t - m);
		mx [t << 1 | 1] += add[r];
	}
}

void modify(int l,int r,int val,int f,int t,int root = 1){
	//cout << l << ' ' << r << ' ' << val << ' ' << f << ' ' << t <<  ' ' << root << endl;
	if (l <= f && r >= t){
		sum[root] += val * (r - l + 1);
		mx[root] += val;
		add[root] =  val;
		return ;
	}
	int mid = (f + t) >> 1;
	if (l <= mid){
		modify(l,min(mid,r),val,f,mid,root << 1);
	}
	if (r > mid){
		modify(max(mid + 1,l),r,val,mid + 1,t,root << 1 | 1);
	}
	pushUp(root);
}

int querySum(int l,int r,int f,int t,int root = 1){
	if (l <= f && r >= t){
		return sum[root];
	}
	pushDown(root,f,t);
	int res = 0;
	int mid = (f + t) >> 1;
	if (l <= mid){
		res += querySum(l,min(mid,r),f,mid,root << 1);
	}
	if (r > mid){
		res += querySum(max(mid + 1,l),r,mid + 1,t,root << 1 | 1);
	}
	return res;
}

int queryMax(int l,int r,int f,int t,int root = 1){
	//cout << l << ' ' << r << ' ' << f << ' ' << t << ' ' << root << endl;
	if (l <= f && r >= t){
		return mx[root];
	}
	pushDown(root,f,t);
	int res = 0;
	int mid = (f + t) >> 1;
	if (l <= mid){
		res = max(res,queryMax(l,min(mid,r),f,mid,root << 1));
	}
	if (r > mid){
		res = max(res,queryMax(max(mid + 1,l),r,mid + 1,t,root << 1 | 1));
	}
	return res;
}

int n,m;
int sc[N];

void init(){
	init_tree();
	for (int i=1;i<=n;i++){
		scanf("%d",&sc[i]);
	}
	build(sc,1,n);
}

void solve(){
	for (int i=1;i<=m;i++){
		char arg;
		int a,b;
		cin >> arg >> a >> b;
		if (arg == 'C'){
            cin >> c;
			modify(a,b,c,1,n);
			sc[a] = b;
		}else{
			cout << querySum(a,b,1,n) << endl;
		}
	}
}

#undef int
int main(){
#define int long long
	while(~scanf("%d%d",&n,&m)){
		init();
		solve();
	}
	return 0;
}
