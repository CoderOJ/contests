#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
ll n,m,dp[20][10],ans;
string a[55],b[55];
bool cleann[55];
int main()
{
    scanf("%lld%lld",&n,&m);
    ans=(ll)pow(10LL,n);
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            if(i==j||a[i].size()>a[j].size())continue;
            bool check=0;
            for(int k=0;k<a[i].size();k++){
                if(a[i][k]!=a[j][k]){
                    check=1;
                    break;
                }
            }
            if(check==0)cleann[j]=1;
        }
    }
    for(int i=1;i<=m;i++){
        if(cleann[i]==0)ans-=(ll)pow(10LL,n-a[i].size());
    }
    printf("%lld",ans);
    return 0;
}
