#include <bits/stdc++.h>
using namespace std;

long long n,k,m,x,s;

struct ljb{
    static const long long N = 1000005;
    long long fst[N];
    long long pt[N];
    long long nxt[N];
    long long dis[N];
    long long e;

    void clear(){
        e = 0;
        memset(fst,-1,sizeof(fst));
        memset(nxt,-1,sizeof(nxt));
        memset(pt,-1,sizeof(pt));
        memset(dis,0,sizeof(dis));
    }

    void add(long long a,long long b,long long _dis){
        nxt[e] = fst[a];
        fst[a] = e;
        pt[e] = b;
        dis[e] = _dis;
        e++;
    }

    void multiAdd(long long a,long long b,long long d){
        add(a,b,d);
        add(b,a,d);
    }
};

ljb mp;

long long d[ljb::N];
long long book[ljb::N];

void init(){
    memset(d,0x3f,sizeof(d));
    memset(book,0,sizeof(book));
}

priority_queue < pair < long long , long long > > heap;

template <class Ty>
void clear(priority_queue < Ty > & x){
    while (!x.empty()){
        x.pop();
    }
}

void solve(long long st,long long n){
    init();
    clear(heap);
    d[st] = 0;
    heap.push(make_pair(0,st));
    book[st] = 1;
    while (!heap.empty()) {
        //cout<<heap.size()<<endl;
        long long w ;
        if (-heap.top().first > d[heap.top().second]){
            heap.pop();
            continue;
        }
        //d[heap.top().second] = -heap.top().first;

        w = heap.top().second;
        heap.pop();

        book[w] = 1;
        for (long long j=mp.fst[w];j!=-1;j=mp.nxt[j]){
            long long t = mp.pt[j];
            long long ndis = d[w] + mp.dis[j];
            if (book[t] == 0 && d[t] > ndis){
                d[t] = ndis;
                heap.push(make_pair(-ndis,t));
            }
        }
    }
    for (long long i=1;i<=n;i++){
        printf("%lld ",d[i] / 2);
    }
    puts("");
}

int main(){
    long long T;
    scanf("%lld",&T);
    while (T--){
        mp.clear();
        scanf("%lld%lld%lld%lld%lld",&n,&k,&x,&m,&s);
        for (long long i=1;i<=m;i++){
            long long pa,pb,pd;
            scanf("%lld%lld%lld",&pa,&pb,&pd);
            mp.multiAdd(pa,pb,pd * 2);
        }
        for (long long i=1;i<=k;i++){
            mp.multiAdd(0,i,x);
        }
        solve (s,n);
    }
    return 0;
}
