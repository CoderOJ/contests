#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);

const int N = 2005;
const int M = 205;
const int K = 26;
const int MOD = 1e9 + 7;

struct Node {
    Node* ss[K];
	int mn, mx;
	Node () { mn = N; rep (i,K) ss[i] = NULL;  }
};

class Trie {
private:
    Node* R;
public:
    Trie() { R = new Node(); }

    void insert(const char* s,int inter) {
        Node* p = R;
		checkMin(p->mn,inter); 
		checkMax(p->mx,inter);
        while (*s) {
            int u = *s-'a';
			if (p->ss[u] == NULL) p->ss[u] = new Node();
			p = p->ss[u];
			checkMin(p->mn,inter);
			checkMax(p->mx,inter);
            s++;
        }
    }

    vector < pr > is;

    void getInter(Node* u) {
        if (u != R) is.push_back( pr(u->mx, u->mn) );
        rep (i,26) if (u->ss[i] != NULL) getInter(u->ss[i]);
    }

    vector < pr > get() {
        getInter(R);
        return is;
    }
};

Trie T;

int n, m;
string s[N];
vector < pr > inters;
vector < int > act[N];

void init() {
    scanf(II,&n,&m);
    rep (i,n) s[i] = sc.next();
    sort(s, s+n);
    rep (i,n) T.insert(s[i].c_str(),i+1);
    inters = T.get();
    repe (i,inters) act[ inters[i].L ].push_back( inters[i].R-1 );
    repe (i,inters) { ses(inters[i].L); see(inters[i].R); }
    repa (i,n) { repe(j,act[i]) ses(act[i][j]); see(""); }
}

int dp[N];

void solve() {
    dp[0] = 1;
    rep (_,m) repb (i,n,0) {
        dp[i] = 0;
        repe (j,act[i]) (dp[i] += dp[act[i][j]]) %= MOD;
    }
    printf(IN,dp[n]);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
