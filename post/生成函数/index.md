
<!--more-->

## 泰勒多项式

### 定义

对于函数$f$，设它在点$x_0$存在直到$n$阶的导数，则我们由这些导数构造一个$n$次多项式：
$$
T_n(x)=f(x_0)+\frac{f'(x_0) }{1!}(x-x_0)+\frac{f''(x_0)}{2!}(x-x_0)^2+\ldots +\frac{f^{(n)}(x_0)}{n!}(x-x_0)^n
$$
 称为$f$在点$x_0$处（带有皮亚诺型余项）的**泰勒多项式**，$T_n(x)$的各项系数称为**泰勒系数**。



稍微来解释一下

第一项就是已经知道在$x_0$处的所有性质，现在要用这个点性质来拟合$x$处的$f(x)$。

![QQ图片20210429073754.png](https://i.loli.net/2021/04/29/2B81YbdURuaNJXQ.png)

那么首先中间这一段我们并不知道它具体是什么样子的，它可能是歪歪扭扭的，但可以先把它近似为一条直线。那么既然是一条直线，那么它有一个形式为$y=kx+b$。在很靠近$x_0$处，斜率$k$可以表示为$f'(x_0)$。那么前两项的意思就是将这个东西拟合成一条直线。再加一项就是拟合为一个二次函数，再加一项就是三次函数……再往后就是不断加次数。次数越来越大这个箭头就越来越扭，所以说最后到$n$次之后就没有误差了。如果$f(x)$是一个100次曲线，那么拟合到100项时就没有误差了。



以及当$x_0=0$时，有**麦克劳林公式**：
$$
f(x)=f(0)+f'(0)x+\frac{f''(0)}{2!}x^2+\ldots +\frac{f^{(n)}(0)}{n!}x^n+o(x^n)
$$

### 定理

若函数$f$在点$x_0$存在直到$n$阶的导数，则
$$
f(x)=T_n(x)+o((x-x_0)^n)
$$
具体证明：不会...

展开就是
$$
f(x)=f(x_0)+\frac{f'(x_0)}{1!}(x-x_0)+\frac{f^{(2)}(x_0)}{2!}(x-x_0)^2+\ldots +\frac{f^{(n)}(x_0)}{n!}(x-x_0)^n+ o((x-x_0)^n)
$$
其实除去最后小$o$那一项就是$f(x)$了。而小$o$的意思，主要就是其实$f(x)$和$T_n(x)$差了一些的，差了的东西是比$(x-x_0)^n$要低阶（当$x$和$x_0$很靠近的时候，$(x-x_0)^n$特别特别小）的。误差项就是说，当$x$很靠近$x_0$时，它比$(x-x_0)^n$在渐进意义下还要小。（在所有应用中将它展开到无限项，误差会特别特别小）。

以及拓展一下**拉格朗日余项**
$$
f(x)=T_n(x)+\frac{f^{(n+1)}(\xi)}{(n+1)!}(x-x_0)^{n+1}
$$
其中$\xi \in [x_0,x]$

证明大概知乎上有，以及这个东西不重要..

### 一些常用的求导

$$
(a^x)'=a^x \ln a
$$

$$
(\sin x)'= \cos x
$$

$$
(\cos x)'=-\sin x
$$

$$
(x^a)'=ax^{a-1}
$$

$$
(\ln x)'=\frac{1}{x}
$$

### 关于定理的一些简单例子

$$
f(x)=\sum_{i=0}^n \frac{f^{(i)}(x_0)}{i!} (x-x_0)^i
$$

$e^x$

因为
$$
(e^x)'=e^x \ln e=e^x
$$
令$x_0=0$，则有
$$
e^x= \sum_{i=0}^n \frac{x^i}{i!}
$$
所以
$$
e^x=1+\frac{x}{1!}+\frac{x^2}{2!}+\frac{x^3}{3!}+\ldots + \frac{x^n}{n!}+\ldots ;
$$



$\sin(x)$

因为
$$
(\sin x )' = \cos x
$$
$$
(\cos x)' = -\sin x
$$

所以
$$
f(x)=\sin x
$$

$$
f^{(1)} (x)=\cos x
$$

$$
f^{(2)} (x)= -\sin x
$$

$$
f^{(3)} (x) = -\cos x
$$

$$
f^{(4)} (x)=\sin x
$$

仍然令$x_0=0$

由于
$$
\sin x =0
$$

$$
\cos x =1
$$

$$
-\sin x =0
$$

$$
-\cos x= -1 
$$

所以
$$
\sin(x) = \frac{x}{1!} - \frac{x^3}{3!}+\frac{x^5}{5!} + \ldots + (-1)^n \frac{x^{2n+1}}{(2n+1)!}+ \ldots;
$$


$\cos x$

同理
$$
f(x)=\cos x
$$

$$
f^{(1)} (x)=-\sin x
$$

$$
f^{(2)} (x)= -\cos x
$$

$$
f^{(3)} (x) = -\sin x
$$

$$
f^{(4)} (x)=\cos x
$$

所以：
$$
\cos(x) =1-\frac{x^2}{2!}+\frac{x^4}{4!}+\ldots +(-1)^n \frac{x^{2n}}{(2n)!}+\ldots;
$$

$\ln (x+1)$

下面均取$x_0=0$
$$
\ln ^{(1)}(x+1) =\frac{1}{x+1}=1
$$

$$
\ln^{(2)} (x+1)= -\frac{1}{(x+1)^2}=-1
$$

$$
\ln^{(3)} (x+1)=\frac{2}{(x+1)^3} =2
$$

$$
\ln ^{(k)} (x+1)=\frac{(-1)^{k-1}\times (k-1)!}{(x+1)^k}
$$

所以：
$$
\ln(1+x)=\frac{x}{1}-\frac{x^2}{2}+\frac{x^3}{3}+\ldots +(-1)^{n+1}\frac{x^n}{n}+\ldots ;
$$


$\frac{1}{1+x}$
$$
\frac{1}{1+x} = (1+x)^{-1}
$$

$$
(\frac{1}{1+x})' = -(1+x)^{-2}=\frac{-1}{(1+x)^2}
$$

然后就硬展开就行了..
$$
\frac{1}{1+x} =1-x+x^2-x^3+\ldots +(-1)^n\cdot x^n+\ldots ;
$$
$(1+x)^a$
$$
((1+x)^a)' =(a (1+x)^{a-1 })
$$
然后还是硬展开...
$$
(1+x)^a=1+\frac{a}{1!}x+\frac{a(a-1)}{2!}x^2+\ldots +\frac{a(a-1)\ldots (a-n+1)}{n!} +\ldots; 
$$

## 普通生成函数

### 定义

对于一个无穷序列$\{a_0,a_1,a_2,\cdots\}$，定义其**普通生成函数**为**形式**幂级数：$\sum\limits_{k=0}^{\infty} a_k\cdot x^k$。

注意是形式幂级数，[维基百科](https://zh.wikipedia.org/wiki/%E5%BD%A2%E5%BC%8F%E5%B9%82%E7%BA%A7%E6%95%B0)。

与一般幂级数的区别在于一般幂级数可以表示为$f(x)$，相当于一个函数，如$x=-1$时，$f(-1)=\sum\limits_{k=0}^{\infty} (-1)^k a^k$。

而形式幂级数就没有这样的操作，它只是长成这个样子，只是一个形式。大概就是$R[[x]]$，它与$1,2,3,4,5\ldots$这些数地位等同。

### 一些例子

序列$\{\frac{1}{0!},\frac{1}{1!},\cdots ,\frac{1}{k!},\cdots \}$的普通生成函数？
$$
\sum_{k=0}^{\infty} \frac{x^k}{k!}=e^x
$$
序列$\{1,1,1,\cdots ,1,\cdots\}$的普通生成函数？
$$
\sum_{k=0}^\infty x^k=\frac{1}{1-x}
$$
序列$\{1,2,4,\cdots ,2^n,\cdots \}$的普通生成函数？
$$
\sum_{k=0}^\infty 2^k \cdot x^k=\sum_{k=0}^\infty (2x)^k
$$
令$y=2x$

那么
$$
\sum_{k=0}^\infty y^k=\frac{1}{1-y}=\frac{1}{1-2x}
$$
序列$\{1,0,1,0,\cdots,1,0,\cdots \}$的普通生成函数？
$$
\sum_{k=0}^\infty x^k[k\bmod 2=0]=\sum_{k=0}^\infty x^{2k} =\sum_{k=0}^\infty (x^2)^k 
$$
令$y=x^2$
$$
\sum_{k=0}^k y^k=\frac{1}{1-y}=\frac{1}{1- x^2}
$$
序列$\{0,1,0,1,\cdots ,0,1,\cdots\}$的普通生成函数？
$$
\sum_{k=0}^\infty x^k[k\bmod 2=1]=\sum_{k=0}^\infty x^{2k+1}=x\cdot \sum_{k=0}^\infty x^{2k}=\frac{x}{1-x^2}
$$
序列$\{1,2,3,4,\cdots ,n,\cdots\}$的普通生成函数？
$$
\sum_{k=0}^\infty(k+1)x^k=\sum_{k=0}^{\infty} k\cdot x^{k-1}=\sum_{k=0}^\infty (x^k)'
$$
因为$(f+g)'=f'+g'$

所以
$$
\sum_{k=0}^\infty (x^k)'= \big(\sum_{k=0}^{\infty}x^k \big)' = (\frac{1}{1-x})'=\frac{1}{(1-x)^2}
$$
以及为什么可以这么做：

令$F(x)=(\frac{1}{1-x})'$，可以当做一般函数求导，为什么这是对的呢？

因为实际上把所有东西都用幂级数展开定义了，在一般的函数里面泰勒展开是成立的。

一般的式子来进行这样一个求导操作之后得到的结果也是符合泰勒展开的。

在多项式函数世界当中求导就是这么定义的。

任何一个非多项式函数都可以使用泰勒展开写成若干个多项式函数的和，所以我们知道这几个东西在函数求导都是对的，所以在这个里面我们也可以对它的生成函数求导。对生成函数求导就等价于对原序列求导。

所以$F(x)=\frac{1}{(1-x)^2}$


$$
\frac{d(1+x+x^2+x^3+\ldots)}{dx}=\frac{1}{(1-x)^2}
$$

### 小练习

序列$\{1,3,5,7,\cdots ,2n-1,\cdots \}$的普通生成函数？


$$
S=1+a+a^2+\ldots
$$

$$
aS=a+a^2+a^3+\ldots
$$

$$
S\cdot (1-a)=1
$$

$$
S=\frac{1}{1-a}
$$

令$F(x)=1+3x+5x^2+7x^3+\ldots$

那么
$$
xF(x)=x+3x^2+5x^3+7x^4+\ldots
$$

$$
(1-x)\cdot F(x)=1+2x+2x^2+2x^3+2x^4+\ldots
$$

然后将1和后面的2分开来，即$\{1,0,0,\ldots \}$和$\{0,2,2,\ldots \}$

得到：
$$
(1-x)\cdot F(x)=1+2x+2x^2+2x^3+\ldots =1+\frac{2x}{1-x}
$$

$$
F(x)=\frac{1+\frac{2x}{1-x}}{1-x}=\frac{1+x}{(1-x)^2}
$$

当然还有一种做法是拆成$\{1,1,1,1,\ldots\}+\{0,1,2,3,4,\ldots\}+\{0,1,2,3,4,\ldots\}$，然后把解出来的加起来就是了。

### 练习

求下列级数的普通生成函数：

$\{4,4,4,4,\ldots \}$

$$
4\cdot \sum_{k=0}^\infty x^k
$$

$$
\frac{4}{1-x}
$$

$\{2,4,6,8,\ldots \}$
$$
2\cdot \sum_{k=0}^\infty (k+1) \cdot x^k =2\cdot \sum_{k=0}^\infty k\cdot x^{k-1}=2\cdot \sum_{k=0}^\infty (x^k)'=2\cdot\big(\sum_{k=0}^\infty x^k \big)'=2\cdot (\frac{1}{1-x})'=\frac{2}{(1-x)^2}
$$
$\{0,0,0,2,4,6,8,\ldots \}$

$2\cdot \{0,0,0,1,2,3,4\}$
$$
2\cdot \sum_{k=0}^{\infty} k \cdot x^{k+2} = 2x^3 \sum_{k=0}^\infty k\cdot x^{k-1}=\frac{2x^3}{(1-x)^2}
$$
$\{1,5,25,125,\ldots \}$
$$
\sum_{k=0}^\infty 5^k \cdot x^k =\sum_{k=0}^\infty (5x)^k=\frac{1}{1-5x}
$$
$\{1,-3,9,-27,81,\ldots\}$
$$
\sum_{k=0}^{\infty} (-3)^k\cdot x^k=(-3x)^k =\frac{1}{1+3x}
$$
$\{1,0,5,0,25,0,125,0,\ldots \}$
$$
\sum_{k=0}^\infty 5^{\frac{k}{2}} x^k [k\bmod 2=0]=\sum_{k=0}^{\infty} 5^{k}\cdot x^{2k}=\sum_{k=0}^\infty (5x^2)^k=\frac{1}{1-5x^2} 
$$
$\{0,1,0,0,2,0,0,3,0,0,4,0,0,5,\ldots \}$
$$
\sum_{k=0}^{\infty} k\cdot x^{3k-2}=x^{-2} \sum_{k=0}^{\infty} k \cdot x^{3k}
$$
令$y=x^3$
$$
x^{-2} \sum_{k=0}^{\infty} k \cdot x^{3k}=x\sum_{k=0}^{\infty} k\cdot y^{k-1}=x \sum_{k=0}^{\infty}(y^k)'=\frac{x}{(1-y)^2}=\frac{x}{(1-x^3)^2}
$$
$\{4,5,7,10,14,19,25,\ldots  \}$

令$F(x)=4+5x+7x^2+10x^3+\ldots$
$$
(1-x)\cdot F(x)=4+x+2x^2+3x^3+\ldots
$$
拆成$\{4,0,0,\ldots \}+\{0,1,2,3,\ldots \}$得到：
$$
(1-x)\cdot F(x)=4+\frac{x}{(1-x)^2}
$$

$$
F(x)=\frac{4}{1-x}+\frac{x}{(1-x)^3}
$$

### 经典例题

有四种无限多的水果，要求第一种恰好拿出偶数个，第二种恰好拿出$5$的倍数个，第三种最多拿$4$个，第四种最多拿$1$个，求恰好拿出$n$个水果的方案数。

先考虑只有前两种水果时的情况

现在知道了第一种水果拿$0$个的方案数是$a_0$，拿$1$个的方案数是$a_1$...拿$n$个的方案数$a_n$

$\{a_0,a_1,a_2,\ldots ,a_n\}$

同样设第二种水果拿$0$个的方案数是$b_0$.......

$\{b_0,b_1,b_2,\ldots ,b_n\}$

 然后现在求一共恰好拿出$n$个水果的方案
$$
\sum_{i=0}^n a_i\cdot b_{n-i}
$$
定义$C_n$表示$\sum\limits_{i=0}^n a_i \cdot b_{n-i}$

解出$C_n$的生成函数$C(x)$
$$
\sum_{n=0}^{\infty} C_n\cdot x^n
$$
将定义式代回来，得到：
$$
\sum_{n=0}^\infty \sum_{i=0}^n a_i\cdot b_{n-i} \cdot x^n
$$
看到有两个求和符号，你的DNA就动了，交换两个求和符号
$$
\sum_{i=0}^\infty a_i \sum_{n=i}^n b_{n-i} \cdot x^n
$$
然后令$j=n-i$，原式变为：
$$
\sum_{i=0}^\infty a_i \sum_{j=0}^\infty b_j\cdot x^{i+j}
$$
而$x^{i+j}=x^i\cdot x^j$，所以继续转化原式变为：
$$
\big(\sum_{i=0}^\infty a_i\cdot x^i \big )\big(\sum_{j=0}^\infty b_j\cdot x^j \big )
$$
那么其实这就分别是$a$和$b$的生成函数，记作$A(x)$和$B(x)$

事实上$C(x)=A(x)\cdot B(x)$

那么例题就是分别求出$4$个条件的生成函数然后直接乘起来就是了

为什么这会是对的呢？

可以想象一下做一个$dp$，设$dp_{i,j}$表示前$i$种水果恰好拿出$j$个的方案数。

假设它第$i$行的一个生成函数叫做$F_i$

就有$F_i(x)=F_{i-1}(x)\cdot A_i(x)$，$A_i(x)$为从第$i$个水果中拿恰好多少个对应的生成函数

那么如$F_4(x)=A_1A_2A_3A_4$



回到例题

第一种水果的数列为$\{1,0,1,0,\ldots\}$，它的生成函数即$\frac{1}{1-x^2}$

第二种生成函数为$\frac{1}{1-x^5}$

第三种为$\{1,1,1,1,1,0,0,0,0,\ldots\}$，它的生成函数即$1+x^1+x^2+x^3+x^4$

第四种的生成函数为$1+x$

四个相乘就可以得到恰好拿出$n$个水果的方案数即$\frac{1}{(1-x)^2}$。

就是$\{1,2,3,4,5,\ldots\}$的生成函数

故方案数为$n+1$



对于线性递推都可以求普通生成函数

### Fibonacci 数列

求 Fibonacci 数列 $a_0=a_1=1,a_n=a_{n-1}+a_{n-2}(n\ge 2)$的普通生成函数？

设：
$$
A=a_0+a_1x+a_2x^2+a_3x^3+\ldots 
$$

$$
xA=0+a_0x+a_1x^2+a_2x^3+\ldots
$$

$$
x^2A=0+0+a_0x^2+a_1x^3+a_2x^4\ldots
$$

然后可以得到
$$
(1-x-x^2)A=a_0+a_1x-a_0x=1
$$

$$
A=\frac{1}{1-x-x^2}
$$

### 线性递推的特征根法

假设现在有一个$k$阶的线性递推$a_n=\sum\limits_{i=1}^k b_i\cdot a_{n-i}$

怎么用上述方法来做呢。

我们想要凑出来在某一项之后，在某一个位置，

第一位是$a_n$，第二位$b_1a_{n-1}$，第三位$b_2a_{n-2}$....

在后面乘的$x^n$要对齐，那么第一个就是$A$，第二个就是$b_1xA$，第三个就是$b_2x^2A$

大概就这个样子

![QQ图片20210430110014.png](https://i.loli.net/2021/04/30/hdQli42PNRB3rFJ.png)

仿照刚刚一减，就可以得到式子
$$
(1-b_1x-b_2x^2-b_3x^3-\ldots-b_k x^k)A(x)=F(x)
$$
其中$F(x)$是一个低次多项式。

考虑解这个方程

左边的一堆东西可以分解成形如
$$
(1-\alpha_1 x)\cdot (1-\alpha_2 x)\cdot \ldots \cdot (1-\alpha_n x)
$$
假设$\alpha$两两不相同，那么分母待定系数一下，可以证明可以写成
$$
\frac{a_1}{1-\alpha_1x}+\frac{a_2}{1-\alpha_2 x}+\ldots 
$$
每一项都可以算出来如第$n$项第一位为$\alpha_1^n \cdot a_1$

通项公式第$n$项就是
$$
\alpha_1 a_1+\alpha_2 a_2+\ldots
$$
假如有重复就有一点麻烦，比如$\alpha_1 =\alpha_2$

就会出现
$$
\frac{a_1}{1-a_1x}+\frac{a_2}{(1-a_1x)^2}
$$
当然这也能算。

通过这种方法可以很方便地求出一个线性递推的通项公式。

[如果看不懂可以看这里](https://blog.csdn.net/hefenghhhh/article/details/84897165)



使用特征根法，即可得到Fibonacci数列的通项公式



### Catlan数

求Catlan数$c_0=1,c_n=\sum\limits_{i=0}^{n-1}c_i\cdot c_{n-i-1}(n\ge 1)$的普通生成函数？

错误版：

$c_n$的生成函数$C(x)=\sum\limits_{n=0}^{\infty} \sum\limits_{i=0}^{n-1} c_i\cdot c_{n-i-1}\cdot  x^n$

将$x^n$拆成$x^i,x^{n-i-1},x$

然后原式变成$\sum\limits_{i=0}^{\infty} c_i x^i\cdot \sum\limits_{j=0}^{\infty} c_j x^j\cdot x$

这样会得到$C(x)=C^2(x)\cdot x$，然而这实际上是错的，因为当$n\ge 1$时，$c_n$才会等于这个式子。

即$c_n$本来为$\sum\limits_{n=1}^{\infty} c_nx^n=\sum\limits_{n=1}^{\infty} \sum\limits_{i=0}^{n-1} c_i\cdot c_{n-i-1}\cdot x^n$

然而$n$从$0$开始或从$1$开始在下面的式子并不能体现出来，因为已经将$x^n$拆成$x^i,x^{n-i-1},x$

所以说正确的式子应长成$C(x)=\sum\limits_{n=1}^{\infty} c_nx^n+c_0\cdot x^0$

而$c_0\cdot x^0=1$

所以$C(x)=C^2(x)+x+1$

解得$C(x)=\frac{1\pm \sqrt{1-4x}}{2x}$

若$C(x)=\frac{1+\sqrt{1-4x}}{2x}$，则$\lim\limits_{x\to 0} C(x)=\infty$，与$C(x)$的常数项为$1$矛盾。（或者将这个按照下面展开，可以发现$c_0\neq 1$）

 现在知道$C(x)=\frac{1-\sqrt{1-4x}}{2x}$，现在来求通项，将它泰勒展开（因为$\sqrt{1-4x}$长得很像$x^a$的形状$-\sqrt{1-4x}=-(1-4x)^{\frac{1}{2}}$，将它按照$x^a$泰勒展开，然后将$1-4x$代入，就可以得到：
$$
\frac{1-\sqrt{1-4x}}{2x}=\frac{1}{2x} \sum_{k=1}^{\infty} \frac{1\cdot 3 \cdot \ldots \cdot (2k-3)}{2^k}\cdot \frac{(4x)^k}{k!}
$$
因为这个东西就是原来的生成函数$\sum\limits_{k=0}^{\infty} c_k x^k$，按$x$对齐，将系数提出来，就得到了
$$
c_k=\frac{1}{2}\cdot \frac{1\cdot 3\cdot \ldots \cdot (2k-1)}{2^{k+1}} \cdot \frac{4^{k+1}}{(k+1)!}
$$
整理得到：
$$
c_k=\frac{(2k)!}{(k+1)!k!}=\frac{1}{k+1} \binom {2k} {k}
$$

### 例子3（多元生成函数）

$$
a_n=\sum\limits_{i=0}^{\infty}\binom {n+i}{2i}
$$

令$A(x)$为这个的生成函数
$$
A(x)=\sum_{n=0}^{\infty} \sum_{i=0}^n \binom {n+i} {2i} x^n
$$
令杨辉三角第$n$行的生成函数为$F_n(x)=\sum\limits_{i=0}^n \binom {n}{i} x^i$

然后对着$F_0(x),F_1(x),F_2(x),\ldots$这些生成函数再整一个生成函数$\sum\limits_{n=0}^{\infty} F_n(x)\cdot y^n $


$$
\sum_{n=0}^{\infty} \sum_{i=0}^n \binom{n}{i} x^i y^n
$$
然后转换一下形式
$$
\sum_{i=0}^{\infty} \sum_{j=0}^{\infty} \binom{i+j}{i} x^i y^{i+j}
$$
注意到同时有$x^i$和$y^i$，令$z=xy$

原式化为：
$$
\sum_{i=0}^{\infty} \sum_{j=0}^{\infty} \binom{i+j}{i} z^i y^j
$$
这个东西是一个二项式定理的形状

就可以化为
$$
\sum_{n=0}^{\infty} (y+z)^n
$$
回到一开始的生成函数$A(x)=\sum\limits_{n=0}^{\infty}\sum\limits_{i=0}^n \binom{n+i}{2i} x^n$

与上面那个式子进行比较$\sum\limits_{a=0}^{\infty} \sum\limits_{b=0}^a \binom {a+b}{a} z^ay^b$

考虑先让组合数对应起来，就是让$a=2i,b=n-i$

那么后面的系数就变成了$z^{2i} y^{n-i}$

然后令$y=z^2$，系数就变成了$z^{2n}$，然后令$x=z^2$，就可以对应起来的，然后得到了一个新的生成函数
$$
B(x)=\sum_{n=0}^{\infty} \sum_{i=0}^n \binom{n+i}{2i} z^{2n}=\sum_{n=0}^{\infty} (z^2+z)^n
$$
这是一个等比数列求和$=\frac{1}{1-z-z^2}$

假如将$B(x)$写成$b_0,b_1,b_2\ldots$，$A(x)$写成$a_0,a_1,a_2,\ldots$

因为$x=z^2$，所以$a_0\to b_0,a_1\to b_2,a_2\to b_4$即$a_k=b_{2k}$

而因为$b$是斐波那契数列，所以第$n$条对角线的和$a_n=\sum\limits_{i=0}^{\infty}\binom {n+i}{2i}=\operatorname{Fib}_{2n}$



最后理一下步骤

首先明确问题是求$a_n=\sum\limits_{i=0}^n \binom{n+i}{2i}$

那第一步是写出他的生成函数$A(x)=\sum\limits_{n=0}^{\infty} a_n x^n$

代入$a_n$得到
$$
\sum_{n=0}^{\infty} \sum_{i=0}^n \binom {n+i}{2i}x^n
$$
然后对于杨辉三角每一行都写出一个生成函数$F_n(x)=\sum\limits_{j=0}^n \binom n j x^j$

然后对于这$F_0(x),F_1(x),\ldots, F_{\infty}(x)$再写一个生成函数$G(x,y)$
$$
G(x,y)=\sum_{n=0}^{\infty} F_n(x) y^n=\sum_{n=0}^{\infty} \sum_{i=0}^n \binom n i x^i y^n
$$

将$y^n$拆成$y^i\cdot y^{n-i}$，令$z=xy$

就有
$$
\sum_{n=0}^{\infty} \sum_{i=0}^n \binom n i z^i y^{n-i}
$$
运用二项式定理，得到：
$$
\sum_{n=0}^{\infty} (z+y)^n
$$
再把两个生成函数抄下来
$$
A(x)=\sum_{n=0}^{\infty} \sum_{i=0}^n \binom {n+i}{2i}\cdot x^n
$$

$$
G(z,y)=\sum_{n=0}^{\infty} \sum_{i=0}^{n} \binom n i z^i y^{n-i}
$$

令$a=i,b=n-i$
$$
\sum_{a=0}^{\infty} \sum_{b=0}^{\infty} \binom {a+b} {a}y^b z^a
$$
然后要让这两个式子尽量一样，令$a=2i,b=n-i$

然后$G(z,y)$就长成
$$
\sum_{n=0}^{\infty} \sum_{i=0}^n \binom {n+i} {2i} y^{n-i} z^{2i}
$$
然后它还是等于$\sum\limits_{n=0}^{\infty} (y+z)^n$

接下来令$y=z^2$，然后两个式子就分别变成$\sum_{n=0}^{\infty} \sum_{i=0}^n \binom {n+i} {2i} z^{2n}$和$\sum\limits_{n=0}^{\infty} (z^2+z)^n$

其中$\sum\limits_{n=0}^{\infty}(z^2+z)^n $可以通过等比数列求和得到$\frac{1}{1-z-z^2}$，即斐波那契数列。

然后对比$A(x)=\sum\limits_{n=0}^\infty \sum\limits_{i=0}^\infty \binom {n+i}{2i} x^n$，令$x=z^2$

上面那个就相当于斐波那契数列的$1,2,3\ldots$项，而下面斐波那契数列的$2,4,6,\ldots$ 项

所以$a_k=F_{2k}$，其中$F_{k}$为斐波那契数列第$k$项。

## 指数生成函数

对于一个无穷序列$\{a_0,a_1,a_2,\ldots \}$，定义其**指数生成函数**为级数：$\sum\limits_{k=0}^{\infty} a_k \cdot \frac{x^k}{k!}$

普通生成函数通常用来解决无标号计数问题，指数生成函数通常用来解决带标号的计数问题。

### 一些例子

$n$个元素的排列数$p_n=n!$的指数生成函数？
$$
\hat{P}(x)=\sum\limits_{n=0}^{\infty} \frac{n!}{n!} x^n=\frac{1}{1-x}
$$
$n$个元素的环排列数$c_n=(n-1)! (n\ge 1)$的指数生成函数？
$$
\hat{C}=\sum_{n=0}^{\infty} \frac{1}{n} x^n
$$
这个东西和$\ln(1+x)$长的比较像$\ln(1+x)=\sum\limits_{n=0}^{\infty} (-1)^{n-1} \frac{x^n}{n}$

然后把那个$-1$去掉，变成$(-1) \sum\limits_{n=0}^{\infty} (-1)^n \frac{x^n}{n}=(-1)\sum\limits_{n=0}^{\infty} (-x)^n \frac{1}{n}$

如果变成$\ln(1-x)$就变成$(-1)\sum\limits_{n=0}^{\infty} x^n \frac{1}{n!}$

所以$\hat{C}=-\ln(1-x)=\ln(\frac{1}{1-x})$

注意到$\hat{P}(x)=e^{\hat{C}(x)}$

考虑一个排列，对它进行置换分解，即沿$i\to p_i\to p_{p_i}\to p_{p_{p_i}}\to \ldots \to i$。这样会组成一个环。

假设现在知道$1,3,5,8$这四个位置组成了一个环，然后现在要搞出来$p_1,p_3,p_5,p_8$分别是多少。

举个例子$p_1=3,p_3=5,p_5=8,p_8=1$。

现在要求出这样的排列数有多少个，显然为$(n-1)!$

现在考虑排列数和原排列数的生成函数有什么关系

先枚举它被分成了多少个环

只有一个环就是$(n-1)!$

假如组成两个环就是$f_n=\frac{1}{2} \sum\limits_{i=0}^{n} \binom n i (i-1)!(n-i-1)!$

令$g_i=(n-1)!$那么$g_{n-i}=(n-i-1)!$（$g_0=0$）

那么$f_n=\frac{1}{2}\sum\limits_{i=0}^n \binom n i g_i g_{n-i}$即一个卷积的形式

然后写出它的生成函数
$$
\hat{F_2}(x)=\sum_{n=0}^{\infty} f_n \frac{x^n}{n!}=\sum_{n=0}^{\infty} \frac{1}{2} \sum_{i=0}^n \binom n i g_i g_{n-i} \frac{x^n}{n!}
$$
因为$\binom n i =\frac{n!}{i!(n-i)!},x^n= x^i\cdot x^{n-i}$

所以原式
$$
\sum_{n=0}^{\infty} \frac{1}{2} \sum_{i=0}^n \frac{g_i}{i!} \frac{g_{n-i}}{(n-i)!} x^i x^{n-i}=\frac{1}{2}\sum_{i=0}^{\infty} \frac{g_i}{i!} x^i \sum_{j=0}^{\infty} \frac{g_j}{j!} x^j=\frac{1}{2} (\hat{G}(x))^2
$$
发现
$$
\hat{F_1}(x)=\hat{G} (x)
$$

$$
\hat{F_2} (x)=\frac{1}{2} (\hat{G}(x))^2
$$

$$
\hat{F_3}(x)=\frac{1}{6}(\hat{G}(x))^3
$$

$$
\ldots
$$

$$
\hat{F_n}(x)=\frac{1}{n!} (\hat{G}(x))^n
$$
而
$$
\hat{F} (x)=\sum_{n=0}^{\infty} \frac{1}{n!} (\hat{G}(x))^n
$$
这就是一个$\exp$的样子。
$$
\hat{F}(x)=e^{\hat{G}(x)}
$$


错排数的指数生成函数？

把排列拆成环排列，只要没有大小为1的环就是一个错排。

当$n\ge 2$时，类似地$g_n=(n-1)!$，但当$n=1$时，$g_n=0$

这里同样以两个环为例：$d_n=\frac{1}{2}\sum\limits_{i=2}^{n-2} \binom n i g_i g_{n-i} $

但是这个东西不太好卷起来，实际上只有下标为1不能选

所以改成$\frac{1}{2}\sum\limits_{i=0}^n \binom n i g_i g_{n-i} [i\neq 1][n-i\neq 1]$

然后令$h_i=g_i\cdot [i\neq 1]$

式子就变成$\frac{1}{2}\sum\limits_{i=0}^n \binom n i h_i h_{n-i}$
$$
\hat{H} =\sum_{n=0}^{\infty} \frac{h_n}{n!} x^n=\sum_{n=0}^{\infty} \frac{g_n[n\neq 1]}{n!} x^n=\sum_{n=2}^{\infty} \frac{g_n}{n!} x^n
$$
因为$g_1=1$，所以又等于$\sum\limits_{n=0}^{\infty} \frac{g_n}{n!}x^n-x$

前面的一堆就是$\hat{G}(x)=\ln (\frac{1}{1-x})$

所以$\hat{H}(x)=\ln(\frac{1}{1-x})-x$

那错排数$\hat{D}(x)=\exp(\hat{H}(x))= \exp(\ln(\frac{1}{1-x})-x)=\frac{e^{-x}}{1-x}$

这个东西看上去挺简洁的，实际上一点也不简洁。

展开就相当于两个东西卷起来，分子是一个无限项的东西，分母又是一个无限项的东西，所以这个通项展开并不好看。



$n$个点的有标号无向连通图个数的指数生成函数？

先把连通这个条件去掉，即$n$个点的有标号无向连通图个数显然为$2^{\frac{n(n-1)}{2}}$。

假设这个东西为$b_n$，这个的生成函数为$\hat{B}$。

一个无向图可以分成若干个连通块的不交并，而且这还是带标号的。

第一步，先确定每一个联通块分别有哪些点。

第二步，将每一个联通块内的联通方式算上。

假如已经知道这个东西是$a_n$了，那现在就相当于求$b_n$

然后两个连通块，三个连通块这样推下来……

就可以得到$\hat{B}=\exp (\hat{A})$

所以有$\hat{A}=\ln (\hat{B})$



## 生成函数操作

### 乘法

FFT：

假如现在有一个$n$次多项式$f(x)$，现在求出了$f(x_0),f(x_1),\ldots ,f(x_n)$且知道$x_0,x_1,\ldots x_n$，那么就可以求出$f(x)$，现在有$f(x)$也可以知道在$x_0,x_1\ldots x_n$的点值。

通过拉格朗日插值可以在任意$x_0,x_1,\ldots x_n$平方复杂度插出来。

但是如果不取任意位置，可以在更优的时间复杂度求出

假设$n < 2^k$，令$\omega =\exp(\frac{2\pi i}{2^k})=\cos(\frac{2\pi}{2^k})+i\sin (\frac{2\pi}{2^k})$

假设$f(x)=\sum\limits_{i=0}^n a_i x^i$

现在求$\sum\limits_{i=0}^n a_i \omega_{2^k} ^i$

不妨设系数到$2^k-1$即求$\sum\limits_{i=0}^{2^k} a_i \omega_{2^k}^i$

单位圆有$\omega_{2^k}=\omega_{2^{k+1}}^2$的性质

这启发我们分治，将它劈成奇数项和偶数项
$$
\sum_{i=0}^{2^{k-1}-1} a_{2i} \omega _{2^k}^{2i} +\sum_{i=0}^{2^{k-1}-1} a_{2i+1} \omega _{2^k}^{2i+1}
$$

$$
\sum_{i=0}^{2^{k-1}-1} a_{2i} \omega _{2^k}^{2i} +\omega_{2k} \sum_{i=0}^{2^{k-1}-1} a_{2i+1} \omega _{2^k}^{2i}
$$

而$\omega_{2^k}^{2i}=\omega_{2^{k-1}}^i$

所以可以将左边偶数项的$a_0,a_2,a_4,\ldots$再分治下去就可以求出左边，右边奇数项同理。

这样就得到了$i$在$0\to 2^{k-1}-1$范围的结果。

实际上这只是求了$x_1=\omega_{2^k}^1$处的点值

我们需要一次性求出上面的这些。

我们还需要求$\omega^2$的$i$次方，$\omega^3$的$i$次方。

但是为了保证复杂度，显然不能一次全部把$0\to 2^k -1$全部都代进去。

每次分治的时候求一半，那么之后怎么合并回去呢？

直接合并只能求出一半。

但是注意到$\omega_{2^k}$转$2^k -1$次正好转到$-1$。且现在已经知道$0\to 2^k-1$（上半圆）的点值。

对于一半之后的，在提出来的$\omega_{2^k}$上直接乘一个$-1$，具体原因是转一半就正好转出了$-1$。因此分治下去即可。时间复杂度就是$O(n\log n)$的。

所以说可以在$O(n\log n)$时间复杂度求出在$f(x)$上的点值，插值回去同样，这涉及到傅里叶变换一个优美的性质，两个只差一个系数。

NTT：

与FFT是一样的，唯一的区别是FTT是在复平面上做这件事，相当于$1$开了$2^k$根。而NTT是在数论域（模$p$域）上做这件事，这个时候也是把$1$开$2^k$根。

原根：

$g^0,g^1,\ldots,,g^{p-2}$在模$p$意义下两两不同，且遍历$1\to p-1$

若$2^k | p-1$

令$\omega_{2^k}=g^{\frac{p-1}{2^k}}$

就得到了一个开$2^k$的结果

所以说只要求出$g$，且$2^k|p-1$，就能很方便求出不管多少次的单位根。

第一个条件比较好弄直接暴力枚举或者随机即可。如$998244353$的一个原根就是$3$。

第二个条件比较麻烦。如$10^9+7$就只能处理$2$以内的DFT。

MTT：

在模数为$10^9+7$时就不太好，这个时候一般有几种做法：

FFT，需要精度比较高

中国剩余定理，要达到$10^9+7$，每一次NTT选的模数也在$10^9$左右，且若值域较大要选三个左右。

假如要乘两个矩阵$A,B$，那么$A$要一次FFT到$A$的点值，$B$也需要一次FFT到$B$的点值，乘起来得到$C$的点值，再FFT回去得到$C$，就需要三次FFT，选三个FFT模数就要九次.

而MTT只需要做四次。

模数是$P$，$P$只要是一个质数就行。

然后随便一个数$M$，这个$M$差不多是$\sqrt P$。

然后把每一个数字表示成$a+bM$

现在要卷两个序列，假设系数分别为$a_1,a_2,\ldots a_n,b_1,b_2,\ldots b_n$。

然后把每一个数字都写成这样的形式，如$a_i=a_{1i}+b_{1i}M,b_i=a_{2i}+b_{2i}M$

相乘会长成这个样子
$$
(a_1+b_1M)(a_2+b_2M)=a_1a_2+(a_1b_2+a_2b_1)M+b_1b_2M^2
$$
然后假如现在给它DFT过去，然后回来的时候只要DFT $a_1 a_2,(a_1b_2+a_2b_1)M,b_1b_2M^2$即可。

这时就把$9$次FFT变成了$7$次FFT，因为$a,b$都在$M$以内，所以结果是在$P$以内的，所以`double`的精度够了，直接FFT即可。

这样总共是7次FFT（去4次，回来3次），继续优化。

假如说现在有两个实数序列$A(x),B(x)$

令$P(x)=A(x)+iB(x),Q(x)=A(x)-iB(x)$
$$
P(\omega ^k_{2^n})=\sum_{j=0}^{2^n-1} (a_j+ib_j)\omega_{2^n}^{jk}=\sum_{j=0}^{2^n-1} (a_j+ib_j)(\cos(\frac{2\pi jk}{2^n})+i\sin \frac{2\pi j k}{2^n} )
$$
然后暴力乘开
$$
\sum_{j=0}^{2^n-1} (a_j \cos(\frac{2\pi jk}{2^n})-b_j\sin(\frac{2\pi jk}{2^n}) )+i(b_j \cos(\frac{2\pi jk}{2^n})+a_j\sin(\frac{2\pi jk}{2^n}))
$$
同理
$$
Q(\omega^k)=\sum_{j=0}^{2^n-1} (a_j \cos(\frac{2\pi jk}{2^n})+b_j\sin(\frac{2\pi jk}{2^n}) )-i(b_j \cos(\frac{2\pi jk}{2^n})-a_j\sin(\frac{2\pi jk}{2^n}))
$$
对比一下上下的式子，大概就是$\cos$不变而$\sin$正负号变了

$\cos$是横坐标，$\sin$是纵坐标，有什么方法让横坐标不变而纵坐标变呢，就是上下折一下，原来是$\theta$就变成$-\theta$，然后式子就变成：
$$
\sum_{j=0}^{2^n-1} (a_j \cos(\frac{2\pi jk}{2^n})-b_j\sin(\frac{2\pi jk}{2^n}) )-i(b_j \cos(\frac{2\pi jk}{2^n})+a_j\sin(\frac{2\pi jk}{2^n}))
$$
就和上面那个式子差不多了，除了$i$那里一个是加一个是减。

所以$=\overline{P(\omega^{-k})}=\overline{P(\omega^{2^n-k})}$

所以只需要对$P$跑一次DFT，就可以得到$P$的所有$\omega^k$（$P(\omega^k)$）

然后`reverse`一下再取一个共轭，就可以得到$Q(\omega^k)$

然后还可以求出$A,B$

$P=A+iB,Q=A-iB$

所以$\frac{1}{2}(P+Q)=A$



所以说对$a_1,b_1$做一次DFT得到$a_1,b_1$的点值，再对$a_2,b_2$做一次得到点值，反过来三个东西$a_1a_2+(a_1b_2+a_2b_1)M+b_1b_2M^2$就是把两个一拼做一次DFT，然后另外一个自己做一次。总共就是$4$次了。这玩意就是MTT。



然而这玩意没有什么用...

### 求逆

给你一个多项式$f$，求$\frac{1}{f}$。（假设$f$的常数项不为0，因为0乘任何数都不为1）

假设只需要求一个多项式$g$满足$f\cdot g\equiv 1 \pmod {x^n}$，不妨设$n$是$2$的幂。

倍增下去，令$k=\frac{n}{2}$

假设当前已经知道$f\cdot h\equiv 1 \pmod {x^k}$

有$f\cdot g\equiv 1\pmod {x^k}$

将两式相减，一定要有这个式子成立
$$
f\cdot (g-h) \equiv 0 \pmod {x^k}
$$
将两边平方
$$
f^2\cdot(g-h)^2\equiv 0 \pmod {x^{2k}}
$$
因为$f$显然不为$0$
$$
g^2-2gh+h^2\equiv 0 \pmod {x^{2k}}
$$
然后两边同时乘个$f$
$$
fg^2-2fgh+fh^2\equiv 0 \pmod {x^{2k}}
$$
因为上面的各种条件可以得到：
$$
g=2h-h^2f=h(2-hf)
$$
然后分析一下时间复杂度
$$
T(n)=T(\frac{n}{2})+O(n\log n)
$$

$$
\rightarrow T(n)=O(n\log n)
$$

### 牛顿迭代

解方程$f(Y)\equiv 0 \pmod {x^n}$

其中$f:R[x]\to R[x]$（从多项式到多项式的一个函数）

然后令$k=\frac{n}{2}$，然后现在已经知道$f(Z)\equiv 0 \pmod {x^k}$

因为$f$是一个函数，既然它是一个函数，那么它就能泰勒展开，具体原因我不会！！1

我们对$f$这个函数在$Z$位置泰勒展开
$$
f(Y)=f(Z)+\frac{f'(Z)}{1!}(Y-Z)+\frac{f''(Z)}{2!}(Y-Z)^2+\ldots
$$
解方程的时候，不妨设$Y\equiv Z \pmod {x^k}$（因为解是不唯一的）

所以说$(Y-Z)^2\equiv 0 \pmod {x^{2k}}$

所以上面泰勒展开后面的几项全没了。

即：
$$
f(Y)=f(Z)+f'(Z)(Y-Z) \pmod {x^2k}
$$
而因为$f(Y)\equiv 0 \pmod {x^n}$

所以$0\equiv f(Z)+f'(Z)(Y-Z) \pmod {x^{2k}}$
$$
Y\cdot f'(Z)\equiv Z f'(Z)-f(Z) \pmod {x^{2k}}
$$

$$
Y\equiv Z- \frac{f(Z)}{f'(Z)} \pmod {x^{2k}}
$$

$\frac{f(Z)}{f'(Z)}=(f'(Z))^{-1} \cdot f(Z)$

时间复杂度为$O(n\log n)$

值得一提的是$f'$怎么办，这个东西机器不会帮我们求，只能具体问题具体分析，



比如说$f(A)=\ln A$

对它求导是$\frac{1}{A}$还是$\frac{A'}{A}$。

什么叫求导？

应该是
$$
\frac{\mathrm{d}f}{\mathrm{d}A} = \frac{\mathrm{d}(\ln A)}{\mathrm{d} A}=\frac{1}{A}
$$
而后面这个是
$$
\frac{\mathrm{d}f}{\mathrm{d}x}=\frac{\mathrm{d}(\ln A)}{\mathrm{d}A} \frac{\mathrm{d}A}{\mathrm{d}x}=\frac{A'}{A}
$$
我们要上面那一个，因为泰勒公式是对$f$里面这个东西求导

加入写作$f(Y)$，那么$f'(Y)$应该被定义成$\frac{df}{dY}$，就是说不管里面是什么东西都是说对里面这个东西求导，而不是更里层的变量来求导。



再举个例子$f(A)=A-B$而$B$是一个固定的多项式，

而$f'(A)=1$，因为你要记住你是对A求导的，所以对A而言B只是一个常数。

### 求$\ln$

$$
\frac{\mathrm{d}(\ln A)}{\mathrm{d}x	}=\frac{A'}{A}
$$

而$A'$好求，$\frac{1}{A}$也好求，右边就可以求出来了。而因为是对$x$求导的，所以对$x$的积分也直接求出来了，就有
$$
\ln x=\int \frac{A'}{A} \mathrm{d} x
$$
时间复杂度$O(n\log n)$

### 求$\exp$

相当于解$B= e^A$

两边取$\ln$，$\ln B =A$

令$f(B)=\ln B-A$，牛顿迭代求零点即可。

### 除法与取余

$A=DB+R$

翻转一下，即将所有的$X$用$\frac{1}{X}$代替，$A(\frac{1}{x})=D(\frac{1}{x})B(\frac{1}{x})+R(\frac{1}{x})$

两边同乘$x^n$，$x^n A(\frac{1}{x})=x^n D(\frac{1}{x})B(\frac{1}{x})+R(\frac{1}{x})$

然后拆成
$$
x^nA(\frac{1}{x})=(x^{n-m} D(\frac{1}{x})) (x^m B(\frac{1}{x}))+x^{m-1}\cdot x^{n-m+1} R(\frac{1}{x})
$$
注意到$x^n A(\frac{1}{x})$就是把$A$的各项系数给反过来，就是$\sum\limits_{i=0}^n a_{n-i}\cdot x^i$记作$A^R(x)$

那么有
$$
A^R(x)=D^R (x)B^R(x)+x^{n-m+1} R^R(x)
$$
然后两边对$x^{n-m+1}$取模，因为$D^R(x)$是$n-m$次的，所以取模之后$x^{n-m+1}\cdot R^R(x)$这一项就没有了。而$D^R(x)$是不变的，所以再将$A^R(x)$与$B^R(x)$取模之后，就可以准确求出$D^R(X)$。然后把系数翻回去就得到了$D$，然后再代回原式$A=DB+R$，就得到了$R$。

### 多点求值

咕咕咕

### 多点插值

咕咕咕

### 复合逆（拉格朗日反演）

给出$F(x)$求$G(x)$满足$F\circ G=G\circ F =id$（$id$为恒等函数）
$$
[x^n]G(x)=\frac{1}{n} [x^{n-1}] (\frac{x}{F(x)})^n
$$
（$[x^n]G(x)$表示$G(x)$的$n$次项。）

证明：

令$G=\sum\limits_{i=0}^{\infty} a_i x^i$

要求$\sum\limits_{i=0}^{\infty} a_i F^i(x)=x$

然后两边对$x$求导
$$
\frac{\mathrm{d}\sum\limits_{i=0}^{\infty} a_i F^i(x) }{\mathrm{d}x}=1
$$

$$
1=\sum_{i=1}^{\infty} a_i\cdot iF^{i-1}(x) F'(x)
$$

然后左右两边同时除以$F^n(x)$
$$
\frac{1}{F^n(x)} =\frac{ \sum\limits_{i=1}^{\infty} a_i \cdot i F^{i-1}(x) F'(x)} {F^{n}(x)}
$$
两边同时取$[x^{-1}]$得到 
$$
[x^{-1}]\sum_{i=0}^{\infty} i \cdot a_i F^{i-n-1}(x)F'(x)=[x^{-1}]\frac{1}{F^n(x)}
$$
然后考虑这个$\sum$的式子

分两种情况

1. $i \neq n$，$F^{i-n-1}(x)F'(x)$这个东西是刚刚求导求出来的东西，所以可以搞回去$=\frac{1}{i-n} (F^{i-n}(x))'$这个东西是一个多项式$\in R[[x]]$（用两个中括号表示$x$的幂都$\ge 0$，就形式幂级数化），所以不存在$x^{-1}$项，所以这边是$0$。
2. $i=n$，当$i=n$时，上面有一个$F^{-1}(x)$，这个东西想要求导直接用$0$次方是求不出来的，相当应用$\ln$求导，$\frac{F'(x)}{F(x)}$，而不是用多项式求导。（然而也没用$\ln$求导），考虑直接写出来$\frac{F'(x)}{F(x)}=\frac{a_1+2a_2x+3a_3x^2+\ldots}{a_1x+a_2x^2+a_3x^3+\ldots}=\frac{a_1\ldots}{a_1x}\cdot \frac{1}{1+\frac{a_2}{a_1}x+\frac{a_3}{a_1}x^2+\ldots}$，后面那个东西是一个多项式的逆，因为常数项为$1$，所以可以逆。而前面那个东西$[x^{-1}]$上的系数为$1$,而后面那个东西$[x^0]=1$，所以$a_n=[x^{-1}]\frac{1}{F^{n}(x)}$

所以就有$[x^n]G(x)=\frac{1}{n} [x^{n-1}] (\frac{x}{F(x)})^n$

更有趣的东西：

### 扩展拉格朗日反演

这里公式好像挂了

![QQ图片20210512112912.png](https://i.loli.net/2021/05/12/JFV58geykI6XGs1.png)
$$
[x^n]H(G(x))=\frac{1}{n}[ x^{n-1} ](H'(x)(\frac{x}{F(x)})^n )
$$

这个东西记住即可，证明没有什么用，而且我也不会。

而且不像前面的东西的证明过程可能会有点用...

