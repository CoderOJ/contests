#include <stdio.h>
#include <algorithm>


char ch;
inline void read(int &x)
{
	x=0;ch=getchar();
	while ( ch<=32 ) ch=getchar();
	while ( ch>32 ) x=x*10+ch-48,ch=getchar();
};

#define MAXN 500005
#define MAXHSIZE (MAXN+500005*4)

int n,k;
int w[MAXN];
int fa[MAXN],h[MAXN];

int _ch[MAXN],size[MAXN];
int d1[MAXN],_tot;

int up[MAXN];
int _mi[MAXN];

inline void _pre()
{
	int i;
	for ( i=1;i<=n;i++ ) {
		if ( !d1[i] ) {
			int j=i;
			while ( j ) {
				d1[j]=++_tot;
				up[j]=i;
				j=_ch[j];
			};
		};
	};
};

#define M (1<<19)

int T[M<<1];

inline void pre()
{
	int i;
	for ( i=n;i>=2;i-- ) {
		++size[i];
		int f=fa[i];
		size[f]+=size[i];
		_ch[f]=size[_ch[f]]>size[i] ? _ch[f] : i;
	};
	up[1]=1;_mi[1]=1;T[1+M]=1;
	_pre();
	for ( i=2;i<=n;i++ ) {
		T[d1[i]+M]=i;
		if ( up[i]==i ) {
			_mi[i]=i;
		} else {
			int t=_mi[fa[i]];
			_mi[i]=w[t]<w[i] ? t : i;
		};
	};
	int l=1+M,r=n+M;
	while ( l^1 ) {
		l>>=1;r>>=1;
		for ( i=r;i>=l;i-- ) T[i]=w[T[i+i]]<w[T[i+i+1]] ? T[i+i] : T[i+i+1];
	};
};

inline int getlca(int x,int y)
{
	int ux=up[x],uy=up[y];
	while ( ux^uy ) {
		if ( h[ux]>h[uy] ) {
			x=fa[ux];
			ux=up[x];
		} else {
			y=fa[uy];
			uy=up[y];
		};
	};
	return h[x]<h[y] ? x : y;
};

inline int que(int l,int r)
{
	int ret=T[l+M];
	l+=M-1;r+=M+1;
	while ( l^r^1 ) {
		if ( ~l&1 ) ret=w[T[l^1]]<w[ret] ? T[l^1] : ret;
		if ( r&1 ) ret=w[T[r^1]]<w[ret] ? T[r^1] : ret;
		l>>=1;r>>=1;
	};
	return ret;
};

inline int getmin_d(int x,int d)
{
	int ret=x;
	while ( 1 ) {
		int u=up[x];
		int len=h[x]-h[u]+1;
		if ( d>len ) {
			int t=_mi[x];
			ret=w[ret]<w[t] ? ret : t;
			d-=len;
			x=fa[u];
		} else {
			int t=que(d1[x]-d+1,d1[x]);
			return w[ret]<w[t] ? ret : t;
		};
	};
};

struct data0 {
	int x1,d1,x2,d2,x3,d3;
};

data0 A[MAXN];

inline void get(int id)
{
	int _x,_y,_z;
	read(_x);read(_y);read(_z);
	int _l1=getlca(_x,_y),_l2=getlca(_y,_z),_l3=getlca(_x,_z);
	int l1,l2,x,y,z;
	if ( _l1==_l2 ) {
		l1=_l1,l2=_l3;
		x=_y,y=_z,z=_x;
	} else if ( _l1==_l3 ) {
		l1=_l1,l2=_l2;
		x=_x,y=_y,z=_z;
	} else {
		l1=_l2,l2=_l1;
		x=_z,y=_x,z=_y;
	};
	A[id]=(data0){x,h[x]-h[l1],y,h[y]-h[l2],z,h[z]-h[l1]+1};
};

struct data {
	int w;
	int id;
	int x,d;
};

inline bool operator < (const data &a,const data &b)
{
	return !(a.w<b.w);
};

data _H[MAXHSIZE];

int hsize;

inline void push(data x)
{
	_H[++hsize]=x;
	std::push_heap(_H+1,_H+hsize+1);
};

inline void pop()
{
	std::pop_heap(_H+1,_H+(hsize--)+1);
};

inline void push(int W,int x,int d)
{
	int mi=getmin_d(x,d);
	push((data){W+w[mi],mi,x,d});
};

inline void push(int W,int id)
{
	if ( A[id].d1 ) push(W,A[id].x1,A[id].d1);
	if ( A[id].d2 ) push(W,A[id].x2,A[id].d2);
	if ( A[id].d3 ) push(W,A[id].x3,A[id].d3);
};

inline void solve()
{
	int i;
	for ( i=1;i<=n;i++ ) {
		_H[i]=(data){w[i],i,i,1};
	};
	hsize=n;
	std::make_heap(_H+1,_H+n+1);
	while ( k-- ) {
		data t=_H[1];
		pop();
		int W=t.w;
		printf("%d\n",W);
		int id=t.id;
		int x=t.x;
		int d=t.d;
		push(W,id);
		if ( id!=x ) {
			int len=h[x]-h[id];
			int mi=getmin_d(x,len);
			push((data){W+w[mi]-w[id],mi,x,len});
		};
		if ( h[x]-d+1!=h[id] ) {
			int len=d-(h[x]-h[id]+1);
			int mi=getmin_d(fa[id],len);
			push((data){W+w[mi]-w[id],mi,fa[id],len});
		};
	};
};

int main()
{
	read(n);read(k);
	int i;
	for ( i=1;i<=n;i++ ) read(w[i]);
	for ( i=2;i<=n;i++ ) {
		read(fa[i]);h[i]=h[fa[i]]+1;
	};
	pre();
	for ( i=1;i<=n;i++ ) {
		get(i);
	};
	solve();
}

