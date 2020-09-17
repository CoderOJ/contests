#include <bits/stdc++.h>
using namespace std;
#define int long long
  
int n,m;
const int N = 100;
int a[N];
struct em{
    int b,c;
    bool operator < (em B) const{
        return b < B.b;
    }
}e[N];
  
bool judge(int x){
    em f[N];
    for (int i=1;i<=m;i++){
        f[i] = e[i];
    }
    int ia = 1;
    int ib = 1;
    for (;ia <= n;ia++){
        int tmp = x;
        while (f[ib].b <= a[ia] && ib != (m + 1)){
            //cout << x << ' ' << ia << ' ' << ib << ' ' << tmp << ' ' << f[ib].c << endl;
            if (f[ib].c <= tmp){
                tmp -= f[ib].c;
                //e[ib].c = 0;
                ib++;
            }else{
                f[ib].c -= tmp;
                tmp = 0;
                break;
            }
        }
    }
    return ib == (m + 1);
}
  
#undef int
int main(){
#define int long long
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> a[i];
    }
    cin >> m;
    for (int i=1;i<=m;i++){
        cin >> e[i].b;
    }
    int sum = 0;
    for (int i=1;i<=m;i++){
        cin >> e[i].c;
        sum += e[i].c;
    }
    sort(a + 1,a + n + 1);
    sort(e + 1,e + m + 1);
    int lower = 0,upper = sum;
    while (lower < upper){
        int mid = (lower + upper) / 2;
        if (!judge(mid)){
            lower = mid + 1;
        }else{
            upper = mid;
        }
    }
    if (lower == sum){
        puts("-1");
    }else{
        cout << lower << endl;
    }
    return 0;
}
