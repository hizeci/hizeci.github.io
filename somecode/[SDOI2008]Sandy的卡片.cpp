//P3193
#include <bits/stdc++.h>
#define y1 y1_
#define index index_
#define pipe pipe_
#define next next_
#define rgi register int
#define ll long long
#define Pi acos(-1.0)
#define lowbit(x) ((x&(-x)))
#define pb push_back
#define mk make_pair
#define pii pair<int,int>
#define fst first
#define scd second
using namespace std;
inline int read() {
    int f=1,x=0;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n,m,mo,next[30];
char s[30];
struct Matrix{
    int a[25][25];
    Matrix(){
        memset(a,0,sizeof(a));
    }
}G,F;
Matrix operator * (Matrix a,Matrix b) {
    Matrix ans;
    for(rgi i=0;i<m;++i) {
        for(rgi j=0;j<m;++j) {
            for(rgi k=0;k<m;++k) {
                ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j])%mo;
            }
        }
    }
    return ans;
}
Matrix QuickPow(Matrix di,int k) {
    Matrix ans;
    for(rgi i=0;i<=m;++i) ans.a[i][i]=1;
    while(k) {
        if(k&1) ans=ans*di;
        di=di*di;
        k>>=1;
    }
    return ans;
}
int main() {
//  freopen("","r",stdin);
//  freopen("","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);/*syn加速*/
    n=read();m=read();mo=read();
    scanf("%s",s+1);
    
    /*KMP和预处理出G*/
    int j=0;
    for(rgi i=1;i<m;++i) {
        while(j && s[j+1]!=s[i+1]) j=next[j];
        if(s[j+1]==s[i+1]) j++;
        next[i+1]=j;
    }
    
    for(rgi i=0;i<m;++i) {
        for(rgi ch='0';ch<='9';++ch) {
            int j=i;
            while(j && s[j+1]!=ch) j=next[j];
            if(s[j+1]==ch) j++;
            G.a[i][j]=(G.a[i][j]+1)%mo;
        }
    }

    /*快速幂*/
    G=QuickPow(G,n);
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++) printf("%lld ",G.a[i][j]);
            puts("");
    }
    F.a[0][0]=1; F=F*G;
    
    int sum=0;
    for(rgi i=0;i<m;++i) {
        sum=(sum+F.a[0][i])%mo;
    }
    cout<<sum<<endl;
    return 0;
}