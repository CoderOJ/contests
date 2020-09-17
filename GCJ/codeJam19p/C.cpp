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
#include <sstream>
using namespace std;

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > Point;
    
struct Bint {
//data
    static const int L = 305;
    int a[L];//from 0 to L-1
//insideUse fumction
    Bint(string s) {
        *this = s;
    }
    Bint(long long num = 0){
        stringstream s;
        s<<num;
        string str;
        s>>str;
        *this = str;
    }
    void print(){
        int top = L - 1;
        while(a[top] == 0) top--;
        for (int i = top; i >= 0; i--)
            cout<<a[i];
    }
    int length() const{
        int top = L - 1;
        while(top > 0 && a[top] == 0) top--;
        return top+1;
    }
    void clear(int top = -1){
        if (top == -1){
            top = length()-1;
        }
        for (int i=0;i<=top;i++){
            if (a[i] >= 0){
                a[i + 1] += a[i] / 10;
                a[i] %= 10;
            }else{
                a[i] = -a[i];
                a[i+1] -= ((a[i]-1) / 10 + 1);
                a[i] %= 10;
                if (a[i] == 0){
                    continue;
                }
                a[i] = (-a[i] + 10);
            }
        }
    }
    void left(int k=1){ //eq (*this /= 10^k);
        if (k < 0){
            return;
        }
        int s = this->length();
        for (int i=0;i<=s-k;i++){
            a[i] = a[i + k];
        }
        for (int i=s-k+1;i<=s;i++){
            a[i] = 0;
        }
    }
    void right(int k=1){//eq (*this *= 10^k);
        if (k < 0){
            return;
        }
        int s = this->length();
        for (int i=s-1;i>=0;i--){
            a[i+k] = a[i];
        }
        for (int i=0;i<k;i++){
            a[i] = 0;
        }
    }
    bool less(Bint A,Bint B){
        int sa = A.length()-1;
        int sb = B.length()-1;
        if (sa < sb){
            return 1;
        }else if (sa > sb){
            return 0;
        }else{
            for (int i=sa;i>=0;i--){
                if (A.a[i] < B.a[i]){
                    return 1;
                }else if (A.a[i] > B.a[i]){
                    return 0;
                }
            }
        }
        return 0;
    }
    void div_mod(Bint A,Bint B,Bint& d,Bint& m){
        if (B == 0){
            puts("Floating point exception");
            exit(136);
        }
        if (A < B){
            d = 0;
            m = A;
            return ;
        }
        d = 0;
        int sa = A.length()-1;
        int sb = B.length()-1;
        int ts = sa - sb + 1;
        B.right(ts-1);
        for (int i=ts;i>=1;i--){
            while(A >= B){
                A -= B;
                d.a[i-1]++;
            }
            B.left();
        }
        m = A;
    }
//operator
    bool operator < (const Bint B){
        return less(*this,B);
    }
    bool operator > (const Bint B){
        return less(B,*this);
    }
    bool operator <= (const Bint B){
        return !less(B,*this);
    }
    bool operator >= (const Bint B){
        return !less(*this,B);
    }
    bool operator == (const Bint B){
        return ((!less(*this,B)) && (!less(B,*this)));
    }
    Bint operator = (const string str){
        memset(a,0,sizeof(a));
        int len = (int)str.size();
        for (int  i = 0; i < len; i++) {
            a[i] = str[len - 1 - i] - '0';
        }
        return *this;
    }
    Bint operator = (const long long n){
        stringstream t;
        t<<n;
        string str;
        t>>str;
        return *this = str;
    }
    Bint operator + (const Bint B){
        const Bint& A = *this;
        Bint C;
        for (int i = 0; i < L; i++){
            C.a[i] = A.a[i] + B.a[i];
        }
        C.clear();
        return C;
    }
    Bint operator += (const Bint B){
        *this = *this + B;
        return *this;
    }
    Bint operator - (const Bint B) {
        const Bint& A = *this;
        Bint C;
        for (int i = 0; i < L; i++){
            C.a[i] = A.a[i] - B.a[i];
        }
        C.clear();
        return C;
    }
    Bint operator -= (const Bint B){
        *this = *this - B;
        return *this;
    }
    Bint operator * (const Bint B){
        Bint C;
        int topA = length()-1;
        int topB = B.length()-1;
        for (int i=0;i<=topA;i++){
            for (int j=0;j<=topB;j++){
                int num = a[i] * B.a[j];
                C.a[i+j] += num % 10;
                C.a[i+j+1] += num / 10;
            }
        }
        C.clear();
        return C;
    }
    Bint operator *= (Bint B){
        *this = *this * B;
        return *this;
    }
    Bint operator / (Bint B){
        Bint A = *this;
        Bint x,y;
        div_mod(A,B,x,y);
        return x;
    }
        
    Bint operator % (Bint B){
        Bint A = *this;
        Bint x,y;
        div_mod(A,B,x,y);
        return y;
    }
//outsideUse_function
    Bint pow(int x){
        if (x == 0){
            return 1;
        }
        if (x == 1){
            return *this;
        }
        Bint k = pow(x / 2);
        if (x % 2 == 0){
            return k * k;
        }else{
            return k * k * *this;
        }
    }
};
//outStruct_function&operator
ostream& operator << (ostream& out,Bint x){
    int top = x.length();
    for (int i = top-1; i >= 0; i--){
        out<<x.a[i];
    }
    return out;
}
    
istream& operator >> (istream& in,Bint& x){
    string s;
    if (!(in >> s)){
        return in;
    }
    x = s;
    return in;
}

Bint gcd (Bint A , Bint B) {
    return B == 0 ? A : gcd ( B , A % B );
}

const int L = 105;
Bint a[L];
Bint pub[L];
int n,l;

int main(){
    int T;
    scanf("%d",&T);
    repa (kase , T) {
        scanf("%d%d",&n,&l);   
        rep (i,l) cin >> a[i];

        int st = 0;
        while (a[st] == a[st + 1]) st++;
        Bint g = gcd(a[st] , a[st + 1]);
        pub[st] = a[st] / g;
        for (int i=st - 1;i>=0;i--) pub[i] = a[i] / pub[i + 1];
        for (int i=st + 1;i<=l;i++) pub[i] = a[i - 1] / pub[i - 1];

        vector < Bint > vt;
        rep (i , l + 1) vt.push_back(pub[i]);
        sort(vt.begin() , vt.end());
        unique(vt.begin() , vt.end());
        printf("Case #%d: ",kase);
        rep (i, l + 1) {
            char x = 'A';
            int j = 0;
            while (!(vt[j] == pub[i])) {
                j++;
                x++;
            }
            putchar(x);
        }
        puts("");
    }
    return 0;
}
