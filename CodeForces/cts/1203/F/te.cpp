    #include <iostream>
    #include <map>
    #include <algorithm>
     
    using namespace std;
     
    int main() {
    	map<int, int> m;
    	int rating, delta = 0, need = 0, n;
    	cin >> n >> rating;
    	while (n-- > 0) {
    		int x, d;
    		cin >> x >> d;
    		if (d > 0) m[x] += d;
    		delta += d;
    		need = max(need, x);
    	}
    	if (rating + delta >= 0) {
    		for (auto &x: m) {
    			if (rating < x.first) {
    				cout << "NO" << endl;
    				return 0;
    			}
                cout << x.first << ' ' << x.second << endl;
    			rating += x.second;
    		}
    		if (rating >= need) {
    			cout << "YES" << endl;
    			return 0;
    		}
    	}
    	
    	cout << "NO" << endl;
    	return 0;
    }


