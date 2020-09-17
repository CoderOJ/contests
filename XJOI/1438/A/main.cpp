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
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

namespace fft {
     const double eps = 0.1;
     const double PI = acos(-1.0);

    struct Virt {
        double r , i;
        
        Virt (double r = 0.0 , double i = 0.0) : r(r) , i(i) {}
        Virt operator = (const double x) {
            *this = Virt(x,0);
            return *this;
        }
        Virt scanr() {
            *this = Virt();
            scanf("%lf",&r);
            return *this;
        }
        Virt scanv() {
            scanf("%lf%lf",&r,&i);
            return *this;
        }
        void log() {
            cout << r << ' ' << i << endl;
        }
        
        bool operator == (const Virt B) const {
            return (abs(r - B.r) < eps) && (abs(i - B.i) < eps);
        }
        bool operator == (const double x) const {
            return *this == Virt(x,0);
        }
        bool operator != (const Virt B) const {
            return !(*this == B);
        }
        bool operator != (const double x) const {
            return !(*this == x);
        }
        
        Virt operator + (const Virt B) const {
            return Virt(r + B.r , i + B.i);
        }
        Virt operator - (const Virt B) const {
            return Virt(r - B.r , i - B.i);
        }
        Virt operator * (const Virt B) const{
            return Virt(r * B.r - i * B.i , i * B.r + r * B.i);
        }
        Virt conv() {
            return Virt(r , -i);
        }
    };
    
    int getRev (int x , int len) {
        int res = 0;
        for (int i=1;i<len;i<<=1) {
            res <<= 1;
            res |= (x & 1);
            x >>= 1;
        }
        return res;
    }
    
    void dft (vector < Virt > & A , int conv) { // conv ? IDFT : DFT
        int n = A.size();
        rep (i,n) {
            int rev = getRev(i,n);
            if (rev >= i) continue;
            swap (A[i] , A[rev]);
        }
        for (int len = 1;len < n;len <<= 1) {
            Virt mul = Virt( cos(PI / len) , sin(PI / len) );
            if (conv) mul = mul.conv();
            for (int j=0;j<n;j += len * 2) {
                Virt w = 1.0;
                for (int st = j;st < j + len ;st++) {
                    Virt x = A[st];
                    Virt y = w * A[st + len];
                    A[st] = x + y;
                    A[st + len] = x - y;
                    w = w * mul;
                }
            }
        }
    }
    
    vector < Virt >
    fft (vector < Virt > A , vector < Virt > B) {
        int as = A.size() + B.size() - 1;
        int bn = max(A.size() , B.size());
        int n = 1;
        while (n < bn) n <<= 1;
        n <<= 1;
        A.resize(n , Virt());
        B.resize(n , Virt());
        dft(A,0);
        dft(B,0);
        rep (i,n) A[i] = A[i] * B[i];
        dft(A,1);
        rep (i,n) A[i].r /= n;
        A.resize(as,Virt());
        return A;
    }
    
    vector < Virt > 
    vivc (vector < int > A) {
        vector < Virt > B;
        rep (i,(int)A.size()) B.push_back( Virt(1.0 * A[i],0.0) );
        return B;
    }

    vector < int > 
    vvic (vector < Virt > A) {
        vector < int > B;
        rep (i,(int)A.size()) B.push_back( (int)(A[i].r + 0.5) );
        return B;
    }

    vector < int > 
    mul (vector < int > A , vector < int > B) {
        return vvic( fft( vivc(A) , vivc(B) ) );
    }
}

struct Bint {
    vector < int > dig;
    int pn;
    
    Bint (vector < int > dig = vector < int > () , int pn = 0) 
        : dig(dig) , pn(pn) {}
    inline int len() const {
        return (int)dig.size();
    }
    Bint (long long x) {
        dig.clear();
        pn = (x >= 0) ? 0 : 1;
        if (x < 0 ) x = -x;
        while (x) {
            dig.push_back(x % 10);
            x /= 10;
        }
    }
    Bint (const string s) {
        dig.clear();
        pn = 0;
        int st = 0;
        int len = s.length();
        if (s == "") return;
        if (s[0] == '-') {
             st++;
             pn = 1;
        }
        for (int i=st;i<len;i++) dig.push_back(s[i] - '0');
        reverse(dig.begin() , dig.end());
        while (dig.size() && dig[dig.size() - 1] == 0) dig.pop_back();
    }
    string toString() const {
        if (len() == 0) return "0";
        string res ;
        if (pn) res = "-";
        for (int i=len();i > 0;i--) res = res + (char)(dig[i - 1] + '0');
        return res;
    }
    friend istream& operator >> (istream& is , Bint& B) {
        string s;
        is >> s;
        B = Bint(s);
        return is;
    }
    friend ostream& operator << (ostream& os , const Bint& B) {
        os << B.toString();
        return os;
    }

    bool less(const Bint& B) const {
        if (len() != B.len()) return len() < B.len();
        for (int i = len() - 1;i>=0;i--) {
            if (dig[i] != B.dig[i]) return dig[i] < B.dig[i];
        }
        return 0;
    }

    void weal() {
        if (!len()) return;
        int n = len() + 1;
        dig.resize(n,0);
        for (int i=1;i < n;i++) {
            dig[i] += dig[i - 1] / 10;
            dig[i - 1] %= 10;
            if (dig[i - 1] < 0) {
                dig[i - 1] += 10;
                dig[i] --;
            }
        }
        while (n && dig[n - 1] == 0) {
            dig.pop_back();
            n--;
        }
    }
    Bint uadd (const Bint& B) const {
        int n = len() , m = B.len();
        Bint C;
        rep (i, max(n,m) ) C.dig.push_back( ((i < n) ? dig[i] : 0) + (i < m ? B.dig[i] : 0) );
        C.weal();
        return C;
    }
    Bint usub (const Bint& B) const {
        int n = len() , m = B.len();
        Bint C;
        rep (i, max(n,m) ) C.dig.push_back( ((i < n) ? dig[i] : 0) - (i < m ? B.dig[i] : 0) );
        C.weal();
        return C;
    }

    Bint operator + (const Bint& B) const {
        int x = pn ^ B.pn;
        Bint C;
        if (x) {
            C.pn = less(B);
            C.dig = (C.pn ? B.usub(*this) : usub(B)).dig;
            C.pn ^= pn;
        } else {
            C.pn = pn;
            C.dig = (uadd(B)).dig;
        }
        return C;
    }
    Bint operator - (const Bint& B) const {
        Bint C = *this + Bint(B.dig,B.pn ^ 1) ;
        return C; 
    }
    Bint operator * (const Bint& B) const {
        Bint C = Bint(fft::mul( this->dig , B.dig ) , pn ^ B.pn );
        C.weal();
        return C;
    }   
    bool operator == (const Bint& B) const {
        return dig == B.dig && pn == B.pn;
    }
};

void init() {
     
}

void solve() {
    Bint n, m;
    cin >> n >> m;
    if (m == Bint(0)) cout << n+1 << endl;
    else cout << m-n+1 + n*2 << endl;
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

