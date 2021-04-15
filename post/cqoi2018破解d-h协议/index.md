
<!--more-->

题意：

先给定一个固定的质数$P$以及模$P$的一个原根$g$。

多组测试数据，每次给定给定两个整数$A,B$，其中$A=g^x \pmod P,B=g^y \pmod P$，求出$g^{xy} \pmod P$的值

大概就是直接暴力解同余方程求出$x,y$然后算$g^{xy}\bmod P$即可。

然后可以发现$x,y$只要求出一个就可以，比如解出$x$之后算$B^x$。



然后因为是多次数据，而$P$和$g$已经给定了。

原来的方程为$g^x\equiv A\pmod P$，设$x=i\times \sqrt{P}-j$
$$
\frac{g^{i\sqrt{P}}}{g^j\cdot A}\equiv 1 \pmod P 
$$

$$
0<i \leq \sqrt{P} ,0\leq j< \sqrt P
$$



考虑预处理出分子部分，丢到哈希表中。每次查询时枚举$A\cdot g^j$。

```c++
inline void writeln(ll x){write(x);putchar('\n');}
const int N=1145141;
const int hst_mod=173219;
struct hash_map_t
{
    int head[hst_mod+10],cnt;
    struct edge {int nxt,key,val;}e[N<<1];
    inline int ser(int key)
    {
        int u=key%hst_mod;
        for(int i=head[u];i;i=e[i].nxt) if(key==e[i].key) return e[i].val;
        return -1;
    } 
    inline int ins(int key,int val)
    {
        if(ser(key)!=-1) return -1;
        int u=key%hst_mod;e[++cnt]=(edge){head[u],key,val};head[u]=cnt;
        return val;
    }
    inline int modify(int key,int val)
    {
        if(ser(key)==-1) return ins(key,val);
        int u=key%hst_mod;
        for(int i=head[u];i;i=e[i].nxt) if(e[i].key==key) return e[i].val=val;
    }
    inline void clear() {R(i,1,cnt) head[e[i].key%hst_mod]=e[i].nxt=0;cnt=0;}
}mp;

int P,g;
int n;
int A,B;
#define lll __int128 
inline int qpow(int a,int b,int p) {int ans=1;while(b){if(b&1)ans=(lll)ans*a%p;a=(lll)a*a%p;b>>=1;}return ans;}
signed main()
{
	g=read(),P=read();
	int sq=1;
	for(;sq*sq<=P;sq++);
	//	printf("sq:%lld\n",sq);
	int ff=qpow(g,sq,P);
	int mu=ff,pos;
 	R(i,1,sq) mp.ins(mu,i*sq),mu=mu*ff%P;
 	for(int _=read();_;_--)
 	{
 		A=read(),B=read();
 		mu=A;
 		R(j,0,sq-1) 
 		{
 			pos=mp.ser(mu);
 			if(pos!=-1) 
 			{ 			
 				//printf("j:%lld pos:%lld\n",j,pos);
 				writeln(qpow(B,pos-j,P));
 				break;
 			}
 			mu=mu*g%P;
 		}
 	}
}
```

