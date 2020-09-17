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

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)

const int N = 5005;
int a[N];
int sum[N];
int start[N];
int n,k;

void init(){
    cin >> n >> k;
    for (int i=1;i<=n;i++){
        cin >> a[i];
    }
}

void makeSum(){
    for (int i=1;i<=n;i++){
        sum[a[i]]++;
    }
}   

void makeStart(){
    int st = 1;
    for (int i=1;i<=5000;i++){
        if (sum[i] > k){
            puts("NO");
            exit(0);
        }
        start[i] = min(st,k - sum[i] + 1);
        st += sum[i];
    }
    puts("YES");
}

void solve(){
    for (int i=1;i<=n;i++){
        cout << start[a[i]] << ' ';
        start[a[i]] ++;
    }
    puts("");
}

int main(){
    init();
    makeSum();
    makeStart();
    solve(); 
    return 0;
}
