#include <bits/stdc++.h>
using namespace std;

const long long N = 100005;
long long di[N];
long long vdi[N];
vector <long long> le[N];
vector <long long> ri[N];
multiset <long long> st;
long long va[N];
long long dp[505];

long long bag(long long k,long long n){
    memset(dp,0,sizeof(dp));
    //long long ans = 0;
    for (long long i=1;i<n;i++){
        long long vl = va[i];
        for (long long j=k;j>=vl;j--){
            dp[j] = max(dp[j],dp[j-vl] + vdi[i]);
            //ans = max(ans,dp[i][j]);
        }
    }
    return dp[k];
}

int main(){
    long long T;
    scanf("%lld",&T);
    while (T--){
        long long sum = 0;
        st.clear();
        long long n,k,m;
        scanf("%lld%lld%lld",&n,&k,&m);
        for (long long i=1;i<=n;i++){
            le[i].clear();
            ri[i].clear();
        }
        for (long long i=1;i<=n;i++){
            long long read;
            scanf("%lld",&read);
            di[i] = read;
            sum += read;
        }
        for (long long i=1;i<=m;i++){
            long long a,b,c;
            scanf("%lld%lld%lld",&a,&b,&c);
            le[a].push_back(c);
            ri[b].push_back(c);
        }
        long long idx = 1;
        for (long long i=1;i<=n;i++){
            //cout<<"#"<<i<<' '<<le[i].size()<<' '<<ri[i].size()<<endl;
            for (long long j=0;j<(long long)le[i].size();j++){
                st.insert(le[i][j]);
            }
            //for (multiset <int> :: iterator it = st.begin();it != st.end();++it){
          //      cout<<*it<<' ';
        //    }
      //      cout<<endl;
            if (!st.empty() && di[i] < 0){
                va[idx] = *st.begin();
                vdi[idx++] = -di[i];
            }
            for (long long j=0;j<(long long)ri[i].size();j++){
                st.erase(st.find(ri[i][j]));
            }
        }
    //    for (long long i=0;i<idx;i++){
  //          cout<<va[i]<<' '<<vdi[i]<<endl;
//        }
        printf("%lld\n",sum + bag(k,idx));
    }
    return 0;
}
