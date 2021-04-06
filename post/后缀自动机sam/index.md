
<!--more-->

## 一些前置约定/定义

记$\Sigma$为字符集，$|\Sigma|$为字符集大小。对于一个字符串$\texttt s$，记$|s|$为其长度。

## 概述

**后缀自动机**$\texttt{(suffix automaton,SAM)}$是一个能解决许多字符串相关问题的数据结构。

举个例子，以下的字符串问题都可以在线性时间内通过$\texttt{SAM}$解决。

- 在另一个字符串中搜索一个字符串的所有出现位置。
- 计算给定的字符串中有多少个不同的子串。

直观上，字符串的$\texttt{SAM}$可以理解为给定字符串的**所有子串**的压缩形式。值得注意的事实是，$\texttt{SAM}$将所有的这些信息以高度压缩的形式储存。对于一个长度为$\texttt n$的字符串，它的空间复杂度仅为$O(n)$。此外，构造$\texttt{SAM}$的时间复杂度仅为$O(n)$。准确地说，一个$\texttt{SAM}$最多有$2n-1$个节点和$3n-4$条转移边。

## SAM的定义

可以且仅可以接受母串$\texttt S$的后缀的$\texttt{DFA}$（确定性有限自动机或确定性有限状态自动机）。

换句话说：

- $\texttt{SAM}$是一张$\texttt{DAG}$。节点被称为**状态**，边被称作状态间的**转移**。
- 图存在一个源点$t_0$，称为**初始状态**，其它各节点均可从$t_0$出发到达。
- 每个**转移**都标有一些字母（？个人认为就是一个字符）。从一个节点出发的所有转移均**不同**。
- 存在一个或多个**终止状态**。如果我们从初始状态$t_0$出发，最终转移到了一个终止状态，则路径上的所有转移连接起来一定是字符串$\texttt s$的一个后缀。$\texttt s$的每个后缀均可用一条从$t_0$到某个终止状态的路径构成。
- 在所有满足上述条件的自动机中，$\texttt{SAM}$的节点是最少的。

## 子串的性质

$\texttt{SAM}$最简单、也最重要的性质是，它包含关于字符串$\texttt s$的所有子串的信息。任意从初始状态$t_0$开始的路径，如果我们将转移路径上的标号写下来，都会形成$\texttt s$的一个**子串**。反之每个$\texttt s$的子串对应从$t_0$开始的某条路径。

为了简化表达，我们称子串**对应**一条路径（从$t_0$开始、由一些标号构成这些子串）。反过来，我们说任意一条路径**对应**它的标号构成的字符串。

到达某个状态的路径可能不止一条，因此我们说一个状态对应一些字符串的集合，这个集合的每个元素对应这些路径。

## 结束位置endpos

考虑字符串$\texttt s$的任意非空子串$\texttt t$，我们记$\texttt{endpos(t)}$为在字符串$\texttt s$中$\texttt t$的所有结束位置（假设对字符串中字符的编号从零开始）。例如，对于字符串$\texttt{abcbc}$，我们有$\texttt{endpos("bc")=2,4}$。

两个子串$t_1$与$t_2$的$\texttt{endpos}$集合可能相同：$endpos(t1)=endpos(t2)$。这样所有字符串$\texttt s$的非空子串都可以根据它们的$\texttt{endpos}$集合被分为若干**等价类**。

显然，$\texttt{SAM}$中的每个状态对应一个或多个$\texttt{endpos}$相同的子串。换句话说，$\texttt{SAM}$中的状态数等于所有子串的等价类的个数，再加上初始状态。$\texttt{SAM}$的状态个数等价于$\texttt{endpos}$相同的一个或多个子串所组成的集合的个数$+1$。

我们稍后将会用这个假设来介绍构造$\texttt{SAM}$的算法。我们将发现，$\texttt{SAM}$需要满足的所有性质，除了最小性以外都满足了。由$\texttt{Nerode}$定理我们可以得出最小性（不会在这篇文章中证明）。

由$\texttt{endpos}$的值我们可以得到一些重要结论：

> **引理$\texttt 1$：** 字符串$\texttt s$的两个非空子串$\texttt u$和$\texttt w$（假设$|u|\leq |w|$）的$\texttt{endpos}$相同，当且仅当字符串$\texttt u$在$\texttt s$中的每次出现，都是以$\texttt w$后缀的形式存在的。

引理显然成立。且如果$\texttt u$为$\texttt w$的一个后缀，且只以后缀的形式在$\texttt s$中出现时，两个子串的$\texttt{endpos}$相同。

> **引理 $\texttt 2$：**考虑两个非空子串$\texttt u$和$\texttt w$（假设$|u|\leq|w|$）。那么要么$endpos(u)\cap endpos(w)=\varnothing$，要么$endpos(w)\subseteq endpos(u)$,取决于$\texttt u$是否是$\texttt w$的一个后缀：
>
> $\begin{cases} endpos(w)\subseteq  endpos(u) & \mbox{if }u\mbox{ is a suffix of w} \\ endpos(w)\cap  endpos(u)=\varnothing   & otherwise \end{cases}$

证明：如果集合$endpos(u)$与$endpos(w)$有至少一个公共元素，那么由于字符串$\texttt u$和$\texttt w$在相同位置结束，$\texttt u$是$\texttt w$是的一个后缀。所以每次$\texttt w$出现的位置，子串$\texttt u$也会出现。所以$endpos(w)\subseteq endpos(u)$。

>**引理$\texttt 3$：**考虑一个$endpos$等价类，将类中的所有子串按长度非递增的顺序排序。每个子串都不会比它前一个子串长，与此同时每个子串也是它前一个子串的后缀。换句话说，对于同一等价类的任一两子串，较短者为较长者的后缀，且该等价类中的子串长度恰好覆盖整个区间 $[x,y]$

证明：如果$endpos$等价类中只包含一个子串，引理显然成立。现在我们来讨论子串元素个数大于$\texttt 1$的等价类。

由引理$\texttt 1$，两个不同的$endpos$等价的字符串中，较短者总是较长者的真后缀。因此，等价类中没有等长的字符串。

记$\texttt w$为等价类中最长的字符串、$\texttt u$为等价类中最短的字符串。由引理$\texttt 1$，字符串$\texttt u$是字符串$\texttt w$的真后缀。现在考虑长度在区间$\texttt{[|u|,|w|]}$中的$\texttt{|w|}$的任意后缀。容易看出，这个后缀也在同一等价类中，因为这个后缀只能在字符串$\texttt s$中以$\texttt w$的一个后缀的形式存在（也因为较短的后缀$\texttt u$在$\texttt s$中只以$\texttt w$的后缀形式存在）。因此，由引理$\texttt 1$，这个后缀和字符串$\texttt w$的$\texttt{endpos}$相同。

## 后缀链接link

考虑$\texttt{SAM}$中某个不是$t_0$的状态$\texttt v$。我们已经知道，状态$\texttt v$对应于具有相同$\texttt{endpos}$的等价类。我们如果定义$\texttt w$为这些字符串中最长的一个，则所有其他的字符串都是$\texttt w$的后缀。

我们还知道字符串$\texttt w$的前几个后缀（按长度降序考虑）全部包含于这个等价类，且所有其他后缀（至少有一个——空后缀）在其他的等价类中。我们即$\texttt t$为最长的这样的后缀，然后将$\texttt v$的后缀链接到$\texttt t$上。

换句话说，一个**后缀链接$\texttt{link(v)}$**连接到对应于$\texttt w$的最长后缀的另一个$\texttt{endpos}$等价类的状态。

以下我们假设初始状态$t_0$对应与它自己这个等价类（只包含一个空字符串）。为了方便，我们规定$\operatorname {endpos}(t_0)=\{-1,0,\cdots,|S|-1\}$。

>**引理$\texttt 4$：** 所有后缀链接构成一棵根节点为$t_0$的树。

证明：考虑任意不是$t_0$的状态$\texttt v$，后缀链接$\texttt{link(v)}$连接到的状态对应严格更短的字符串（后缀链接的定义、引理$\texttt 3$）。因此，沿后缀链接移动，我们总是能到达对应空串的初始状态$t_0$。

> **引理$\texttt 5$：** 通过$\texttt{endpos}$集合构造的树（每个子节点的$\texttt{subset}$都包含在在父节点的$\texttt{subset}$中）与通过后缀链接$\texttt{link}$构造的树相同。

证明：由引理$\texttt{2}$，任意一个$\texttt{SAM}$的$\texttt{endpos}$集合形成了一棵树（因为两个集合要么完全没有交集要么一个是另一个的子集）。

我们现在考虑任意不是$t_0$的状态$\texttt v$及后缀链接$\texttt{link(v)}$，由后缀链接和引理$\texttt 2$，我们可以得到

$endpos(v)\subset endpos(link(v))$，

注意这里是真子集，因为若$\texttt{endpos(v)=endpos(link(v))}$，那么$\texttt v$和$\texttt{link(v)}$应该被合并为一个节点。

结合前面的引理有：后缀链接构成的树本质上是由$\texttt{endpos}$集合构成的一棵树。

以下是对字符串$\texttt{"abcbc"}$构造$\texttt{SAM}$时产生的后缀链接树的一个**例子**，节点被标记为对应等价类中最长的子串。

