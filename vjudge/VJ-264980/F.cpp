#include <bits/stdc++.h>
using namespace std;
#define fom(a,b) for(int a=0;a<(int)b.size();a++)
#define pii pair < int , int >

const int N = 205;
vector < int > e[N];

pii dfs(int root,int pre,int ng){
    pii ans(0,root);
    fom(i,e[root]){
        int v = e[root][i];
        if (v != pre && v != ng){
            pii foo = dfs(v,root,ng);
            foo.first++;
            ans = max(ans,foo);
        }
    }
    return ans;
}

int main(){
    int n;
    scanf("%d",&n);
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int ans = 0;
    for (int i=1;i<=n;i++){
        fom(j,e[i]){
            int v = e[i][j];
            pii a1 = dfs(i,v,v);
            pii a2 = dfs(v,i,i);
            pii s1 = dfs(a1.second,v,v);
            pii s2 = dfs(a2.second,i,i);
            ans = max(ans,s1.first * s2.first);
        }
    }
    printf("%d\n",ans);
    return 0;
}
