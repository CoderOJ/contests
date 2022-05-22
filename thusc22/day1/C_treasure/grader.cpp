#include<cstdlib>
#include<cstdio>
int main(){
	system("g++ Alice.cpp main.cpp -o Alice -O2 -std=c++17");
	system("g++ Bob.cpp main.cpp -o Bob -O2 -std=c++17");
	puts("Alice:");
	system("./Alice >treasure.tmp");
	puts("Bob:");
	system("./Bob <treasure.tmp");
	return 0;
}
