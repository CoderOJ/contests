#include<cstdlib>
#include<cstdio>
int main(){
	system("g++ Alice.cpp treasure.cpp -o Alice -O2 -std=c++14 -Wl,--stack=1000000000");
	system("g++ Bob.cpp treasure.cpp -o Bob -O2 -std=c++14 -Wl,--stack=1000000000");
	puts("Alice:");
	system("Alice >treasure.tmp");
	puts("Bob:");
	system("Bob <treasure.tmp");
	return 0;
}
