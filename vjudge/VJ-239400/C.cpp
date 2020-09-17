#include <bits/stdc++.h>
using namespace std;

const int N = 2000005;
long long dm[N];
long long sum[N];
long long ans[N];
 
void make_dm(){
    for (int i=2;i<N-4;i++){
        int foo = i;
        int p1 = 0;
        int p2 = 0;
        while (foo != 0){
            if (foo % 2 == 0){
                p2 += foo % 10;
            }else{
                p1 += foo % 10;
            }
            foo /= 10;
        }
        dm[i] = abs(p1 - p2);
    }
}

void make_sum(){
    for (int i=1;i<N-4;i++){
        sum[i] = sum[i - 1] + dm[i];
    }
}
 
long long get(long long f,long long t){
    return sum[t] - sum[f - 1];
}

void make_ans(){
    for (int i=1;i<N-4;i++){
        long long add = get(i + 1,2 * i) * 2 - get(i * 2,i * 2);
        ans[i] = ans[i - 1] + add;
    }
}

int main(){
    make_dm();
    make_sum();
    make_ans();
    int T;
    scanf("%d",&T);
    while (T--){
        int read;
        scanf("%d",&read);
        printf("%lld\n",ans[read]);
    }
    return 0;
}
