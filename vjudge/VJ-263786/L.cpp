#include <bits/stdc++.h>
using namespace std;

struct bcj{
    static const int L = 1e2 + 5;
    int pt[L];
    bool tick[L];

    bcj(){
        for (int i=0;i<L;i++){
            pt[i] = i;
            tick[i] = 0;
        }
    }
    
    void clear(){
        for (int i=0;i<L;i++){
            pt[i] = i;
            tick[i] = 0;
        }
    }
    
    int find(int x){
        if (pt[x] == x){
            return x;
        }
        return pt[x] = find(pt[x]);
    }

    void add(int a,int b){
        tick[a] = 1;
        tick[b] = 1;
        int fa,fb;
        fa = find(a);
        fb = find(b);
        pt[fb] = fa;
    }
    
    bool uni(int a,int b){
        return (find(a) == find(b));
    }
    
    int sum(int x = L){
        int ans = 0;
        for (int i=1;i<=x;i++){
            if (pt[i] == i){
                ans++;
            }
        }
        return ans;
    }
};

struct edge{
    int f,t;
    double time;
    bool operator < (edge B){
        double a = this->time;
        double b =    B .time;
        return a < b;
    }
    edge(){};
    edge(int u,int v,double e):f(u),t(v),time(e){}
};


bcj book;
edge road[10005];

void reset_road(){
    for (int i=0;i<10005;i++){
        road[i].f = 0;
        road[i].t = 0;
        road[i].time = 0;
    }
}

typedef pair < int , int > point;

double getDis(point a,point b){
    int x = abs(a.first - b.first);
    int y = abs(a.second - b.second);
    return sqrt(x * x + y * y);
}

point pt[105];

void solve(int n){
    int sum = 0,m = 0;
    double ans = 0;
    for (int i=1;i<=n;i++){
	int x,y;
	scanf("%d%d",&x,&y);
	pt[i] = point(x,y);
    }
    for (int i=1;i<n;i++){
	for (int j=i+1;j<=n;j++){
	    double tmp = getDis(pt[i],pt[j]);
	    if (tmp >= 10 && tmp <= 1000){
		road[++m] = edge(i,j,tmp);
	    }
	}
    }

    sort(road + 1,road + m + 1);
    for (int i=1;i<=m;i++){
        int a = road[i].f;
        int b = road[i].t;
        if (!book.uni(a,b)){
            book.add(a,b);
            sum++;
            ans += road[i].time;
        }
    }
    //cout<<sum<<' '<<ans<<endl;
    if (sum < n - 1){
        cout<<"oh!"<<endl;
        return ;
    }
    printf("%.1lf\n",ans * 100);
}

int main(){
    int T;
    scanf("%d",&T);
    int n;
    while(T--){
        cin>>n;
        book.clear();
        reset_road();
        solve(n);
    }
    return 0;
}
