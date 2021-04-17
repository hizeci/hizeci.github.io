
<!--more-->

题意：

给定五个整数$p,a,b,x_1,t$满足$0<a,b,x_1<p$，求是否存在按照下面公式生成的数是否有最小的$n$满足$t=x_{n}$
$$
x_{i+1}= a\cdot x_i+b\bmod p
$$
分类讨论

- $a=0$时，直接判断$b=t$。

- $a=1$时，$x$为等差数列$x_n=x_1+(n-1)\cdot b$，求$x_1+(n-1)\cdot b\equiv t\pmod p$的最小非负整数解，扩欧求解。

- $a\ge 1$时。

  有
  $$
  x_{i+1}+\frac{b}{a-1}=a(x_i+\frac{b}{a-1})
  $$
  那么数列$y_n=x_n+\frac{b}{a-1}$为一个公比是$a$的等比数列
  $$
  y_n=(x_1+\frac{b}{a-1})a^{n-1}
  $$
  则有
  $$
  x_n=(x_1+\frac{b}{a-1})a^{n-1}- \frac{b}{a-1}
  $$
  即
  $$
  t\equiv (x_1+\frac{b}{a-1})a^{n-1}-\frac{b}{a-1}\pmod p 
  $$
  化简
  $$
  a^{n-1}\equiv \frac{(a-1)t+b}{(a-1)x_1+b} \pmod p
  $$
  BGSG求解
  
  ```c++
  #define lll __int128
  int p,a,b,x_1,t;
  inline int qpow(int a,int b,int p)
  {
  	int ans=1;
  	while(b) 
  	{
  		if(b&1) ans=(lll)ans*a%p;
  		a=(lll)a*a%p;
  		b>>=1;
  	}
  	return ans;
  }
  int exgcd(int a,int b,int &x,int &y) {if(!b){x=1,y=0;return a;}int ret=exgcd(b,a%b,y,x);y-=x*(a/b);return ret;}
  
  inline int get_inv(int a,int p){if(!a)return 1;int x,y;exgcd(a,p,x,y);return (x+p)%p;}
  
  int BSGS(int a,int b,int p)
  {
      mp.clear();
      int sq,mu=1;
      for(sq=1;sq*sq<=p;sq++);
      R(i,0,sq-1) mp.ins((lll)mu*b%p,i),mu=(lll)mu*a%p;
      int now=1;
      R(i,1,sq)
      { 
          now=(lll)now*mu%p;
          int pos=mp.ser(now);
          if(pos!=-1) return i*sq-pos;
      }
      return -2;
  }
  
  
  signed main()
  {
  	//freopen("test.out","w",stdout);
  	for(int _=read();_;_--)
  	{
  		p=read(),a=read(),b=read(),x_1=read(),t=read();
  		if(x_1==t) puts("1");
  		else if(!a) 
  		{
  			if(b==t) puts("2");
  			else puts("-1");
  		}
  		else if(a==1)
  		{
  			int x,y;
  			int Y=((t+b-x_1)%p+p)%p,g=exgcd(b,p,x,y);
  			if(Y%g) puts("-1");
  			else
  			{
  				x*=Y/g;
  				int tmp=(x%p+p)%p;
  				writeln(tmp?tmp:p);
  			}
  		}
  		else
  		{
  			t=(lll)(t*(a-1)%p+b)%p;
  			int tmp=(lll)(a*x_1%p-x_1+b+p)%p;
  			//printf("%lld %lld %lld\n",t,tmp,get_inv(tmp,p));
  			if(!tmp) {puts(t?"-1":"1");}
  			else writeln(BSGS(a,(lll)t*get_inv(tmp,p)%p,p)+1);
  		}
  	}
  }
  ```
  
  
