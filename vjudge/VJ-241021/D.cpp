#include <bits/stdc++.h>
using namespace std;

const int N = 5000005;
int a[N];
char cd[N];
int n1[N];
int ans [N];
int que[N];
int qti[N];
int res[N];

inline int get(int a,int b){
    return n1[b] - n1[a - 1];
}

inline void checkMax(int& a,int b){
    if (b > a){
        a = b;
    }
}

int main(){
    int n,k,p;
    scanf("%d%d%d",&n,&k,&p);
    
    if (k > n){
        k = n;
    }  
    
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n] = a[i];
    }
    for (int i=1;i<=n * 2;i++){
        n1[i] = n1[i - 1] + a[i];
    }
    scanf("%s",cd);
    int loop = n * 2 - k + 1;
    for (int i=1;i<=loop;i++){
        ans[i] = get(i,i+k-1);
    }
    
    int f = 1;
    int t = 0;
    int len = n - k + 1;
    
    for (int i=1;i<len;i++){
        while (t >= f && que[t] < ans[i]){
            t--;
        }
        que[++t] = ans[i];
        qti[  t] =   i ;
    }
//    for (int i=f;i<=t;i++){
//        printf("%d ",que[i]);
//    }
//    puts("x");
    for (int i=len;i<=loop;i++){
        while  (t >= f && qti[f] + n - k < i ){
            f++;
        }
        while (t >= f && que[t] < ans[i]){
            t--;
        }
        que[++t] = ans[i];
        qti[  t] =   i ;
        res[i - len + 1] = que[f];
//        cout<<'#'<<i<<" :"<<endl;
//        for (int i=f;i<=t;i++){
//            printf("%d ",que[i]);
//        }
//        puts("x");
    }
    
//    puts("pass");
    
    int st = 1;
    for (int i=0;i<p;i++){
        if (cd[i] == '!'){
            st--;
            if (st == 0){
                st = n;
            }
        }else{
            printf("%d\n",res[st]);
        }
    }
    puts("");
    return 0;
}
