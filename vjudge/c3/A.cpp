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

#define int long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)

void init(){
     
}

#undef int
int main(){
#define int long long
    init();
    int n;
    cin >> n;
    cout << ( 1LL * (n + 1) * n / 2 ) % 2 << endl;
    return 0;
}
