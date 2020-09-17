#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#endif
#ifndef __LOCALE__
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif

int rb[1000][1000];
const int N = 100005;
int pt[N],flag[N],fstApr[N];

void init(){
    for (int i=1;i<=N;i++){
        pt[i] = i;
    }
}

int getParent(int u){
    return pt[u] == u ? u : ( pt[u] = getParent(pt[u]) );   
}

void merge(int u,int v){
    pt[getParent(u)] = getParent(v);
}

int main(){
    init();
    int n,m;
    scanf("%d%d",&n,&m);
    see(n);see(m);
    for (int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        merge(u,v);
    }
    for (int i=1;i<=n;i++){
        int foo = getParent(i);
        if (flag[foo]){
            puts("YES");
            cout << fstApr[foo] << ' ' << i << endl;
            return 0;
        }else{
            flag[foo] = 1;
            fstApr[foo] = i;
        }
    }
    puts("NO");
    return 0;
}
