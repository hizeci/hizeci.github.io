#include<bits/stdc++.h>
using namespace std;
const int N=2000000;

signed main()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 rand_num(seed);  
	uniform_int_distribution<long long> dis(0, 200000);  // 赂酶露篓路露脦搂
	uniform_int_distribution<long long> dist(0, (int)1e9);
	int n=20,k=dis(rand_num)%n+1;
	for(int i=1;i<=20;i++) printf("%lld\n",dist(rand_num));
	//printf("%lld ",dist(rand_num));
	//printf("%lld ",dist(rand_num));

	return 0;
}