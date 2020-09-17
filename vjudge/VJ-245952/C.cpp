#include <bits/stdc++.h>
using namespace std;

const int ask[100] = {2,3,4,5,7,9,11,13,17,19,23,25,29,31,37,41,43,47,49};
const int ASK = 19;

int main(){
	int sum = 0;
	for (int i=0;i<ASK;i++){
		cout << ask[i] << endl;
		fflush(stdout);
		string s;
		cin >> s;
		if (s == "yes"){
			sum++;
		}
	}
	if (sum <= 1){
		cout << "prime" << endl;
	}else{
		cout << "composite" << endl;
	}
	return 0;
}