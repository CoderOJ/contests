#include <bits/stdc++.h>
using namespace std;
#define ref(i,x,y)for(int i=x;i<=y;++i)
#define SZ(x) ((int)x.size())
int pr[35] = {
	2,3,5,7,11,
	13,17,19,23,29,
	31,37,41,43,47,
	53,59,61,67,71,
	73,79,83,89,97,
	101,103,107,109,113,
	127,131,137,139,149
};
vector<long long> a, b;
int main() {
  srand(time(NULL));
	a.push_back(137); a.push_back(139); a.push_back(149);
	//random_shuffle(pr+3,pr+30);
	int cnt = 0;
	ref(ti, 1, 8) {
		int n = SZ(a);
		int x = ti % n;
		b.clear();
		ref(i, x, n - 1)b.push_back(a[i]);
		ref(i, 0, x - 1)b.push_back(a[i]);
		a = b;
		if (n % 2 == 0) {
			ref(i, 0, n - 1)a.push_back(a[i]);
			ref(i, 0, n - 2)if (i & 1)a[i] *= pr[cnt]; else a[i] *= pr[cnt + 1];
			ref(i, n, n + n - 2)if (i & 1)a[i] *= pr[cnt + 1]; else a[i] *= pr[cnt];
			cnt += 2;
			a[0] *= pr[cnt + 1]; a[n] *= pr[cnt];
			a[n - 2] *= pr[cnt]; a[n - 1] *= pr[cnt + 1];
			a[n + n - 2] *= pr[cnt + 1]; a[n + n - 1] *= pr[cnt];
			cnt += 2;
		}
		else {
			ref(i, 0, n - 1)a.push_back(a[i]);
			ref(i, 0, n * 2 - 1) {
				if (i & 1)a[i] = a[i] * pr[cnt];
				else a[i] = a[i] * pr[cnt + 1];
			}
			cnt += 2;
		}
		//cout<<endl;
		//ref(i,0,SZ(a)-1)cout<<a[i]<<" ";cout<<endl;
	}
	a.pop_back();
	//ref(i, 0, SZ(a)-1)if(a[i]>1e18)exit(0);
	int nn;
	cin >> nn;
	a.resize(nn);
	ref(i, 0, SZ(a) - 1)cout << a[i] << " "; 
    cout << endl;
}
