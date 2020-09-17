#include <bits/stdc++.h>
#define int long long
#define debug(x) std::cout<<#x<<"="<<x<<std::endl;

inline int calc(int f,int t){
    if (f > t){
	std::swap(f,t);
    }
    return (f + t) * (t - f + 1) / 2;
}

#undef int
int main(){
#define int long long

    int d1,d2,w1,w2;
    scanf("%lld%lld%lld%lld",&d1,&d2,&w1,&w2);
    int lower = 0,upper = w1;
    while (lower < upper){
	int mid = (lower + upper + 1) / 2;
	int foo = calc(mid,std::max(0LL,mid - d1 + 1));
	if (foo <= w1){
	    lower = mid;
	}else{
	    upper = mid - 1;
	}
    }
    int up = lower;
    lower = 0;upper = w1;
    while (lower < upper){
	int mid = (lower + upper) / 2;
	int foo = calc(mid,mid + d1 - 1);
	if (foo >= w1){
	    upper = mid;
	}else{
	    lower = mid + 1;
	}
    }
    int low = lower;
    if (low != 0){
	low --;
    }
    up ++ ;
    int left  = calc(low,std::max(0LL,low - d2 + 1));
    int right = calc(up ,             up  + d2 - 1 );
    if (left <= w2 && right >= w2){
	puts("Possible");
    }else{
	puts("Impossible");
    }
    return 0;
}
