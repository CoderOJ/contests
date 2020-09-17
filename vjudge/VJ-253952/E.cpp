#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
    int cs = 0;
    while (++cs){
        vector < pair < double , double > > p;
        int n,d;
        scanf("%d%d",&n,&d);
        if (n == 0 && d == 0){
            break;
        }
        double nps;
        int ans;
        for (int i=1;i<=n;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            if (d < y){
                for (int j=i + 1;j<=n;j++){
                    scanf("%d%d",&x,&y);
                }
                printf("Case %d: -1\n",cs);
                goto exception;
            }else{
                double tmp = 1.0 * d * d - 1.0 * y * y;
                tmp = sqrt(tmp);
                p.push_back ( pair < double , double > ( x + tmp , x - tmp ) );
            }
        }
        sort ( p.begin() , p.end() );
        nps = p[0].first;
        ans = 1;
        for (int i=1;i< ( int ) p.size();i++){
            if (nps < p[i].second){
                nps = p[i].first;
                ans++;
            }
        }
        printf("Case %d: %d\n",cs,ans);
        exception:;
    }
    return 0;
}
