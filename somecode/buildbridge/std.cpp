#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[100001],h[100001],s[100001];
struct node{
    int at;
    ll x,y;
}b[550000];//���������һ���������ʡ�ڴ�
inline ll mmin(const ll &x,const ll &y){
    return x<y?x:y;
}
inline bool chk(const node &n1,const node &n2,const node &n3){
    return n3.x==n2.x?n3.y<=n2.y:(n3.y-n2.y)*(n2.x-n1.x)<=(n2.y-n1.y)*(n3.x-n2.x);
}
struct stk{
    int h,t;//head��tail (tail��������βָ�룩
    bool ext;//�����Ƿ����
    inline void add(const node &x){
        while(t>h&&chk(b[t-1],b[t],x))--t;
        if(t>=h&&x.x==b[t].x)
            if(x.y>b[t].y)return;
            else --t;
        b[++t]=x;
    }
    inline node qus(const ll &k){//�������
        int l=h,r=t,mid;
        while(l<r){
            mid=l+r>>1;
            if(k*(b[mid+1].x-b[mid].x)>b[mid+1].y-b[mid].y)l=mid+1;
            else r=mid;
        }
        return b[l];
    }
}q[18],z,mr;
inline void cpy(stk &x,const stk &y){//һ��Ҫע���ǰ����ݸ��ƹ�ȥ����ֱ�Ӹ�head��tail
    x.t=x.h-1;
    for(int j=y.h;j<=y.t;++j)
        b[++x.t]=b[j];
}
inline void mrg(const int &at){//�ϲ�������
    mr.h=400001,mr.t=400000;
    for(int i=z.h,j=q[at].h;i<=z.t||j<=q[at].t;)
        if(i>z.t||(j<=q[at].t&&b[i].x>b[j].x))mr.add(b[j]),++j;
        else mr.add(b[i]),++i;
    cpy(z,mr);
}
int sum=-1;
inline void psh(const node &x){//�����Ʒ���Ĳ���
    z.h=265001,z.t=265000,z.ext=1;
    z.add(x);
    int at=0;
    while(at<=sum&&q[at].ext){
        q[at].ext=0;
        mrg(at);
        ++at;
    }
    if(at==sum+1)++sum;
    cpy(q[at],z);
    q[at].ext=1;
}
inline node fnd(const ll &k){//�����Ʒ���Ĳ���
    node ans;
    int at=0;
    while(!q[at].ext)++at;
    ans=q[at].qus(k);
    while(++at<=sum){
        const node &t=q[at].qus(k);
        if(t.y-k*t.x<ans.y-k*ans.x)ans=t;
    }
    return ans;
}
inline int rd(){//���
    register int x=0,f=1;
    register char c=getchar();
    while(c!='-'&&(c<'0'||c>'9'))c=getchar();
    if(c=='-')f=0,c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?x:-x;
}
void pt(const ll &x){//��д
    if(x>9)pt(x/10);
    putchar((x%10)|48);
}
int main(){
    register int n;
    n=rd();
    for(int i=0;i<18;++i)q[i].h=1<<i;
    for(register int i=1;i<=n;++i)h[i]=rd();
    for(register int i=1;i<=n;++i)s[i]=rd()+s[i-1];
    psh((node){1,h[1],h[1]*h[1]-s[1]});//�Ȱѵ�1���������⴦����Ϊ������Ҫ�κδ��۾����Լ����ӣ�
    for(register int i=2;i<=n;++i){
        const node &now=fnd(2*h[i]);
        dp[i]=now.y+s[i-1]+h[i]*(h[i]-(now.x<<1));
        psh((node){i,h[i],dp[i]+h[i]*h[i]-s[i]});
    }
    if(dp[n]<0)putchar('-'),dp[n]=-dp[n];//�������
    pt(dp[n]);
    return 0;
}
