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
        return (pt[a] == pt[b]);
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
    int f,t,time;
    bool operator < (edge B){
        int a = this->time;
        int b =    B .time;
        return a < b;
    }
};

istream& operator >> (istream& in,edge& A){
    int a,b,c;
    in>>a>>b>>c;
    A.f = a;
    A.t = b;
    A.time = c;
    return in;
}

bcj book;
edge road[10005];

void reset_road(){
    for (int i=0;i<10005;i++){
        road[i].f = 0;
        road[i].t = 0;
        road[i].time = 0;
    }
}

void solve(int n,int m){
    int sum = 0,ans = 0;
    for (int i=1;i<=m;i++){
        cin>>road[i];
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
        cout<<"?"<<endl;
        return ;
    }
    cout<<ans<<endl;
}

int main(){
    int n,m;
    while(1){
        cin>>n;
        book.clear();
        reset_road();
        if (n == 0){
            return 0;
        }
        solve(n * (n - 1) / 2,n);
    }
    return 0;
}
