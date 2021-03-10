#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x,I=y+1;i<I;++i)
#define per(i,x,y) for(int i=x,I=y-1;i>I;--i)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}
template<class T>istream&operator>>(istream&in,vector<T>&V){for(auto&x:V)in>>x;return in;}
template<class T>ostream&operator<<(ostream&out,const vector<T>&V){for(auto x:V)out<<x<<' ';return out;}
template<class T>void sort(vector<T>&V){sort(V.begin(),V.end());}
template<class T>void reverse(vector<T>&V){reverse(V.begin(),V.end());}
template<class T>int SZ(const vector<T>&V){return (int)V.size();}
void debug(){cerr<<"whxorz"<<'\n';}

const int N = 200000 + 5;
int n, a[N];
int L[N], R[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	static int st[N], top;
	st[top = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (top && a[st[top]] < a[i]) { R[st[top--]] = i; }
		L[i] = st[top]; st[++top] = i;
	}
	while (top) R[st[top--]] = n + 1;
	for (int i = 1; i <= n; i++) {
		L[i]++;
		R[i]--;
		printf("L[%lld]:%lld R[%lld]:%lld \n",i,L[i],i,R[i]);
	}

	static int tmpL[N], tmpR[N], tmp[32];
	for (int i = 1; i <= n; i++) tmpL[i] = 0;
	for (int j = 0; j < 31; j++) tmp[j] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 31; j++)
			if (a[i] >> j & 1)
				tmp[j] = i;
			else
				cmax(tmpL[i], tmp[j]);
	}
	for (int i = 1; i <= n; i++) tmpR[i] = n + 1;
	for (int j = 0; j < 31; j++) tmp[j] = n + 1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < 31; j++)
			if (a[i] >> j & 1)
				tmp[j] = i;
			else
				cmin(tmpR[i], tmp[j]);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (L[i] <= tmpL[i])
			ans += 1ll * (R[i] - i + 1) * (tmpL[i] - L[i] + 1);
		if (tmpR[i] <= R[i])
			ans += 1ll * (i - L[i] + 1) * (R[i] - tmpR[i] + 1);
		if (L[i] <= tmpL[i] && tmpR[i] <= R[i])
			ans -= 1ll * (tmpL[i] - L[i] + 1) * (R[i] - tmpR[i] + 1);
	}
	cout << ans << '\n';
	return 0;
}