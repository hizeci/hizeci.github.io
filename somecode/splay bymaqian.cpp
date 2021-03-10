#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ls(x) T[x].ch[0]
#define rs(x) T[x].ch[1]
#define fa(x) T[x].fa
#define root T[0].ch[1]
using namespace std;
const int MAXN=1e5+10,mod=10007,INF=1e9+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
struct node
{
    int fa,ch[2],val,rec,sum;
}T[MAXN];
int tot=0,pointnum=0;
void update(int x){T[x].sum=T[ls(x)].sum+T[rs(x)].sum+T[x].rec;}
int ident(int x){return T[fa(x)].ch[0]==x?0:1;}
void connect(int x,int fa,int how){T[fa].ch[how]=x;T[x].fa=fa;}
void rotate(int x)
{
    int Y=fa(x),R=fa(Y);
    int Yson=ident(x),Rson=ident(Y);
    connect(T[x].ch[Yson^1],Y,Yson);
    connect(Y,x,Yson^1);
    connect(x,R,Rson);
    update(Y);update(x);
}
void splay(int x,int to)
{
    to=fa(to);
    while(fa(x)!=to)
    {
        int y=fa(x);
        if(T[y].fa==to) rotate(x);
        else if(ident(x)==ident(y)) rotate(y),rotate(x);
        else rotate(x),rotate(x);
    }
}
int newnode(int v,int f)
{
    T[++tot].fa=f;
    T[tot].rec=T[tot].sum=1;
    T[tot].val=v;
    return tot;
}
void Insert(int x)
{
    int now=root;
    if(root==0) {newnode(x,0);root=tot;}//
    else
    {
        while(1)
        {
            T[now].sum++;
            if(T[now].val==x) {T[now].rec++;splay(now,root);return ;}
            int nxt=x<T[now].val?0:1;
            if(!T[now].ch[nxt])
            {
                int p=newnode(x,now);
                T[now].ch[nxt]=p;
                splay(p,root);return ;
            }
            now=T[now].ch[nxt];
        }       
    }
}
int find(int x)
{
    int now=root;
    while(1)
    {
        if(!now) return 0;
        if(T[now].val==x) {splay(now,root);return now;}
        int nxt=x<T[now].val?0:1;
        now=T[now].ch[nxt];
    }
}
void delet(int x)
{
    int pos=find(x);
    if(!pos) return ;
    if(T[pos].rec>1) {T[pos].rec--,T[pos].sum--;return ;} 
    else
    {
        if(!T[pos].ch[0]&&!T[pos].ch[1]) {root=0;return ;}
        else if(!T[pos].ch[0]) {root=T[pos].ch[1];T[root].fa=0;return ;}
        else
        {
            int left=T[pos].ch[0];
            while(T[left].ch[1]) left=T[left].ch[1];
            splay(left,T[pos].ch[0]);
            connect(T[pos].ch[1],left,1); 
            connect(left,0,1);//
            update(left);
        }
    }
}
/*
int rak(int x)
{
    int now=root,ans=0;
    while(1)
    {
        if(T[now].val==x) return ans+T[T[now].ch[0]].sum+1;
        int nxt=x<T[now].val?0:1;
        if(nxt==1) ans=ans+T[T[now].ch[0]].sum+T[now].rec;
        now=T[now].ch[nxt];
    }
}
*/
int rak(int val)
{
    int pos=find(val);
    return T[ls(pos)].sum+1;
}
int kth(int x)//排名为x的数 
{
    int now=root;
    while(1)
    {
        int used=T[now].sum-T[T[now].ch[1]].sum;
        if(T[T[now].ch[0]].sum<x&&x<=used) {splay(now,root);return T[now].val;}
        if(x<used) now=T[now].ch[0];
        else now=T[now].ch[1],x-=used;
    }
}
int lower(int x)
{
    int now=root,ans=-INF;
    while(now)
    {
        if(T[now].val<x) ans=max(ans,T[now].val);
        int nxt=x<=T[now].val?0:1;//这里需要特别注意 
        now=T[now].ch[nxt];
    }
    return ans;
}
int upper(int x)
{
    int now=root,ans=INF;
    while(now)
    {
        if(T[now].val>x) ans=min(ans,T[now].val);
        int nxt=x<T[now].val?0:1;
        now=T[now].ch[nxt];
    }
    return ans;
}
int main()
{
    int N=read(),M=read();
    for(int i=1;i<=N;i++) {int x=read();Insert(x);}
    while(M--)
    {
        int opt=read(),x=read();
        if(opt==1) Insert(x);
        else if(opt==2) delet(x);
        else if(opt==3) printf("%d\n",rak(x));
        else if(opt==4) printf("%d\n",kth(x));
        else if(opt==5) printf("%d\n",lower(x));
        else if(opt==6) printf("%d\n",upper(x));
    } 
    return 0;
}