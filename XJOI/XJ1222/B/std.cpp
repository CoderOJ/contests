#include<bits/stdc++.h>
#define IL inline
#define RI register int
using namespace std;
IL void in(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s>'9' or s<'0'){if(s=='-')f=-1;s=getchar();}
    while(s>='0' and s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int k,v,n,ans,cnt,now[55];
int V[288],W[288],f[5008][55];
int main()
{
    in(k),in(v),in(n);
    for(RI i=0;i<=5000;i++)
        for(RI j=0;j<=50;j++)f[i][j]=-20021003;//赋初值为-inf
    f[0][1]=0;//体积为0的最优解为0.
    for(RI i=1;i<=n;i++)
        in(V[i]),in(W[i]);//V[i]为体积,W[i]为价值.
    for(RI i=1;i<=n;i++)
        for(RI j=v;j>=V[i];j--)
        {
            int c1=1,c2=1,cnt=0;
            while(cnt<=k)
            {
                if(f[j][c1]>f[j-V[i]][c2]+W[i])
                now[++cnt]=f[j][c1++];
                else now[++cnt]=f[j-V[i]][c2++]+W[i];
            }
            for(RI c=1;c<=k;c++)f[j][c]=now[c];
        }
    for(RI i=1;i<=k;i++)ans+=f[v][i];
      for(RI c=1;c<=k;c++)printf("%d ",f[v][c]);
    printf("%d",ans);
}
