#include <bits/stdc++.h>
using namespace std;

const int N = 500005;
int a[N];

template <class T>
static void loopRead(T* f,T* t,string type = "~"){
    for (T* idx = f;idx < t;idx++){
        if (type == "~"){
            cin >> *idx;
        }else{
            scanf(type.c_str(),idx);
        }
    }
}

template <class T>
static void loopWrite(T* f,T* t,string type = "~"){
    for (T* idx = f;idx < t;idx++){
        if (type == "~"){
            cout << *idx << ' ';
        }else{
            printf(type.c_str(),*idx);
        }
    }
	cout << endl;
}

int main(){
	int n;
	cin >> n;
	loopRead(a+1,a+n+1,"%d");
	sort(a + 1,a + n + 1);
	//loopWrite(a + 1,a + n + 1);
	long long sum = 0;
	int ans = 0;
	for (int i=1;i<=n;i++){
		if (sum <= a[i] * 1LL){
			ans++;
			sum += a[i];
		}
	}
	cout << ans << endl;
	return 0;
}