#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define pb push_back
#define mp make_pair
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<23;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
    static char Out[Output],*nowps=Out;
    
    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

    template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

inline void file()
{
}

const int MAXN=(1<<17)+7;

static int TT,n;

namespace polynomial
{
	const int mod=998244353,g=3;

	inline int power(int u,int v)
	{
		static int sm;
		for(sm=1;v;v>>=1,u=(uint64)u*u%mod)if(v&1)
			sm=(uint64)sm*u%mod;
		return sm;
	}

	static int Len,rev[MAXN],lg[MAXN];

	inline void predone(){Rep(i,2,Len)lg[i]=lg[i>>1]+1;}

	inline void calrev(int Len)
	{
		Rep(i,1,Len)rev[i]=
			(rev[i>>1]>>1)|((i&1)<<lg[Len]-1);
	}

	inline int ad(int u,int v){return(u+=v)>=mod?u-mod:u;}

	inline void NTT(int *a,int typ)
	{
		Rep(i,1,Len-1)if(rev[i]>i)swap(a[rev[i]],a[i]);
		static int i,j,k,kk,w,wn,t;
		for(k=2;k<=Len;k<<=1)
		{
			kk=k>>1;wn=power(g,(mod-1)/k);
			for(i=0;i<Len;i+=k)
				for(w=1,j=0;j<kk;++j,w=(uint64)w*wn%mod)
				{
					t=(uint64)w*a[i+j+kk]%mod;
					a[i+j+kk]=ad(a[i+j],mod-t);
					a[i+j]=ad(a[i+j],t);
				}
		}
		if(typ==-1)
		{
			reverse(a+1,a+Len);
			static int invn;invn=power(Len,mod-2);
			Rep(i,0,Len-1)a[i]=(uint64)a[i]*invn%mod;
		}
	}

	inline void mul(int *A,int *B)
	{
		NTT(A,1);NTT(B,1);
		Rep(i,0,Len-1)A[i]=(uint64)A[i]*B[i]%mod;
		NTT(A,-1);
	}

	static int A[MAXN],B[MAXN];

	void cdqFFT(int *f,int l,int r)
	{
		if(l==r)
		{
			f[l]=ad(f[l],(uint64)(l-1)*f[l-1]%mod);
			return;
		}
		int mid=(l+r)>>1;
		cdqFFT(f,l,mid);
		for(Len=r-l+1;Len>(Len&-Len);Len+=(Len&-Len));
		Rep(i,0,Len)A[i]=B[i]=0;
		Rep(i,l,mid)A[i-l]=(uint64)f[i]*(i-1)%mod,B[i-l]=f[i];
		calrev(Len);mul(A,B);
		Rep(i,mid+1,r)if(i>=l*2)f[i]=ad(f[i],A[i-2*l]);
		if(l^2)
		{
			Rep(i,0,Len)A[i]=B[i]=0;
			Rep(i,2,min(l-1,r-l))A[i-2]=f[i];
			Rep(i,l,mid)B[i-l]=f[i];
			mul(A,B);
			Rep(i,mid+1,r)if(i>=l+2)
				f[i]=ad(f[i],(uint64)(i-2)*A[i-l-2]%mod);
		}
		cdqFFT(f,mid+1,r);
	}
}
using namespace polynomial;

static int f[MAXN];

inline void init()
{
	read(TT);read(n);
	f[0]=1;f[1]=2;
	for(Len=4;Len<=n<<1;Len<<=1);
	predone();
	if(n>2)cdqFFT(f,2,n);
    for (int i = 0; i <= n; ++ i)
        printf("f[%d]=%d;\n", i, f[i]);
}

static int l[MAXN],cnt[MAXN],sta[MAXN],tp;

inline void solve()
{
	static int flg;
	Rep(i,1,TT)
	{
		tp=flg=0;
		Rep(j,1,n)
		{
			read(l[j]);cnt[j]=0;
			while(tp>=0&&sta[tp]>=j-l[j]+1)
			{
				if(sta[tp]-l[sta[tp]]<j-l[j])
				{flg=1;break;}
				++cnt[j],--tp;
			}
			sta[++tp]=j;
		}
		if(flg||l[n]!=n){puts("0");continue;}
		static int ans;ans=1;
		Rep(i,1,n)ans=(uint64)ans*f[cnt[i]]%mod;
		printf("%d\n",ans);
	}
}

int main()
{
    init();
    solve();
    return 0;
}


