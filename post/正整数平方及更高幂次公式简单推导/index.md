
<!--more-->

首先是$\sum\limits_{i=1}^n i$

因为$(n+1)^2-n^2=2\times n+1$

$\begin{align} (n+1)^2-n^2+n^2-(n-1)^2+\cdots +2^2-1^2 & = 2n+1+2(n-1)+1+\cdots+2+1  \end{align}$

$\begin{align}  (n+1)^2-1=2\times \sum_{i=1}^n i+n  \\ \end{align}$

$\begin{align}  \frac{n(n+1)}{2}=\sum\limits_{i=1}^n i\\ \end{align}$



之后推导到平方上去。

$(n+1)^3-n^3=3n^2+3n+1$

$\to (n+1)^3-n^3+n^3-(n-1)^3+\cdots +2^3-1^3=3\sum\limits_{i=1}^ni^2+3\sum\limits_{i=1}^ni+n$

$\to (n+1)^3-1-\frac{3n(n+1)}{2}-n=3\sum\limits_{i=1}^n i^2$

$\to (n+1)[(n+1)^2-\frac{3n}{2}-1]=3\sum\limits_{i=1}^n i^2$

$\to \frac{(n+1)(2n+1)n}{6}=\sum\limits_{i=1}^n i^2$ 



以此类推

$\sum\limits_{i=1}^n i^k=$最高次数为$k+1$的$n$的多项式





以及附带独特版本：

已知离散求和与连续求积分之间的关系 (可以画图直观理解):

![[公式]](https://www.zhihu.com/equation?tex=%5Csum_%7Bi%3D1%7D%5En+i%5E2+%3D+%5Cint_0%5En+x%5E2+%5Cmathrm%7Bd%7D+x+%2B+%5Csum_%7Bi%3D1%7D%5En+%5Cint_%7Bi-1%7D%5Ei+%28i%5E2+-x%5E2%29+%5Cmathrm%7Bd%7D+x)

因为：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Baligned%7D%5Cint_%7Bi-1%7D%5Ei+%28i%5E2+-x%5E2%29+%5Cmathrm%7Bd%7D+x+%0A%26%3D+%5Cleft.+%5Cleft%28i%5E2+x+-+%5Cfrac%7B1%7D%7B3%7Dx%5E3%5Cright%29+%5Cright%7C_%7Bi-1%7D%5Ei++%5C%5C%0A%26%3D+%5Cleft%28i%5E3+-+%5Cfrac%7B1%7D%7B3%7Di%5E3%5Cright%29+-+%5Cleft%28i%5E2+%28i-1%29+-+%5Cfrac%7B1%7D%7B3%7D%28i-1%29%5E3+%5Cright%29+%5C%5C%0A%26%3D+%5Cfrac%7B1%7D%7B3%7D%28i-1%29%5E3+-%5Cfrac%7B1%7D%7B3%7Di%5E3+%2B+i%5E2+%5C%5C%0A%26%3D+%5Cfrac%7B1%7D%7B3%7D+%28i%5E3+-+3i%5E2+%2B+3i+-+1%29+-%5Cfrac%7B1%7D%7B3%7Di%5E3+%2B+i%5E2+%5C%5C%0A%26%3D+i+-+%5Cfrac%7B1%7D%7B3%7D%0A%5Cend%7Baligned%7D)

所以：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Baligned%7D%0A%5Csum_%7Bi%3D1%7D%5En+i%5E2+%0A%26%3D+%5Cint_0%5En+x%5E2+%5Cmathrm%7Bd%7D+x+%2B+%5Csum_%7Bi%3D1%7D%5En+%5Cint_%7Bi-1%7D%5Ei+%28i%5E2+-x%5E2%29+%5Cmathrm%7Bd%7D+x+%5C%5C%0A%26%3D+%5Cint_0%5En+x%5E2+%5Cmathrm%7Bd%7D+x+%2B+%5Csum_%7Bi%3D1%7D%5En+%5Cleft%28i+-+%5Cfrac%7B1%7D%7B3%7D%5Cright%29+%5Cend%7Baligned%7D)

又因为：

![[公式]](https://www.zhihu.com/equation?tex=%5Cint_0%5En+x%5E2+%5Cmathrm%7Bd%7D+x%3D+%5Cleft.+%5Cfrac%7B1%7D%7B3%7Dx%5E3+%5Cright%7C_0%5En+%3D+%5Cfrac%7B1%7D%7B3%7Dn%5E3)

所以：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Baligned%7D%0A%5Csum_%7Bi%3D1%7D%5En+i%5E2+%0A%26%3D+%5Cfrac%7B1%7D%7B3%7Dn%5E3+%2B+%5Cfrac%7Bn%28n%2B1%29%7D%7B2%7D+-+%5Cfrac%7Bn%7D%7B3%7D+%5C%5C%0A%26%3D+%5Cfrac%7Bn%28n%2B1%29%282n%2B1%29%7D%7B6%7D+%5C%5C%0A%5Cend%7Baligned%7D)

