#include<bits/stdc++.h>
using namespace std;
const int N=20;
int n=10;
int a[N];
signed main()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 rand_num(seed);  
	uniform_int_distribution<long long> dist(0, 10000);  // ¸ø¶¨·¶Î§
	printf("%lld ",dist(rand_num));
	printf("%lld ",dist(rand_num));

	return 0;
}
