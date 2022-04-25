#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> V;
#define F(N,S,E) for(int N=(int)(S);N<=(int)(E);N++)
#define R(N,S,E) for(int N=(int)(S);N>=(int)(E);N--)
#define D(N,E) for(int N=0;N<(int)(E);N++)

LL read10(){
	LL x;
	scanf("%lld",&x);
	return x;
}

typedef __uint128_t u128;
inline u128 read() {
    static char buf[100];
    scanf("%s", buf);
    // std::cin >> buf;
    u128 res = 0;
    for(int i = 0;buf[i];++i) {
        res = res << 4 | (buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10);
    }
    return res;
}
inline void output(u128 res) {
    if(res >= 16)
        output(res / 16);
    putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
    //std::cout.put(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
}

typedef u128 U;
U read16(){
	return read();
}
ostream &operator<<(ostream &o,U v){
	if(v>=16)o<<v/16;
	return o<<(char)(v % 16 >= 10 ? 'a' + v % 16 - 10 : '0' + v % 16);
}

template<int L>
struct Num{
	U v[L];
	U sum()const{
		U ans=0;
		D(i,L)ans+=v[i]<<i;
		return ans;
	}
};

template<int L>
Num<L+1> add(const Num<L> &a,const Num<L> &b){
	Num<L+1> result;
	result.v[0]=a.v[0]^b.v[0];
	U carry=a.v[0]&b.v[0];
	F(i,1,L-1){
		U w=a.v[i]^b.v[i];
		result.v[i]=w^carry;
		carry=(w&carry)|(a.v[i]&b.v[i]);
	}
	result.v[L]=carry;
	return result;
}

template<int L>
void dand(Num<L> &a,U b){
	D(i,L)a.v[i]&=b;
}

template<int L>
struct SegTree{
	static const int SIZE=1<<L;
	bool zero;
	Num<L+1> sum;
	U and_mark;

	SegTree<L-1> ls,rs;

	void build(U a[],int n,int ll){
		int mid=ll+(SIZE>>1);
		ls.build(a,n,ll);
		rs.build(a,n,mid);
		and_mark=~(U)0;
		upd();
	}

	void mk(U v){
		and_mark&=v;
		::dand(sum,v);
	}
	
	void pd(){
		if(~and_mark){
			ls.mk(and_mark);
			rs.mk(and_mark);
			and_mark=~(U)0;
		}
	}

	void upd(){
		sum=add(ls.sum,rs.sum);
		zero=ls.zero&&rs.zero;
	}

	U query(int l,int r,int ll){
		if(zero)return 0;
		// cerr<<"query "<<L<<" "<<l<<" "<<r<<" "<<ll<<endl;
		const int rr=ll+SIZE;
		if(ll>=l&&rr-1<=r)return sum.sum();
		int mid=ll+(SIZE>>1);
		pd();
		U ans=0;
		if(l<mid)ans+=ls.query(l,r,ll);
		if(r>=mid)ans+=rs.query(l,r,mid);
		return ans;
	}
	void dand(U v,int l,int r,int ll){
		if(zero)return;
		const int rr=ll+SIZE;
		if(ll>=l&&rr-1<=r){
			// cerr<<"mk "<<L<<" "<<l<<" "<<r<<" "<<ll<<endl;
			mk(v);
		}
		else{
			pd();
			int mid=ll+(SIZE>>1);
			if(l<mid)ls.dand(v,l,r,ll);
			if(r>=mid)rs.dand(v,l,r,mid);
			// cerr<<"ls:"<<ls.sum.sum()<<endl;
			// cerr<<"rs:"<<rs.sum.sum()<<endl;
			upd();
			// cerr<<"after "<<__FUNCTION__<<L<<": "<<sum.sum()<<endl;
		}
	}
	void ddiv(U v,int l,int r,int ll){
		if(zero)return;
		pd();
		int mid=ll+(SIZE>>1);
		if(l<mid)ls.ddiv(v,l,r,ll);
		if(r>=mid)rs.ddiv(v,l,r,mid);
		upd();
	}
};
template<>
struct SegTree<0>{
	bool zero;
	Num<1> sum;
	void mk(U v){
		::dand(sum,v);
	}
	void build(U a[],int n,int ll){
		if(ll<n){
			// cerr<<"build "<<ll<<endl;
			sum.v[0]=a[ll];
		}
		else{
			sum.v[0]=0;
		}
		zero=!sum.v[0];
	}
	U query(int,int,int){
		return sum.sum();
	}
	void ddiv(U x,int,int,int){
		if(zero)return;
		switch(x){
			case 2:sum.v[0]/=2;break;
			case 3:sum.v[0]/=3;break;
			case 4:sum.v[0]/=4;break;
			case 5:sum.v[0]/=5;break;
			case 6:sum.v[0]/=6;break;
			case 7:sum.v[0]/=7;break;
			case 8:sum.v[0]/=8;break;
			default:sum.v[0]/=x;break;
		}
		zero=!sum.v[0];
	}
	void dand(U v,int,int,int){
		// cerr<<"mk "<<0<<endl;
		::dand(sum,v);
		zero=!sum.v[0];
	}
};

SegTree<19> tr;

const int N=3.1e5;
U a[N];
int main(){
	int n=read10(),q=read10();
	D(i,n)a[i]=read16();
	tr.build(a,n,0);
	D(_,q){
		int op=read10();
		int l=read10()-1,r=read10()-1;
		if(op<=2){
			U v=read16();
			if(op==1){
				if(v>1)tr.ddiv(v,l,r,0);
			}
			else tr.dand(v,l,r,0);
		}
		else{
			output(tr.query(l,r,0));
			printf("\n");
		}
	}
	return 0;
}
