#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;

inline void delet(string& s,int f,int t){
    s = s.substr(0,f) + s.substr(t + 1);
}

bool solve(string s,string t){
    for (int i=0;i<(int)t.length();i++){
	if (s.length() < t.length() || (s.length() == t.length() && s != t)){
	    return 0;
	}
	if (s[i] != t[i]){
	    if (s[i] == '('){
		int tmp = i;
		int ck = 0;
		while (ck || tmp == i){
		    if (s[tmp] == '('){
			ck ++;
		    }else{
			ck --;
		    }
		    tmp++;
		}
		delet(s,i,tmp - 1);
//		cout << tmp - 1 << endl;
		i --;
	    }else{
		int tmp = i;
		int ck = 0;
		while (ck || tmp == i){
		    if (s[tmp] == ')'){
			ck ++;
		    }else{
			ck --;
		    }
		    tmp --;
		}
		delet(s,tmp + 1,i);
		i = 1;
		// cout << i << endl;
	    }
	}
    }
//    cout << s.length() << ' ' << t.length() << endl;
    return s.length() == t.length();
}

int main(){
    string s,t;
    cin >> s >> t;
    cout << (solve(s,t)?"Possible":"Impossible") << endl;    
    return 0;
}
