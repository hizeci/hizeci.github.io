#include <cstdio>
#include <iostream>
#define ll long long
using std::max;

const int MAXN =2e5+20, MAXT =1<<19;

/*------------------------------Array------------------------------*/

int a[MAXN];
ll s[MAXN];

/*------------------------------Seg------------------------------*/

int N =1;
ll mx[MAXT];

/*s_r-2s_{r-1} \geq s_{l-1}-2s_l*/
void query(const int &l, const int &r, const int &pos, int &ans, const int &nl =1, const int &nr =N, const int x =1){
	int mid =(nl+nr)>>1;
	if(nl == nr){
		if(nl-pos >= 2 && (a[pos]^a[nl]) == s[nl-1]-s[pos+1 -1])
			++ans;
	}
	else if(l == nl && r == nr){
		if(mx[x<<1] >= s[pos-1]-2*s[pos])
			query(nl, mid, pos, ans, nl, mid, x<<1);
		if(mx[x<<1^1] >= s[pos-1]-2*s[pos])
			query(mid+1, nr, pos, ans, mid+1, nr, x<<1^1);
	}
	else{
		if(r <= mid)
			query(l, r, pos, ans, nl, mid, x<<1);
		else if(l >= mid+1)
			query(l, r, pos, ans, mid+1, nr, x<<1^1);
		else
			query(l, mid, pos, ans, nl, mid, x<<1), query(mid+1, r, pos, ans, mid+1, nr, x<<1^1);
	}
}

inline void pushup(const int &x){
	mx[x] =max(mx[x<<1], mx[x<<1^1]);
}

/*------------------------------Main------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

int main(){
	int n =read();
	for(int i =1; i <= n; ++i)
		a[i] =read(), s[i] =s[i-1]+a[i];
	
	while(N < n)
		N <<=1;
	for(int i =N; i < N+n; ++i)
		mx[i] =s[i-N+1]-2*s[(i-N+1)-1];
	for(int i =N+n; i < N*2; ++i)
		mx[i] =-0x3f3f3f3f3f3f3f3f;
	for(int i =N-1; i >= 1; --i)
		pushup(i);
	
	int ans =0;
	for(int l =1; l <= n; ++l)
		query(l, n, l, ans);
	printf("%d", ans);
}