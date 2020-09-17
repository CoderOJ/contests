#include <bits/stdc++.h>
using namespace std;

const string TO = "SANTA";

int find_last(string s,char a){
    for (int i=s.length() - 1;;i--){
	if (s[i] == a){
	    return i;
	}
    }
}

string solve(string str,string t){
    int fd = 0;
    for (int i=0;i<(int)str.length();i++){
	if (str[i] == t[fd]){
	    fd++;
	}
    }
    if (fd == 0){
	return str + "SA";
    }else if (fd == 1){
	return str + "A";
    }else {
	return str;
    }
}

int main(){
    string str;
    cin >> str;
    if (str.find("N") == string::npos){
	cout << TO << str << endl;
    }else{
	int pos = find_last(str,'N');
	// cout << str.substr(0,pos) << endl << str.substr(pos,str.length() - pos) << endl;
	cout << solve(str.substr(0,pos),"SA0") << str.substr(pos,str.length() - pos) << "TA" << endl; 
    }
    return 0;
}