![img](https://oi-wiki.org/string/images/SAM/SA_suffix_links.svg)

## 小结

- $\texttt s$的子串可以根据它们结束的位置$\texttt {endpos}$被划分为多个等价类；
- $\texttt{SAM}$由初始状态$t_0$和与每一个$\texttt{endpos}$等价类对应的每个状态组成；
- 对于每一个状态$\texttt v$一个或多个子串与之匹配。我们记$\texttt{longest(v)}$为其中最长的一个字符串，记$\texttt{len(v)}$为它的长度。类似地，记$\texttt{shortest(v)}$为最短的子串，它的长度为$\texttt{minlen(v)}$。那么对应这个状态的所有字符串都是字符串$\texttt{longest(v)}$的不同的后缀 ，且所有字符串的长度恰好覆盖区间$\texttt{[minlen(v),len(v)]}$中的每一个整数。
- 对于任意不是$t_0$的状态$\texttt v$，定义后缀链接为连接到对应字符串$\texttt{longest(v)}$的长度为$\texttt{minlen(v)-1}$的后缀的一条边。从根节点$t_0$出发的后缀链接可以形成一棵树。这棵树也表示$\texttt{endpos}$集合间的包含关系。
- 对于$t_0$以外的状态$\texttt v$，可用后缀链接$\texttt{link(v)}$表达$\texttt{minlen(v)}$：$\texttt{minlen(v)=len(link(v))+1}$。
- 如果我们从任意状态$v_0$开始顺着后缀链接遍历，总会到达初始状态$t_0$。这种情况下我们可以得到一个互不相交的区间$[minlen(v_i),len(v_i)]$的序列，且它们的并集形成了连续的区级$[0,len(v_0)]$。



以上内容均来自[oi-wiki](https://oi-wiki.org/string/sam/#_2)



其结构包含两部分：有向单词无环图（$\texttt{DAWG}$）以及一棵树（$\texttt{parent}$树）。

它们的节点集合相同。

目标：最小化节点集合大小！

### DAWG

$\texttt{DAWG}$是$\texttt{DAG}$，其中每个**节点**表示一个或多个$\texttt{S}$的子串。特别地，起始节点对应$\varnothing$。

每条转移边上仅有一个字符。从起始节点出发，沿着转移边移动，则每条**路径**都会唯一对应$\texttt{S}$的一个子串。

每个节点所代表的字符串是$\texttt{S}$的**某个前缀**的**长度连续的后缀**。设$\texttt u$的长度最小、最大的子串分别为$\min_u$和$\max_v$，$\max_u$在$\texttt S$中出现的位置集合为$end_u$。

#### 定理

任意两个节点的 end 集合互不相同。

### parent  树

#### 定义

定义$\texttt u$的**$\texttt{parent}$指针**指向$\texttt v$,当且仅当$|\min_u|=|\max_v|+1$，且$\texttt v$所代表的子串均为$\texttt u$子串的后缀，记作$next_u=v$。

显然，所有节点沿着**$\texttt{parent}$指针**向前走，都会走到$\texttt{DAWG}$的起始节点。因此以**$\texttt{parent}$指针**为边，所有节点组成了一棵树，称为**$\texttt{parent}$树**。

#### 定理

在**$\texttt{parent}$树**中，子节点的$end$集合一定是父亲的真子集，即$end_u \subset end_{next_u}$。

#### 简易构造SAM例子

用蓝色表示初始状态，用绿色表示终止状态。

对于字符串$s=\varnothing$

![img](https://oi-wiki.org/string/images/SAM/SA.svg)

对于字符串$s=a:$

![img](https://oi-wiki.org/string/images/SAM/SAa.svg)

对于字符串$s=aa:$

![img](https://oi-wiki.org/string/images/SAM/SAaa.svg)

对于字符串$s=ab:$

![img](https://oi-wiki.org/string/images/SAM/SAab.svg)

对于字符串$s=abb:$

![img](https://oi-wiki.org/string/images/SAM/SAabb.svg)

对于字符串$s=abbb:$

![img](https://oi-wiki.org/string/images/SAM/SAabbb.svg)

## 构建：增量法

$\texttt{SAM}$的构建使用**增量法**：通过$\texttt S$的$\texttt{SAM}$求出$\texttt{S+c}$的$\texttt{SAM}$。

设此前表示$\texttt S$的节点为$\texttt p$，$\texttt{parent}$树上从$\texttt p$到起始节点的路径为

$v_1=p,v_2,\cdots,v_k$，则一定存在一个$\texttt i$，使得$v_1$~$v_i$都没有$\texttt c$的转移边：

![Picture.png](https://i.loli.net/2021/03/19/17XPAR8ZK4iMu2v.png)

若$v_i$有$\texttt c$的转移边，则$v_{i+1}$也必有，故没有$\texttt c$转移边的点是$\texttt v$序列的一个前缀：在这个例子中为$v_1$~$v_2$。

（注：由于$\max_{v_5}+c$属于白板，$\min_{v_4}+c$属于$d$，且$v_4$是$v_5$的$\texttt{parent}$，所以有$|\max_{v_5}|+1=|min_{v_4}|$，所以$d$的$\texttt{parent}$为白板。）

$v_1$~$v_2$添加$\texttt c$得到的是新串长度连续的后缀，用新节点$\texttt u$表示，则：$\max_u=\max_{v_1}+\texttt c,\min_u=\min_{v_2}+\texttt c$。

![Pi2cture.png](https://i.loli.net/2021/03/19/vI1wGCMLxWqolU6.png)



共新增了$\texttt{|S|+1}$的后缀，节点$\texttt u$表示了$\min_u$及更长的后缀，而更短的那些可以由$d$及其后缀链接上的路径上的节点来表示。

（注：这里$v_1\to v_2,v_3\to v_4,v_5\to v_6$中间实际上可能有很多点,如$v_{1.5},v_{3.4},v_{5.6}$之类的，



因此$\texttt{DAWG}$的性质已经被满足，接下来考虑$\texttt{parent}$树。

分三种情况讨论：

第一种情况

- 不存在图中的$v_3$。（即所有的点都没有到$\texttt c$的一个转移边）.

![graph.png](https://i.loli.net/2021/03/20/H5ymXgSU7Zul8Aq.png)



建一个新节点$\texttt{u}$,代表$\texttt{S+c}$串的所有后缀（最短串为$\texttt c$），既然最短的串只有一个字符那么它的$\texttt{parent}$为只能有$0$个字符的东西，空串由起始节点代表，所以新节点$\texttt u$的$\texttt{parent}$指针应该指向$\texttt{start}$节点。



- 当$v_3$存在时，分$\max_d$是否等于$\max_{v_3}+C$两种情况讨论

（这里黄色代表$\texttt{DAG}$上的，绿色代表$\texttt{parent}$树上的。）

![guidingsat%2L7XCO.png](https://i.loli.net/2021/03/20/2R9qbvweS4z8QTk.png)

如现在有串$\texttt {S=cbabba}$

![L9SW~8XTYCY55SA2(DY20.png](https://i.loli.net/2021/03/20/SGUs8qR6czWZFe1.png)

此时假设$\texttt x$为绿色这一段，此时新增一个$\texttt b$

$x\to \texttt{bab},\texttt{end={4}}$

$v_3 \to \texttt {bab,ab,end={4}}$

因为这两个集合一样，因此将会被合为一个节点，假设这个节点为$\texttt d$。

那么这个$x$点$+c$转移到的是$\texttt d$，且$x$点的父亲也是$\texttt d$。

那么就会变成这个样子,这时候会产生一个问题

![wwww55.png](https://i.loli.net/2021/03/20/mPHv9xkfcM7R6Q5.png)

考虑新加进来了字符$b$

那么$v_3$集合的$\texttt{bab,ab}$变了，而$\texttt{end={4,7}}$。

那么此时就要将$x$和$v_3$切开。

而当$max_d=max_{v_3}+C$时，即不存在这样的$x$节点。

此时情况比较简单因为我们不用拆这个点。

此时考虑一下$\texttt{u}$和$\texttt{d}$的关系。（猜一下$\texttt u$的父亲是$\texttt d$。）

证明：

首先$\texttt d$的所有串是$\texttt u$的后缀，并且需要考虑一下长度是否吻合。（这里猜一下是吻合的。）

这里稍微推一下：

$\begin{align} |max_{d}| & = |max_{v_3}+1| \\ & = |min_{v_2}|-1+1 \\ & = |min_u| -1 \\ \end{align}$

所以$u$的$\texttt{parent}$应指向$d$.



那么当$\max_d \not= \max_{v_3}+C$.

考虑$d$中的串怎么切。

假设被分割后的集合为$x+C$和$v_3+C$。（两个集合拼起来为$d$.）

用$d'$表示$x+C$,用$v$表示$v_3+C$。

首先$d'$的$\texttt{parent}$指针应该指向$v$，然后$v$的$\texttt{parent}$指向原$v_3$指向的东西。

对于原来$\texttt{parent}$指向$d$的应该都指向$d'$。（因为$d'$保留了最长串，而$\texttt{parent}$是按照最长串定的）。

然后$u$的$\texttt{parent}$应该指向$v$。



关于新建节点。

在实际操作中，每一个点需要存$\max,\min,end,next$。

而$\max$直接存长度即可，因为可以从$end$集合取一个$|\max|$的再随便弄一个下来就是$\max$了。

而$\min$可以不存，因为它一定是$next$的$\max$加上什么东西。

（因为有$end$集合所以有长度集合就可以知道有什么串）

$end$与其说是存整个集合一般情况为只存第一个出现（即$end$集合最小的数）。要得到完整的$end$集合直接在$\texttt{parent}$树上所有子树上的拼起来就得到了。所以$end$也只需要存一个数。

### 伪代码

![fff.png](https://i.loli.net/2021/03/21/fEHABvVmZsCrDdu.png)

![ggg.png](https://i.loli.net/2021/03/21/lVsgAQJPwxB5GSU.png)



空间复杂度是线性的：

证明：

节点数肯定是线性的，因为一次新建一个$u$，然后把$d$拆成两个点，所有说每次最多加$2$个点，最后总的节点数一定不到$2$倍的字符串长度。

$\texttt{parent}$树的边数也一定是线性的，因为$\texttt{parent}$树是一棵树，边数等于点数$-1$。

接下来考虑$\texttt{DAWG}$，考虑给$\texttt{DAWG}$搞一棵生成树，对于一条非树边$u\to v$，来拼一个字符串，沿着树边走到$u$，再沿着非树边走到$v$，接着随便走，（比如以字典序最小）走到一个终态。我们会经过若干条边，将这些边首尾相连就得到了一个字符串$w$，记作$f(u,v)$。（因为是树，所以沿着树边到$u$是唯一的，$u\to v$是唯一的，接下来每一步以字典序最小走也是唯一的）。

$f(u,v)=w$，$w$一定是$s$的一个后缀，因为走到接受态（接受态经过的所有东西都是后缀）。由于给出$f(u,v)$能求出唯一的$w$，给出$w$不一定能求出$f(u,v)$，所以$|u\to v|\leq |w|=|s|$，所以$|u\to v|$的数量是$\leq$串长的，所以非树边的个数是小于串长的，然后树边的个数是线性的，所以最后总的边数也是线性的。

所以空间复杂度是线性的。（用到的部分）。



时间复杂度是线性的：

懒得证了...

就大概第一个循环考虑$|\max_{next_{last}}|$，第二个考虑$|\min_{next_{last}}|$。

然后复杂度可能还有考虑如何复制边的复杂度。



接下来又是搬[oi-wiki](https://oi-wiki.org/string/sam/#_5)。

### 算法

现在我们可以学习构造 SAM 的算法了。这个算法是 **在线** 算法，我们可以逐个加入字符串中的每个字符，并且在每一步中对应地维护 SAM。

为了保证线性的空间复杂度，我们将只保存 $\operatorname{len}$ 和 $\operatorname{link}$ 的值和每个状态的转移列表，我们不会标记终止状态（但是我们稍后会展示在构造 SAM 后如何分配这些标记）。

一开始 SAM 只包含一个状态 $t_0$，编号为 $0$（其它状态的编号为 $1,2,\ldots$）。为了方便，对于状态 $t_0$ 我们指定 $\operatorname{len}=0$、$\operatorname{link}=-1$（$-1$ 表示虚拟状态）。

现在，任务转化为实现给当前字符串添加一个字符 $c$ 的过程。算法流程如下：

- 令 $\textit{last}$ 为添加字符 $c$ 之前，整个字符串对应的状态（一开始我们设 $\textit{last}=0$，算法的最后一步更新 $\textit{last}$）。
- 创建一个新的状态 $\textit{cur}$，并将 $\operatorname{len}(\textit{cur})$ 赋值为 $\operatorname{len}(\textit{last})+1$，在这时 $\operatorname{link}(\textit{cur})$ 的值还未知。
- 现在我们按以下流程进行（从状态 $\textit{last}$ 开始）。如果还没有到字符 $c$ 的转移，我们就添加一个到状态 $\textit{cur}$ 的转移，遍历后缀链接。如果在某个点已经存在到字符 $c$ 的转移，我们就停下来，并将这个状态标记为 $p$。
- 如果没有找到这样的状态 $p$，我们就到达了虚拟状态 $-1$，我们将 $\operatorname{link}(\textit{cur})$ 赋值为 $0$ 并退出。
- 假设现在我们找到了一个状态 $p$，其可以通过字符 $c$ 转移。我们将转移到的状态标记为 $q$。
- 现在我们分类讨论两种状态，要么 $\operatorname{len}(p) + 1 = \operatorname{len}(q)$，要么不是。
- 如果 $\operatorname{len}(p)+1=\operatorname{len}(q)$，我们只要将 $\operatorname{link}(\textit{cur})$ 赋值为 $q$ 并退出。
-   否则就会有些复杂。需要 **复制** 状态 $q$：我们创建一个新的状态 $\textit{clone}$，复制 $q$ 的除了 $\operatorname{len}$ 的值以外的所有信息（后缀链接和转移）。我们将 $\operatorname{len}(\textit{clone})$ 赋值为 $\operatorname{len}(p)+1$。  
    复制之后，我们将后缀链接从 $\textit{cur}$ 指向 $\textit{clone}$，也从 $q$ 指向 $\textit{clone}$。  
    最终我们需要使用后缀链接从状态 $p$ 往回走，只要存在一条通过 $p$ 到状态 $q$ 的转移，就将该转移重定向到状态 $\textit{clone}$。
- 以上三种情况，在完成这个过程之后，我们将 $\textit{last}$ 的值更新为状态 $\textit{cur}$。

如果我们还想知道哪些状态是 **终止状态** 而哪些不是，我们可以在为字符串 $s$ 构造完完整的 SAM 后找到所有的终止状态。为此，我们从对应整个字符串的状态（存储在变量 $\textit{last}$ 中），遍历它的后缀链接，直到到达初始状态。我们将所有遍历到的节点都标记为终止节点。容易理解这样做我们会准确地标记字符串 $s$ 的所有后缀，这些状态都是终止状态。

在下一部分，我们将详细叙述算法每一步的细节，并证明它的 **正确性**。
因为我们只为 $s$ 的每个字符创建一个或两个新状态，所以 SAM 只包含 **线性个** 状态。

而线性规模的转移个数，以及算法总体的线性运行时间还不那么清楚。

### 正确性证明

- 若一个转移 $(p,q)$ 满足 $\operatorname{len}(p)+1=\operatorname{len}(q)$，则我们称这个转移是 **连续的**。否则，即当 $\operatorname{len}(p)+1<\operatorname{len}(q)$ 时，这个转移被称为 **不连续的**。从算法描述中可以看出，连续的、不连续的转移是算法的不同情况。连续的转移是固定的，我们不会再改变了。与此相反，当向字符串中插入一个新的字符时，不连续的转移可能会改变（转移边的端点可能会改变）。
- 为了避免引起歧义，我们记向 SAM 中插入当前字符 $c$ 之前的字符串为 $s$。
- 算法从创建一个新状态 $\textit{cur}$ 开始，对应于整个字符串 $s+c$。我们创建一个新的节点的原因很清楚。与此同时我们也创建了一个新的字符和一个新的等价类。
- 在创建一个新的状态之后，我们会从对应整个字符串 $s$ 的状态通过后缀链接进行遍历。对于每一个状态，我们尝试添加一个通过字符 $c$ 到新状态 $\textit{cur}$ 的转移。然而我们只能添加与原有转移不冲突的转移。因此我们只要找到已存在的 $c$ 的转移，我们就必须停止。
- 最简单的情况是我们到达了虚拟状态 $-1$，这意味着我们为所有 $s$ 的后缀添加了 $c$ 的转移。这也意味着，字符 $c$ 从未在字符串 $s$ 中出现过。因此 $\textit{cur}$ 的后缀链接为状态 $0$。
- 第二种情况下，我们找到了现有的转移 $(p,q)$。这意味着我们尝试向自动机内添加一个 **已经存在的** 字符串 $x+c$（其中 $x$ 为 $s$ 的一个后缀，且字符串 $x+c$ 已经作为 $s$ 的一个子串出现过了）。因为我们假设字符串 $s$ 的自动机的构造是正确的，我们不应该在这里添加一个新的转移。然而，难点在于，从状态 $\textit{cur}$ 出发的后缀链接应该连接到哪个状态呢？我们要把后缀链接连到一个状态上，且其中最长的一个字符串恰好是 $x+c$，即这个状态的 $\operatorname{len}$ 应该是 $\operatorname{len}(p)+1$。然而还不存在这样的状态，即 $\operatorname{len}(q)>\operatorname{len}(p)+1$。这种情况下，我们必须通过拆开状态 $q$ 来创建一个这样的状态。
- 如果转移 $(p,\,q)$ 是连续的，那么 $\operatorname{len}(q)=\operatorname{len}(p)+1$。在这种情况下一切都很简单。我们只需要将 $\textit{cur}$ 的后缀链接指向状态 $q$。
-   否则转移是不连续的，即 $\operatorname{len}(q)>\operatorname{len}(p)+1$，这意味着状态 $q$ 不只对应于长度为 $\operatorname{len}(p)+1$ 的后缀 $s+c$，还对应于 $s$ 的更长的子串。除了将状态 $q$ 拆成两个子状态以外我们别无他法，所以第一个子状态的长度就是 $\operatorname{len}(p)+1$ 了。  
    我们如何拆开一个状态呢？我们 **复制** 状态 $q$，产生一个状态 $\textit{clone}$，我们将 $\operatorname{len}(\textit{clone})$ 赋值为 $\operatorname{len}(p)+1$。由于我们不想改变遍历到 $q$ 的路径，我们将 $q$ 的所有转移复制到 $\textit{clone}$。我们也将从 $\textit{clone}$ 出发的后缀链接设置为 $q$ 的后缀链接的目标，并设置 $q$ 的后缀链接为 $\textit{clone}$。  
    在拆开状态后，我们将从 $\textit{cur}$ 出发的后缀链接设置为 $\textit{clone}$。  
    最后一步我们将一些到 $q$ 转移重定向到 $\textit{clone}$。我们需要修改哪些转移呢？只重定向相当于所有字符串 $w+c$（其中 $w$ 是 $p$ 的最长字符串）的后缀就够了。即，我们需要继续沿着后缀链接遍历，从结点 $p$ 直到虚拟状态 $-1$ 或者是转移到不是状态 $q$ 的一个转移。

### 对操作次数为线性的证明

首先我们假设字符集大小为 **常数**。如果字符集大小不是常数，SAM 的时间复杂度就不是线性的。从一个结点出发的转移存储在支持快速查询和插入的平衡树中。因此如果我们记 $\Sigma$ 为字符集，$\left|\Sigma\right|$ 为字符集大小，则算法的渐进时间复杂度为 $O(n\log\left|\Sigma\right|)$，空间复杂度为 $O(n)$。然而如果字符集足够小，可以不写平衡树，以空间换时间将每个结点的转移存储为长度为 $\left|\Sigma\right|$ 的数组（用于快速查询）和链表（用于快速遍历所有可用关键字）。这样算法的时间复杂度为 $O(n)$，空间复杂度为 $O(n\left|\Sigma\right|)$。（其实可以哈希表把空间也搞到均摊$O(n)$）

所以我们将认为字符集的大小为常数，即每次对一个字符搜索转移、添加转移、查找下一个转移。这些操作的时间复杂度都为 $O(1)$。

如果我们考虑算法的各个部分，算法中有三处时间复杂度不明显是线性的：

- 第一处是遍历所有状态 $\textit{last}$ 的后缀链接，添加字符 $c$ 的转移。
- 第二处是当状态 $q$ 被复制到一个新的状态 $\textit{clone}$ 时复制转移的过程。
- 第三处是修改指向 $q$ 的转移，将它们重定向到 $\textit{clone}$ 的过程。

我们使用 SAM 的大小（状态数和转移数）为 **线性的** 的事实（对状态数是线性的的证明就是算法本身，对转移数为线性的的证明将在稍后实现算法后给出）。

因此上述 **第一处和第二处** 的总复杂度显然为线性的，因为单次操作均摊只为自动机添加了一个新转移。

还需为 **第三处** 估计总复杂度，我们将最初指向 $q$ 的转移重定向到 $\textit{clone}$。我们记 $v=\operatorname{longest}(p)$，这是一个字符串 $s$ 的后缀，每次迭代长度都递减——因为字符串 $s$ 的位置每次迭代都单调上升。这种情况下，如果在循环的第一次迭代之前，相对应的字符串 $v$ 在距离 $\textit{last}$ 的深度为 $k$ $(k\ge 2)$ 的位置上（深度记为后缀链接的数量），那么在最后一次迭代后，字符串 $v+c$ 将会成为路径上第二个从 $\textit{cur}$ 出发的后缀链接（它将会成为新的 $\textit{last}$ 的值）。

因此，循环中的每次迭代都会使作为当前字符串的后缀的字符串 $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last}))$ 的位置单调递增。因此这个循环最多不会执行超过 $n$ 次迭代，这正是我们需要证明的。

## 更多性质

### 状态数

对于一个长度为 $n$ 的字符串 $s$，它的 SAM 中的状态数 **不会超过**  $2n-1$（假设 $n\ge 2$）。

算法本身即可证明该结论。一开始，自动机含有一个状态，第一次和第二次迭代中只会创建一个节点，剩余的 $n-2$ 步中每步会创建至多 $2$ 个状态。

然而我们也能在 **不借助这个算法** 的情况下 **证明** 这个估计值。我们回忆一下状态数等于不同的 $\operatorname{endpos}$ 集合个数。这些 $\operatorname{endpos}$ 集合形成了一棵树（祖先节点的集合包含了它所有孩子节点的集合）。考虑将这棵树稍微变形一下：只要它有一个只有一个孩子的内部结点（这意味着该子节点的集合至少遗漏了它的父集合中的一个位置），我们创建一个含有这个遗漏位置的集合。最后我们可以获得一棵每一个内部结点的度数大于 1 的树，且叶子节点的个数不超过 $n$。因此这样的树里有不超过 $2n-1$ 个节点。

字符串 $\texttt{abbb} \cdots \texttt{bbb}$ 的状态数达到了该上界：从第三次迭代后的每次迭代，算法都会拆开一个状态，最终产生恰好 $2n-1$ 个状态。

### 转移数

对于一个长度为 $n$ 的字符串 $s$，它的 SAM 中的转移数 **不会超过**  $3n-4$（假设 $n\ge 3$）。

证明如下：

我们首先估计连续的转移的数量。考虑自动机中从状态 $t_0$ 开始的所有最长路径的生成树。生成树只包含连续的边，因此数量少于状态数，即边数不会超过 $2n-2$。

现在我们来估计不连续的转移的数量。令当前不连续转移为 $(p,\,q)$，其字符为 $c$。我们取它的对应字符串 $u+c+w$，其中字符串 $u$ 对应于初始状态到 $p$ 的最长路径，$w$ 对应于从 $q$ 到任意终止状态的最长路径。一方面，每个不完整的字符串所对应的形如 $u+c+w$ 的字符串是不同的（因为字符串 $u$ 和 $w$ 仅由完整的转移组成）。另一方面，由终止状态的定义，每个形如 $u+c+w$ 的字符串都是整个字符串 $s$ 的后缀。因为 $s$ 只有 $n$ 个非空后缀，且形如 $u+c+w$ 的字符串都不包含 $s$（因为整个字符串只包含完整的转移），所以非完整的转移的总数不会超过 $n-1$。

将以上两个估计值相加，我们可以得到上界 $3n-3$。然而，最大的状态数只能在类似于 $\texttt{abbb} \cdots \texttt{bbb}$ 的情况中产生，而此时转移数量显然少于 $3n-3$。

因此我们可以获得更为紧确的 SAM 的转移数的上界：$3n-4$。字符串 $\texttt{abbb} \cdots \texttt{bbbc}$ 就达到了这个上界。

### 额外信息

观察 [实现](#_8) 中的结构体的每个变量。实际上，尽管 SAM 本身由 `next` 组成，但 SAM 构造算法中作为辅助变量的 `link` 和 `len` 在应用中常常比 `next` 重要，甚至可以抛开 `next` 单独使用。

设字符串的长度为 $n$，考虑 `extend` 操作中 `cur` 变量的值，这个节点对应的状态是<u>执行 `extend` 操作时的当前字符串</u>，即字符串的一个前缀，每个前缀有一个终点。这样得到的 $n$ 个节点，对应了 $n$ 个不同的 **终点**。设第 $i$ 个节点为 $v_i$，对应的是 $S_{1 \ldots i}$，终点是 $i$。姑且把这些节点称之为“终点节点”。

考虑给 SAM 赋予树形结构，树的根为 0，且其余节点 $v$ 的父亲为 $\operatorname{link}(v)$。则这棵树与原 SAM 的关系是：

- 每个节点的终点集合等于其 **子树** 内所有终点节点对应的终点的集合。

在此基础上可以给每个节点赋予一个最长字符串，是其终点集合中 **任意** 一个终点开始 **往前** 取 `len` 个字符得到的字符串。每个这样的字符串都一样，且 `len` 恰好是满足这个条件的最大值。

这些字符串满足的性质是：

- 如果节点 A 是 B 的祖先，则节点 A 对应的字符串是节点 B 对应的字符串的 **后缀**。

这条性质把字符串所有前缀组成了一棵树，且有许多符合直觉的树的性质。例如，$S_{1 \ldots p}$ 和 $S_{1 \ldots q}$ 的最长公共后缀对应的字符串就是 $v_p$ 和 $v_q$ 对应的 LCA 的字符串。实际上，这棵树与将字符串 $S$ 翻转后得到字符串的压缩后缀树结构相同。

每个状态 $i$ 对应的子串数量是 $\operatorname{len}(i)-\operatorname{len}(\operatorname{link}(i))$（节点 $0$ 例外）。注意到 $\operatorname{link}(i)$ 对应的字符串是 $i$ 对应的字符串的一个后缀，这些子串就是 $i$ 对应字符串的所有后缀，去掉被父亲“抢掉”的那部分，即 $\operatorname{link}(i)$ 对应字符串的所有后缀。



### 实现

```c++
struct node {int len,nxt,son[26];}a[N<<1];
int lst,tn;
inline void init_SAM()
{
	a[0].len=0,a[0].nxt=-1;
	tn=0;lst=0;
}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p!=-1&&!a[p].son[c];p=a[p].nxt) a[p].son[c]=cur;
	if(p==-1) a[cur].nxt=0;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1) a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p!=-1&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}	
```

oi-wiki：

首先，我们实现一种存储一个转移的全部信息的数据结构。如果需要的话，你可以在这里加入一个终止标记，也可以是一些其它信息。我们将用一个 `map` 存储转移的列表，允许我们在总计 $O(n)$ 的空间复杂度和 $O(n\log\left|\Sigma\right|)$ 的时间复杂度内处理整个字符串。（注：在字符集大小为较小的常数，比如 26 时，将 `next` 定义为 `int[26]` 更方便）

```cpp
struct state {
  int len, link;
  std::map<char, int> next;
};
```

SAM 本身将会存储在一个 `state` 结构体数组中。我们记录当前自动机的大小 `sz` 和变量 `last`，当前整个字符串对应的状态。

```cpp
const int MAXLEN = 100000;
state st[MAXLEN * 2];
int sz, last;
```

我们定义一个函数来初始化 SAM（创建一个只有初始状态的 SAM）。

```cpp
void sam_init() {
  st[0].len = 0;
  st[0].link = -1;
  sz++;
  last = 0;
}
```

最终我们给出主函数的实现：给当前行末增加一个字符，对应地在之前的基础上建造自动机。

```c++
void sam_extend(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone].len = st[p].len + 1;
      st[clone].next = st[q].next;
      st[clone].link = st[q].link;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}
```

正如之前提到的一样，如果你用内存换时间（空间复杂度为 $O(n\left|\Sigma\right|)$，其中 $\left|\Sigma\right|$ 为字符集大小），你可以在 $O(n)$ 的时间内构造字符集大小任意的 SAM。但是这样你需要为每一个状态储存一个大小为 $\left|\Sigma\right|$ 的数组（用于快速跳转到转移的字符），和另外一个所有转移的链表（用于快速在转移中迭代）。



## 应用

下面我们来看一些可以用 SAM 解决的问题。简单起见，假设字符集的大小 $k$ 为常数。这允许我们认为增加一个字符和遍历的复杂度为常数。

### 检查字符串是否出现

> 给一个文本串 $T$ 和多个模式串 $P$，我们要检查字符串 $P$ 是否作为 $T$ 的一个子串出现。

我们在 $O(\left|T\right|)$ 的时间内对文本串 $T$ 构造后缀自动机。为了检查模式串 $P$ 是否在 $T$ 中出现，我们沿转移（边）从 $t_0$ 开始根据 $P$ 的字符进行转移。如果在某个点无法转移下去，则模式串 $P$ 不是 $T$ 的一个子串。如果我们能够这样处理完整个字符串 $P$，那么模式串在 $T$ 中出现过。

对于每个字符串 $P$，算法的时间复杂度为 $O(\left|P\right|)$。此外，这个算法还找到了模式串 $P$ 在文本串中出现的最大前缀长度。

### 不同子串个数

> 给一个字符串 $S$，计算不同子串的个数。

对字符串 $S$ 构造后缀自动机。

每个 $S$ 的子串都相当于自动机中的一些路径。因此不同子串的个数等于自动机中以 $t_0$ 为起点的不同路径的条数。

考虑到 SAM 为有向无环图，不同路径的条数可以通过动态规划计算。即令 $d_{v}$ 为从状态 $v$ 开始的路径数量（包括长度为零的路径），则我们有如下递推方程：

$$
d_{v}=1+\sum_{w:(v,w,c)\in DAWG}d_{w}
$$

即，$d_{v}$ 可以表示为所有 $v$ 的转移的末端的和。

所以不同子串的个数为 $d_{t_0}-1$（因为要去掉空子串）。

总时间复杂度为：$O(\left|S\right|)$。

```c++
const int N=222222;
struct node {int len,nxt,son[26];}a[N<<1];
int lst,tn;
inline void init_SAM()
{
	a[0].len=0,a[0].nxt=-1;
	tn=0;lst=0;
}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p!=-1&&!a[p].son[c];p=a[p].nxt) a[p].son[c]=cur;
	if(p==-1) a[cur].nxt=0;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1) a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p!=-1&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}	
int dp[N<<1];
void dfs1(int u)
{
	//writeln(u);
	if(dp[u]) return;
	R(i,0,25)
	{
		int v=a[u].son[i];
		if(!v) continue;
		dfs1(v);dp[u]+=dp[v];
	}
	dp[u]++;
}
int n;
char str[N];
int s[N];
signed main()
{
	n=read();
	scanf("%s",str+1);
	init_SAM();
	R(i,1,n) s[i]=str[i]-'a';
	R(i,1,n) extend_SAM(s[i]);
	dfs1(0);
	writeln(dp[0]-1);
}
```



另一种方法是利用上述后缀自动机的树形结构。每个节点对应的子串数量是 $\operatorname{len}(i)-\operatorname{len}(\operatorname{link}(i))$，对自动机所有节点求和即可。

（ 

$\texttt{SAM}$每个节点表示的串没有交集,而且一定表示了所有的串。

那我们把所有节点表示的串的个数(类大小)加起来就好了, 

考虑到$minlen(u)=maxlen(fa)+1,$直接统计$\sum\limits_{u}(u.len-u.fa.len)$即可。

这种方法需要对$\texttt{SAM}$的基本性质比较熟悉同时比较经典。

```c++
signed main()
{
	n=read();
	scanf("%s",str+1);
	init_SAM();
	R(i,1,n) s[i]=str[i]-'a';
	R(i,1,n) extend_SAM(s[i]);
	int ans=0;
	R(i,1,tn) ans+=a[i].len-a[a[i].nxt].len;
	writeln(ans); 
}
```

）

例题：[【模板】后缀自动机](https://www.luogu.com.cn/problem/P3804)，[SDOI2016 生成魔咒](https://loj.ac/problem/2033)

【模板】后缀自动机题解：

第一种写法比较简单就是串长度乘上$end$集合大小（之后称这个为`siz`）。

具体做法就是把每个前缀所属的点的`siz` 设为$1$，可以证明这些点是前缀对应的$end$出现的$\texttt{parent}$树上最深的点，因为无法在这些前缀前面加东西。

这种方法需要把树建出来，常数较大。

另外一种常数更小的方法是:先按照`len`排序,然后`len`大的先贡献。

由于$fa.len>u.len$正确性显然。

这个排序如果用 `std::sort` 的话复杂度反而会带 $log$ ,那就得不偿失了。

观察到所有的$len\leq n$ ,不妨使用基数排序。

但是这种方法有一定的局限性,比如说广义 $\texttt{SAM}$用不了,某些时候操作麻烦等等……

我们也维护了某个点的最长串`len`，统计$\max\limits_u[u.siz<1](u.siz\times u.len)$即可。

代码，为第一种方法：

```c++
vector<int>e[N<<1];
int n;
ll ans;
char str[N];
int s[N];
void dfs1(int u)
{
	for(int v:e[u])
	{
		dfs1(v);
		a[u].siz+=a[v].siz;
	}
	if(a[u].siz>1) ckmax(ans,1ll*a[u].siz*a[u].len);
}
signed main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	init_SAM();
	R(i,1,n) s[i]=str[i]-'a';
	R(i,1,n) extend_SAM(s[i]);
	int p=0;
	R(i,1,n)
	{
		p=a[p].son[s[i]];
		a[p].siz=1;
	}
	R(i,1,tn) e[a[i].nxt].pb(i);
	dfs1(0);
	writeln(ans);
}

```

### 所有不同子串的总长度

> 给定一个字符串 $S$，计算所有不同子串的总长度。

本题做法与上一题类似，只是现在我们需要考虑分两部分进行动态规划：不同子串的数量 $d_{v}$ 和它们的总长度 $ans_{v}$。

我们已经在上一题中介绍了如何计算 $d_{v}$。$ans_{v}$ 的值可以通过以下递推式计算：

$$
ans_{v}=\sum_{w:(v,w,c)\in DAWG}d_{w}+ans_{w}
$$

我们取每个邻接结点 $w$ 的答案，并加上 $d_{w}$（因为从状态 $v$ 出发的子串都增加了一个字符）。

算法的时间复杂度仍然是 $O(\left|S\right|)$。

同样可以利用上述后缀自动机的树形结构。每个节点对应的所有后缀长度是 $\frac{\operatorname{len}(i)\times (\operatorname{len}(i)+1)}{2}$，减去其 $\operatorname{link}$ 节点的对应值就是该节点的净贡献，对自动机所有节点求和即可。

### 字典序第 k 大子串

> 给定一个字符串 $S$。多组询问，每组询问给定一个数 $K_i$，查询 $S$ 的所有子串中字典序第 $K_i$ 大的子串。

解决这个问题的思路可以从解决前两个问题的思路发展而来。字典序第 $k$ 大的子串对应于 SAM 中字典序第 $k$ 大的路径，因此在计算每个状态的路径数后，我们可以很容易地从 SAM 的根开始找到第 $k$ 大的路径。

预处理的时间复杂度为 $O(\left|S\right|)$，单次查询的复杂度为 $O(\left|ans\right|\cdot\left|\Sigma\right|)$（其中 $ans$ 是查询的答案，$\left|\Sigma\right|$ 为字符集的大小）。

> 虽然该题是后缀自动机的经典题，但实际上这题由于涉及字典序，用后缀数组做最方便。

例题：[SPOJ - SUBLEX](https://www.spoj.com/problems/SUBLEX/)，[TJOI2015 弦论](https://loj.ac/problem/2102)

弦论简要题解：

考虑使用线段树上二分的思路在$\texttt{SAM}$上跳。

假设当前到达了某个点，暴力枚举出边，选定后剩余的$k$要减去比当前构造串小的串的个数。

- 本质相同子串只算一次

$f[u]=$从该点出发的路径的总条数，可以直接`dp`出来（类似不同子串个数方法$1$）

- 本质相同子串算多次

一个子串出现次数$s$为$end$集合大小

那么我们就是需要统计`DAG`上$u$的一颗子`DAG`内，$\sum\limits_{u\to v} v.siz$

也就是每一串的贡献就是$end$集合大小。

在本质不同子串中空串的贡献为$1$，现在改成`siz`

以及这道题不计算空串，要把$f[0]$的贡献去掉。

然后$f[0]<k$即无解。

注意其他点空串的贡献是不能去掉的,因为空串表示停止在该点。

> 给定一个字符串 $S$。找出字典序最小的循环移位。

容易发现字符串 $S+S$ 包含字符串 $S$ 的所有循环移位作为子串。

所以问题简化为在 $S+S$ 对应的后缀自动机上寻找最小的长度为 $\left|S\right|$ 的路径，这可以通过平凡的方法做到：我们从初始状态开始，贪心地访问最小的字符即可。

总的时间复杂度为 $O(\left|S\right|)$。

### 出现次数

> 对于一个给定的文本串 $T$，有多组询问，每组询问给一个模式串 $P$，回答模式串 $P$ 在字符串 $T$ 中作为子串出现了多少次。

利用后缀自动机的树形结构，进行 dfs 即可预处理每个节点的终点集合大小。在自动机上查找模式串 $P$ 对应的节点，如果存在，则答案就是该节点的终点集合大小；如果不存在，则答案为 $0$.

以下为原方法：

> 对文本串 $T$ 构造后缀自动机。
>
> 接下来做预处理：对于自动机中的每个状态 $v$，预处理 $cnt_{v}$，使之等于 $\operatorname{endpos}(v)$ 集合的大小。事实上，对应同一状态 $v$ 的所有子串在文本串 $T$ 中的出现次数相同，这相当于集合 $\operatorname{endpos}$ 中的位置数。
>
> 然而我们不能明确的构造集合 $\operatorname{endpos}$，因此我们只考虑它们的大小 $cnt$。
>
> 为了计算这些值，我们进行以下操作。对于每个状态，如果它不是通过复制创建的（且它不是初始状态 $t_0$），我们将它的 $cnt$ 初始化为 1。然后我们按它们的长度 $\operatorname{len}$ 降序遍历所有状态，并将当前的 $cnt_{v}$ 的值加到后缀链接指向的状态上，即：
>
> $$
> cnt_{\operatorname{link}(v)}+=cnt_{v}
> $$
>
> 这样做每个状态的答案都是正确的。
>
> 为什么这是正确的？不是通过复制获得的状态，恰好有 $\left|T\right|$ 个，并且它们中的前 $i$ 个在我们插入前 $i$ 个字符时产生。因此对于每个这样的状态，我们在它被处理时计算它们所对应的位置的数量。因此我们初始将这些状态的 $cnt$ 的值赋为 $1$，其它状态的 $cnt$ 值赋为 $0$。
>
> 接下来我们对每一个 $v$ 执行以下操作：$cnt_{\operatorname{link}(v)}+=cnt_{v}$。其背后的含义是，如果有一个字符串 $v$ 出现了 $cnt_{v}$ 次，那么它的所有后缀也在完全相同的地方结束，即也出现了 $cnt_{v}$ 次。
>
> 为什么我们在这个过程中不会重复计数（即把某些位置数了两次）呢？因为我们只将一个状态的位置添加到 **一个** 其它的状态上，所以一个状态不可能以两种不同的方式将其位置重复地指向另一个状态。
>
> 因此，我们可以在 $O(\left|T\right|)$ 的时间内计算出所有状态的 $cnt$ 的值。
>
> 最后回答询问只需要查找值 $cnt_{t}$，其中 $t$ 为模式串对应的状态，如果该模式串不存在答案就为 $0$。单次查询的时间复杂度为 $O(\left|P\right|)$。

（$\texttt{SAM}$本质上是将一个trie压缩后得到的结果，所以可以直接跳转移边得到，最后结果就是状态数。状态数可以dfs预处理出来，时间复杂度$O(|S|+|T|)$。）



### 第一次出现的位置

> 给定一个文本串 $T$，多组查询。每次查询字符串 $P$ 在字符串 $T$ 中第一次出现的位置（$P$ 的开头位置）。

我们构造一个后缀自动机。我们对 SAM 中的所有状态预处理位置 $\operatorname{firstpos}$。即，对每个状态 $v$ 我们想要找到第一次出现这个状态的末端的位置 $\operatorname{firstpos}[v]$。换句话说，我们希望先找到每个集合 $\operatorname{endpos}$ 中的最小的元素（显然我们不能显式地维护所有 $\operatorname{endpos}$ 集合）。

为了维护 $\operatorname{firstpos}$ 这些位置，我们将原函数扩展为 `sam_extend()`。当我们创建新状态 $\textit{cur}$ 时，我们令：

$$
\operatorname{firstpos}(\textit{cur})=\operatorname{len}(\textit{cur})-1
$$

；当我们将结点 $q$ 复制到 $\textit{clone}$ 时，我们令：

$$
\operatorname{firstpos}(\textit{clone})=\operatorname{firstpos}(q)
$$

（因为值的唯一的其它选项 $\operatorname{firstpos}(\textit{cur})$ 显然太大了）。

那么查询的答案就是 $\operatorname{firstpos}(t)-\left|P\right|+1$，其中 $t$ 为对应字符串 $P$ 的状态。单次查询只需要 $O(\left|P\right|)$ 的时间。

### 所有出现的位置

> 问题同上，这一次需要查询文本串 $T$ 中模式串出现的所有位置。

利用后缀自动机的树形结构，遍历子树，一旦发现终点节点就输出。

以下为原解法：

> 我们还是对文本串 $T$ 构造后缀自动机。与上一个问题相似，我们为所有状态计算位置 $\operatorname{firstpos}$。
>
> 如果 $t$ 为对应于模式串 $T$ 的状态，显然 $\operatorname{firstpos}(t)$ 为答案的一部分。需要查找的其它位置怎么办？我们使用了含有字符串 $P$ 的自动机，我们还需要将哪些状态纳入自动机呢？所有对应于以 $P$ 为后缀的字符串的状态。换句话说我们要找到所有可以通过后缀链接到达状态 $t$ 的状态。
>
> 因此为了解决这个问题，我们需要为每一个状态保存一个指向它的后缀引用列表。查询的答案就包含了对于每个我们能从状态 $t$ 只使用后缀引用进行 DFS 或 BFS 的所有状态的 $\operatorname{firstpos}$ 值。
>
> 这种变通方案的时间复杂度为 $O(\textit{answer}(P))$，因为我们不会重复访问一个状态（因为对于仅有一个后缀链接指向一个状态，所以不存在两条不同的路径指向同一状态）。
>
> 我们只需要考虑两个可能有相同 $\operatorname{endpos}$ 值的不同状态。如果一个状态是由另一个复制而来的，则这种情况会发生。然而，这并不会对复杂度分析造成影响，因为每个状态至多被复制一次。
>
> 此外，如果我们不从被复制的节点输出位置，我们也可以去除重复的位置。事实上对于一个状态，如果经过被复制状态可以到达，则经过原状态也可以到达。因此，如果我们给每个状态记录标记 `is_clone` 来代表这个状态是不是被复制出来的，我们就可以简单地忽略掉被复制的状态，只输出其它所有状态的 $firstpos$ 的值。
>
> 以下是大致的实现：
>
> ```cpp
> struct state {
> bool is_clone;
> int first_pos;
> std::vector<int> inv_link;
> // some other variables
> };
> 
> // 在构造 SAM 后
> for (int v = 1; v < sz; v++) st[st[v].link].inv_link.push_back(v);
> 
> // 输出所有出现位置
> void output_all_occurrences(int v, int P_length) {
> if (!st[v].is_clone) cout << st[v].first_pos - P_length + 1 << endl;
> for (int u : st[v].inv_link) output_all_occurrences(u, P_length);
> }
> ```

### 最短的没有出现的字符串

> 给定一个字符串 $S$ 和一个特定的字符集，我们要找一个长度最短的没有在 $S$ 中出现过的字符串。

我们在字符串 $S$ 的后缀自动机上做动态规划。

令 $d_{v}$ 为节点 $v$ 的答案，即，我们已经处理完了子串的一部分，当前在状态 $v$，想找到不连续的转移需要添加的最小字符数量。计算 $d_{v}$ 非常简单。如果不存在使用字符集中至少一个字符的转移，则 $d_{v}=1$。否则添加一个字符是不够的，我们需要求出所有转移中的最小值：

$$
d_{v}=1+\min_{w:(v,w,c)\in SAM}d_{w}
$$

问题的答案就是 $d_{t_0}$，字符串可以通过计算过的数组 $d$ 逆推回去。

### $\texttt{SAM}$与$\texttt{AC}$自动机的相似性

回忆：自动机某个点表示的串，是指根到该点的路径构成的所有串。

众所周知，AC自动机的`fail`指针指向的地方，是该节点表示的串的最长后缀，也就是把前面去掉（尽可能少的）一点。

我们注意到$\texttt{SAM}$的`fa`指针有同样的性质：儿子是由父亲在前面加字符产生的，那么父亲就可以视作在儿子前面去掉字符。

我们完全可以将$\texttt{SAM}$理解为把某个串的所有子串建立AC自动机。

#### [**SP1811 LCS - 最长公共子串**](https://www.luogu.org/problem/SP1811)

将两个串称为$S_1,S_2$，

对于$S_2$设一个数组为$slen[1\cdots|S_2|]$。

$slen[i]$表示$S_1$中$S_1[i-slen[i]+1,i]$在$S_2$中出现过，即以$i$**结尾**的位置的**最长匹配长度**。

即"每个前缀匹配出的最长后缀"，不难发现，$slen$数组的$\max$就是答案。

具体做法：

对$S_1$建立SAM，然后当做AC自动机来用。

把$S_2$拿到上面跑匹配，如果当前节点有出边则匹配长度++

否则，跳`fail`直到有出边位置，匹配长度变为该点的`len+1`。

如果回到根还是不能匹配，匹配长度是$0$。

代码：

```c++
const int N=555555;
struct node {int len,nxt,son[26];}a[N];
int lst,tn;
char str[N];
int len1,len2;
int s1[N],s2[N];
int slen[N];
inline void init_SAM(){tn=lst=1;}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p&&!a[p].son[c];p=a[p].nxt) a[p].son[c]=cur;
	if(!p) a[cur].nxt=1;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1) a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}	

signed main()
{
	scanf("%s",str+1);
	len1=strlen(str+1);
	init_SAM();
	R(i,1,len1) s1[i]=str[i]-'a';
	R(i,1,len1) extend_SAM(s1[i]);
	scanf("%s",str+1);
	len2=strlen(str+1);
	R(i,1,len2) s2[i]=str[i]-'a';
	int p=1,plen=0;
	R(i,1,len2)
	{
		if(!a[p].son[s2[i]]) 
		{
			for(;p!=1&&!a[p].son[s2[i]];p=a[p].nxt);
			plen=a[p].len;
		}
		if(a[p].son[s2[i]]) p=a[p].son[s2[i]],plen++;
		slen[i]=plen;
	}	
	int ans=0;
	R(i,1,len2) ckmax(ans,slen[i]);
	writeln(ans);
}	
```



#### [SP1812 LCS2 - 多串最长公共子串](https://www.luogu.org/problem/SP1812)

类似地，把第一个串当做匹配串，其他的串建立SAM

把第一个串在每个SAM跑匹配，$slen$对当前匹配长度取$\min$。

最终答案为整个$slen$的$\max$。

代码：

```c++
const int N=2e5+10;
struct node {int len,nxt,son[26];}a[N];
int lst,tn;
char str[N];
int len1,len2;
int slen[N];
int s1[N],s2[N];

inline void init_SAM(int n){tn=lst=1;R(i,0,2*(n+1)){a[i].len=a[i].nxt=0;R(j,0,25)a[i].son[j]=0;} }
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p&&!a[p].son[c];p=a[p].nxt)a[p].son[c]=cur;
	if(!p)a[cur].nxt=1;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1)a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}

signed main()
{
	memset(slen,-1,sizeof(slen));
	scanf("%s",str+1);
	len1=strlen(str+1);
	R(i,1,len1) s1[i]=str[i]-'a';
	while(~scanf("%s",str+1))
	{
		len2=strlen(str+1);
		init_SAM(len2);
		R(i,1,len2) s2[i]=str[i]-'a';
		R(i,1,len2) extend_SAM(s2[i]);
		int p=1,plen=0;
		R(i,1,len1) 
		{
			if(!a[p].son[s1[i]]) 
			{
				for(;p!=1&&!a[p].son[s1[i]];p=a[p].nxt);
				plen=a[p].len;
			}
			if(a[p].son[s1[i]])p=a[p].son[s1[i]],plen++;
			~slen[i]?ckmin(slen[i],plen):slen[i]=plen;
		}
	}
	int ans=0;
	R(i,1,len1) ckmax(ans,slen[i]); 
	writeln(ans);
}
```



#### [CF235C Cyclical Quest](https://www.luogu.org/problem/CF235C)

先不考虑本质不同这件事。

循环就是把询问串的第一个字符拿去放在最后面。

可以视为，先把目前匹配到的串的第一个字符删掉，然后再加上一个。

如果目前这个串根本没有在文本中完整出现，那么这个删除操作可以忽略。

否则,`len--`，如果删了前面之后$len$**不在当前节点区间**($(u.fa.len,u.len]$)里面了就跳`f`。

（在前面删掉字符就是在parent树上跳的性质）

加字符操作同上。

最后将匹配到的所有节点$siz$加在一起就好了。

还要考虑去重问题：如果同一个询问串多次匹配到同一个节点，贡献只算一次，具体可以打标记实现。

代码：

```c++
const int N=1e6+10;

int tn,lst;
char str[N];
int n;
vector<int>e[N<<1];
int s1[N],s2[N];
int vis[N<<1];
int _;

struct node {int len,nxt,son[26],siz;}a[N<<1];
inline void init_SAM(){tn=lst=1;}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p&&!a[p].son[c];p=a[p].nxt)a[p].son[c]=cur;
	if(!p) a[cur].nxt=1;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1) a[cur].nxt=v;
		else 
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}
void dfs1(int u)
{
	for(int v:e[u]) dfs1(v),a[u].siz+=a[v].siz;
}
void solve()
{
	scanf("%s",str+1);n=strlen(str+1);
	R(i,1,n) s2[i]=str[i]-'a';
	int p=1,plen=0;
	R(i,1,n) 
	{
		if(!a[p].son[s2[i]])
		{
			for(;p!=1&&!a[p].son[s2[i]];p=a[p].nxt);
			plen=a[p].len;
		}
		if(a[p].son[s2[i]]) p=a[p].son[s2[i]],plen++;
	}
	int ans=0;
	R(i,1,n)
	{
		if(plen==n) 
		{
			if(vis[p]!=_) ans+=a[p].siz;
			vis[p]=_;
			if(--plen==a[a[p].nxt].len) p=a[p].nxt;
		}
		if(!a[p].son[s2[i]])
		{
			for(;p!=1&&!a[p].son[s2[i]];p=a[p].nxt);
			plen=a[p].len;
		}
		if(a[p].son[s2[i]]) p=a[p].son[s2[i]],plen++;
	}
	writeln(ans);
}
signed main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	init_SAM();
	R(i,1,n) s1[i]=str[i]-'a';
	R(i,1,n) extend_SAM(s1[i]);
	R(i,2,tn) e[a[i].nxt].pb(i);
	int p=1;R(i,1,n) p=a[p].son[s1[i]],a[p].siz=1;
	dfs1(1);
	_=read()+1;while(--_) solve();
}
```



#### [lgP6640[BJOI2020]封印](https://www.luogu.com.cn/problem/P6640)

先建立$S$的SAM，然后让$T$在上面跑匹配，求出$T$的每个前缀$i$能能够匹配的后缀长度$slen[i]$。

对于区间$[l,r]$答案为$\max\limits_{i=l}^r(\min(slen[i],i-l+1))$。

考虑二分答案$mid$满足$i-l+1\ge mid$即$i\ge mid+l-1$。

若满足这个要求，则$i-l+1$的约束就不用考虑。变成一个RMQ问题，使用ST表做到$O(1)$。

复杂度为$O(n\log n)$。

```c++
const int N=444444;
char strs[N],strt[N];
int s[N],t[N];
int l1,l2;
struct node {int len,nxt,son[26];}a[N];
int lst,tn;
int slen[N];
int _;

inline void init_SAM(){tn=lst=1;}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p&&!a[p].son[c];p=a[p].nxt)a[p].son[c]=cur;
	if(!p) a[cur].nxt=1;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1)a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}
int mx[22][N],Lg[N];
void init_ST()
{
	R(i,2,l1) Lg[i]=Lg[i>>1]+1;
	R(i,1,l1) mx[0][i]=slen[i];
	R(j,1,20) for(int i=1;i+(1<<j)-1<=l1;i++) mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<(j-1))]); 
}
inline int query(int l,int r)
{
	if(l>r) return 0;
	int i=Lg[r-l+1];
	return max(mx[i][l],mx[i][r-(1<<i)+1]);
}

signed main()
{
	scanf("%s%s",strs+1,strt+1);
	l1=strlen(strs+1),l2=strlen(strt+1);
	R(i,1,l1) s[i]=strs[i]-'a';
	R(i,1,l2) t[i]=strt[i]-'a';
	init_SAM();
	R(i,1,l2) extend_SAM(t[i]);
	int p=1,plen=0;
	R(i,1,l1) 
	{
		if(!a[p].son[s[i]]) 
		{
			for(;p!=1&&!a[p].son[s[i]];p=a[p].nxt);
			plen=a[p].len;
		}
		if(a[p].son[s[i]]) p=a[p].son[s[i]],plen++;
		slen[i]=plen;
	}
	init_ST();
	int l,r,pos,L,R;

	for(_=read();_;_--)
	{
		L=l=read(),R=r=read();
		pos=r+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(mid-slen[mid]+1>=L) pos=mid,r=mid-1;
			else l=mid+1;
		}
		writeln(max(query(pos,R),pos-L));
	}
}
```



### 两个字符串的最长公共子串

> 给定两个字符串 $S$ 和 $T$，求出最长公共子串，公共子串定义为在 $S$ 和 $T$ 中都作为子串出现过的字符串 $X$。

我们对字符串 $S$ 构造后缀自动机。

我们现在处理字符串 $T$，对于每一个前缀，都在 $S$ 中寻找这个前缀的最长后缀。换句话说，对于每个字符串 $T$ 中的位置，我们想要找到这个位置结束的 $S$ 和 $T$ 的最长公共子串的长度。显然问题的答案就是所有 $l$ 的最大值。

为了达到这一目的，我们使用两个变量，**当前状态**  $v$ 和 **当前长度**  $l$。这两个变量描述当前匹配的部分：它的长度和它们对应的状态。

一开始 $v=t_0$ 且 $l=0$，即，匹配为空串。

现在我们来描述如何添加一个字符 $T_{i}$ 并为其重新计算答案：

- 如果存在一个从 $v$ 到字符 $T_{i}$ 的转移，我们只需要转移并让 $l$ 自增一。
- 如果不存在这样的转移，我们需要缩短当前匹配的部分，这意味着我们需要按照后缀链接进行转移：

$$
v=\operatorname{link}(v)
$$

与此同时，需要缩短当前长度。显然我们需要将 $l$ 赋值为 $\operatorname{len}(v)$，因为经过这个后缀链接后我们到达的状态所对应的最长字符串是一个子串。

- 如果仍然没有使用这一字符的转移，我们继续重复经过后缀链接并减小 $l$，直到我们找到一个转移或到达虚拟状态 $-1$（这意味着字符 $T_{i}$ 根本没有在 $S$ 中出现过，所以我们设置 $v=l=0$）。

这一部分的时间复杂度为 $O(\left|T\right|)$，因为每次移动我们要么可以使 $l$ 增加一，要么可以在后缀链接间移动几次，每次都减小 $l$ 的值。

代码实现：

```cpp
string lcs(const string &S, const string &T) {
  sam_init();
  for (int i = 0; i < S.size(); i++) sam_extend(S[i]);

  int v = 0, l = 0, best = 0, bestpos = 0;
  for (int i = 0; i < T.size(); i++) {
    while (v && !st[v].next.count(T[i])) {
      v = st[v].link;
      l = st[v].length;
    }
    if (st[v].next.count(T[i])) {
      v = st[v].next[T[i]];
      l++;
    }
    if (l > best) {
      best = l;
      bestpos = i;
    }
  }
  return t.substr(bestpos - best + 1, best);
}
```

例题：[SPOJ Longest Common Substring](https://www.spoj.com/problems/LCS/en/)

### 多个字符串间的最长公共子串

> 给定 $k$ 个字符串 $S_i$。我们需要找到它们的最长公共子串，即作为子串出现在每个字符串中的字符串 $X$。

我们将所有的子串连接成一个较长的字符串 $T$，以特殊字符 $D_i$ 分开每个字符串（一个字符对应一个字符串）：

$$
T=S_1+D_1+S_2+D_2+\cdots+S_k+D_k.
$$

然后对字符串 $T$ 构造后缀自动机。

现在我们需要在自动机中找到存在于所有字符串 $S_i$ 中的一个字符串，这可以通过使用添加的特殊字符完成。注意如果 $S_j$ 包含了一个子串，则 SAM 中存在一条从包含字符 $D_j$ 的子串而不包含以其它字符 $D_1,\,\ldots,\,D_{j-1},\,D_{j+1},\,\ldots,\,D_k$ 开始的路径。

因此我们需要计算可达性，即对于自动机中的每个状态和每个字符 $D_i$，是否存在这样的一条路径。这可以容易地通过 DFS 或 BFS 及动态规划计算。之后，问题的答案就是状态 $v$ 的字符串 $\operatorname{longest}(v)$ 中存在所有特殊字符的路径。

例题：[SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)

### 用SAM构建后缀树

一个NB的结论：**反串的SAM的parent树就是后缀树**

感性理解：

parent树有一个性质，父亲是孩子的最长后缀（$end$集合不同）

而把串翻转过来之后，反串的parent树就满足：父亲是孩子的最长前缀($beginpos$不同)

观察压缩后缀树的定义，$bgp$相同的两个串才能被压缩，所以SAM和后缀树其实是有异曲同工之妙的。

另一个构造后缀树的方法将会在后缀树中讲。

这里先讲一些性质。

- 设$lcs(i,j)$为前缀$i,j$的最长公共后缀长度，其等于parent树上`LCA`的值。

例题：[LgP4248 [AHOI2013]差异](https://www.luogu.org/problem/P4248)

可以转化为求两两后缀的$lcp$和。

众所周知这就相当于求后缀树上两两叶节点的$lca$深度总和。

建立后缀树之后，写一个树形dp就可以解决了：

```c++
const int N=555555;
struct node {int len,nxt,son[26],siz;}a[N<<1];
int lst,tn;
char str[N];
int s[N];

int ans;
int n;
vector<int>e[N<<1];

inline void init_SAM(){tn=lst=1;}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p&&!a[p].son[c];p=a[p].nxt)a[p].son[c]=cur;
	if(!p) a[cur].nxt=1;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1) a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}
void dfs(int u)
{
	int tmp=a[u].siz;
	for(int v:e[u]) dfs(v),a[u].siz+=a[v].siz;
	for(int v:e[u]) ans+=1ll*(a[v].siz)*(a[u].siz-a[v].siz)*a[u].len;
	ans+=tmp*(a[u].siz-tmp)*a[u].len;
}
signed main()
{
	init_SAM();
	scanf("%s",str+1);
	n=strlen(str+1);
	R(i,1,n)s[i]=str[i]-'a';
	L(i,1,n)extend_SAM(s[i]);
	int p=1;
	L(i,1,n) p=a[p].son[s[i]],a[p].siz=1;
	R(i,2,tn) e[a[i].nxt].pb(i);
	dfs(1);
	writeln(1ll*n*(n-1)*(n+1)/2-ans);
}
```

题：[[十二省联考2019]字符串问题](https://www.luogu.com.cn/problem/P5284)

不会，先鸽了。

### 线段树合并维护end集合

我们发现parent树上，父节点的end集合恰好是子节点的集合求并（其实这主要是省空间）。

考虑使用线段树合并来维护end集合，来干一些神奇的事。

例题：[CF1037H Security](https://www.luogu.org/problemnew/show/CF1037H)

题意：给出一个文本串$S$，给出若干文本串$T$。

截取$S$的一个子串$S2=S[l\dots r]$，求$S2$的子串中，严格大于$T$的字典序最小的串，如果没有则输出$-1$。

- 先考虑$S2=S$的情况

有一个显然的贪心：

先建立S的SAM，然后让T在S上面跑匹配，假设在$T_p$匹配不上了，那么只要找一个大于当前$T_p$那个字符的最小字符放在串尾即可。如果当前都小于$T_p$那就让上一位找有没有位置大于$T_{p-1}$的，若到源点都没有方案，即无解。

具体时间复杂度为$O(|S|+26\sum|T|)$，其中$26$并不能跑满。

- 再考虑截取限制即$S2=S[l\dots r]$。

如果我们知道$S[l\dots r]$的SAM，,我们就可以套用上述贪心了,但是每次重构复杂度显然不对。

还是要先建立$S$的SAM，我们称包含任意一个$S[l\dots r]$子串的点为"好点"。

那么我们发现，将所有的"不好点"以及相关的边删掉，那么我们就得到了$S[l\dots r]$的SAM。

这玩意虽然不保证点数边数为$O(|s[l\cdots r]|)$，但是能恰好匹配所有的子串（一个合法的自动机）

考虑设计一个函数，能够判定某个点是否为好点，那样的话就可以实现上述贪心操作了。

如何判断呢？我们采用线段树合并来维护每个点的end集合，具体做法就是在perent树上由下而上合并线段树，空间受得住。注意合并的时候不能销毁儿子的树。

（当然用普通平衡树启发式合并也是可以的，不过代码长，复杂度还多个$\log$）

我们只要在线段树上区间查询一下end集合有没有值就好了，区间是$[l+len-1,r]$。这里的$len$是目前字符串的长度。那么复杂度就是$O(|S|\log n+26\sum|T|\log n)$。

```c++
const int N=4e5+10;
struct node {int len,nxt,son[26];}a[N<<1];
int lst,tn;
int edp[N<<1];

int n,q;
char strs[N],strt[N];
int s[N],t[N];
int Rt[N<<1];
int Ls[N<<6],Rs[N<<6];
int tot_seg;
int ql,qr,qlen;
int val[N<<6];

vector<int>e[N<<1];

inline void init_SAM(){tn=lst=1;}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p&&!a[p].son[c];p=a[p].nxt)a[p].son[c]=cur;
	if(!p) a[cur].nxt=1;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1)a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}
int mer_ge(int x,int y)
{
	if(!x||!y) return x^y;
	int pos=++tot_seg;
	Ls[pos]=mer_ge(Ls[x],Ls[y]);
	Rs[pos]=mer_ge(Rs[x],Rs[y]);
	return pos;
}
void modify(int pos,int l,int r,int &x)
{
	if(!x) x=++tot_seg;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) modify(pos,l,mid,Ls[x]);
	else modify(pos,mid+1,r,Rs[x]);
	//printf("x:%lld ls:%lld rs:%lld\n",x,Ls[x],Rs[x]);
}
int query(int L,int R,int l,int r,int x)
{
	if(!x) return 0;
	if(L<=l&&r<=R) return 1;
	int mid=(l+r)>>1,ret=0;	
	//printf("L:%lld R:%lld l:%lld r:%lld x:%lld\n",L,R,l,r,x);
	if(L<=mid) ret|=query(L,R,l,mid,Ls[x]);
	if(mid<R) ret|=query(L,R,mid+1,r,Rs[x]);
	return ret;
}

void dfs(int u)
{
	if(edp[u]) modify(edp[u],1,n,Rt[u]);
	for(int v:e[u]) dfs(v),Rt[u]=mer_ge(Rt[u],Rt[v]);
}
int sp[N];

signed main()
{
	scanf("%s",strs+1);q=read();
	n=strlen(strs+1);R(i,1,n) s[i]=strs[i]-'a';
	init_SAM();
	R(i,1,n) extend_SAM(s[i]);
	int p=1;R(i,1,n)p=a[p].son[s[i]],edp[p]=i/*,printf("p:%lld edp:%lld\n",p,edp[p])*/;
	R(i,2,tn) e[a[i].nxt].pb(i);
	dfs(1);
	//R(i,1,10) printf("rt:%lld\n",Rt[i]);
	int qlen;
	sp[0]=1;
	while(q--)
	{
		ql=read(),qr=read();scanf("%s",strt+1);
		qlen=strlen(strt+1);
		p=1;R(i,1,qlen) t[i]=strt[i]-'a';
		int v,lim=qlen;
		R(i,1,qlen)
		{
			v=a[p].son[t[i]];
			if(v&&query(ql+i-1,qr,1,n,Rt[v])) p=a[p].son[t[i]],sp[i]=p;
			else {lim=i-1;break;}
		}
		//printf("lim:%d\n",lim);
		//printf("st:");for(int i=0;i<=qlen;i++) printf("%d ",sp[i]);
		//puts(""); 
		int ok=0;
		L(i,0,lim)
		{
			if(ok) break;
			R(j,(i<qlen)?t[i+1]+1:0,25) 
			{
				v=a[sp[i]].son[j];
				if(query(ql+i,qr,1,n,Rt[v])) 
				{
					//printf("%lld\n",i);
					R(k,1,i) putchar(strt[k]);
					putchar(j+'a'),puts("");
					ok=1;break;
				}
			}
		}
		if(!ok) puts("-1");
	}
}
/*
aabbababababasbbbbabababababababbababaababbabababababababbabbbbbbbbaaaaaaaaabbbabababababbbbabbababbababa
10
1 82 abbbababababababa

*/
```

- [P4094 [HEOI2016/TJOI2016]字符串](https://www.luogu.com.cn/problem/P4094)

先把原串倒过来，现在问题变成了$[a,b]$的子串在$[c,d]$中匹配的最长后缀。

考虑二分一个$len$，就变成了$O(\log n)$个$[d-len+1,d]$在$[a+len-1,b]$中的存在性问题。

令$c'=d+len-1,a'=a+len-1$。

建出SAM，跑一个线段树合并求出每一个点的edp。

然后定位包含子串$[c',d']$的点具体方法是先找出前缀$d$的对应结束点，然后看`len`在parent树上倍增。

定位到之后看一看有没有edp在给出的$[a',b]$内，线段树上一个区间查询即可。

时间复杂度$O(n\log^2 n)$

```c++
const int N=2e5+10;

int n,m;
struct node {int len,nxt,son[26];}a[N<<1];
int lst,tn,edp[N<<1];

inline void init_SAM(){tn=lst=1;}
void extend_SAM(int c)
{
    int cur=++tn,p=lst;
    a[cur].len=a[p].len+1;
    for(;p&&!a[p].son[c];p=a[p].nxt)a[p].son[c]=cur;
    if(!p) a[cur].nxt=1;
    else
    {
        int v=a[p].son[c];
        if(a[v].len==a[p].len+1)a[cur].nxt=v;
        else
        {
            int x=++tn;a[x]=a[v];
            a[x].len=a[p].len+1;
            for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
            a[cur].nxt=a[v].nxt=x;
        }
    }
    lst=cur;
}
int Rt[N<<1],Ls[N<<6],Rs[N<<6];
int tot_seg;
char strs[N],strt[N];
int s[N],t[N];
vector<int>e[N<<1];
int sp[N];
int st[N<<1][23];

int mer(int x,int y)
{
    if(!x||!y) return x^y;
    int pos=++tot_seg;
    Ls[pos]=mer(Ls[x],Ls[y]);
    Rs[pos]=mer(Rs[x],Rs[y]);
    return pos;
}
void modify(int pos,int l,int r,int &x)
{
    if(!x) x=++tot_seg;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) modify(pos,l,mid,Ls[x]);
    else modify(pos,mid+1,r,Rs[x]);
}
int query(int L,int R,int l,int r,int x)
{
    if(!x) return 0;
    if(L<=l&&r<=R) return 1;
    int mid=(l+r)>>1,ret=0;
    if(L<=mid) ret|=query(L,R,l,mid,Ls[x]);
    if(mid<R) ret|=query(L,R,mid+1,r,Rs[x]);
    return ret;
}
void dfs(int u)
{
    if(edp[u]) modify(edp[u],1,n,Rt[u]);
    for(int v:e[u]) dfs(v),Rt[u]=mer(Rt[u],Rt[v]);
}
inline int check(int lim,int l,int r,int x)
{
    L(i,0,20) if(a[st[x][i]].len>=lim&&st[x][i]) x=st[x][i];return query(l+lim-1,r,1,n,Rt[x]);
}
signed main()
{
    n=read(),m=read();
    scanf("%s",strs+1);
    reverse(strs+1,strs+n+1);
    R(i,1,n) s[i]=strs[i]-'a';
    init_SAM();R(i,1,n) extend_SAM(s[i]),sp[i]=lst;
    int p=1;R(i,1,n)p=a[p].son[s[i]],edp[p]=i;
    R(i,2,tn) e[a[i].nxt].pb(i);
    dfs(1);
    R(i,1,tn) st[i][0]=a[i].nxt;
    R(j,1,20) R(i,1,tn) st[i][j]=st[st[i][j-1]][j-1];
    int qa,qb,qc,qd,l,r,mid,best;
    while(m--)
    {
        qa=n-read()+1,qb=n-read()+1,qc=n-read()+1,qd=n-read()+1;
        l=0,r=min(qa-qb+1,qc-qd+1);best=0;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid,qb,qa,sp[qc]))l=mid+1,best=mid;
            else r=mid-1;
        }
        writeln(best);
    }
}
```

- [SP687 REPEATS - Repeats](https://www.luogu.com.cn/problem/SP687)

不会，先鸽掉了。

### SAM上树分治

当你要统计前缀**对子**之间的贡献时,你会发现往往与**lcs**最长公共后缀) 有关。

而这又能转化成关于parent树上`LCA`的一些信息，那么我们就可以使用有根树分治来统计。

某些时候也可以直接树剖。

- [[DS记录\]Loj#6198. 谢特](https://www.luogu.com.cn/blog/command-block/ds-ji-lu-6198-xie-te) (启发式合并01Trie)
- [[DS记录\]P5161 WD与数列](https://www.luogu.com.cn/blog/command-block/ds-ji-lu-p5161-wd-yu-shuo-lie) (启发式合并线段树)
- [[DS记录\]P4482 [BJWC2018]Border 的四种求法](https://www.luogu.com.cn/blog/command-block/ds-ji-lu-p4482-bjwc2018border-di-si-zhong-qiu-fa) (重链剖分)



## 例题

- [HihoCoder #1441 : 后缀自动机一·基本概念](http://hihocoder.com/problemset/problem/1441)
- [【模板】后缀自动机](https://www.luogu.com.cn/problem/P3804)
- [SDOI2016 生成魔咒](https://loj.ac/problem/2033)
- [SPOJ - SUBLEX](https://www.spoj.com/problems/SUBLEX/)
- [TJOI2015 弦论](https://loj.ac/problem/2102)
- [SPOJ Longest Common Substring](https://www.spoj.com/problems/LCS/en/)
- [SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)
- [Codeforces 1037H Security](https://codeforces.com/problemset/problem/1037/H)
- [Codeforces 666E Forensic Examination](https://codeforces.com/problemset/problem/666/E)
- [HDu4416 Good Article Good sentence](http://acm.hdu.edu.cn/showproblem.php?pid=4416)
- [HDu4436 str2int](http://acm.hdu.edu.cn/showproblem.php?pid=4436)
- [HDu6583 Typewriter](http://acm.hdu.edu.cn/showproblem.php?pid=6583)
- [Codeforces 235C Cyclical Quest](https://codeforces.com/problemset/problem/235/C)
- [CTSC2012 熟悉的文章](https://www.luogu.com.cn/problem/P4022)
- [NOI2018 你的名字](https://uoj.ac/problem/395)

### 参考资料

[commond_block](https://www.luogu.com.cn/blog/command-block/hou-zhui-zi-dong-ji-xue-xi-bi-ji)

[oi-wiki](https://oi-wiki.org/string/sam/#_5)

[wallace](https://www.cnblogs.com/-Wallace-/p/sam.html)

[ouuan](https://ouuan.github.io/post/%E5%90%8E%E7%BC%80%E8%87%AA%E5%8A%A8%E6%9C%BAsam%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/)

某课件

