
<!--more-->

## 强连通分量(scc)

在有向图$G$中，若两个顶点$u,v$之间能够互相到达，则称$u,v$是强连通的。若有向图$G$的每两个顶点都强连通，则$G$就是一个强连通图。

有向图的极大强连通子图，称作强连通分量。

## 强连通缩点

将一个图中的每一个强连通分量都缩成一个点的过程，称为强连通缩点。容易发现。缩点后的图一定是个DAG。

强连通缩点可以由Kosaraju算法或者Tarjan算法（似乎还有一种）

下面稍微讲一下Kosaraju算法

### Kosaraju

![Picture1.png](https://i.loli.net/2021/04/17/k7Jidwv21g4MqyU.png)

先跑一遍，记录它的posorder，也就是它的返回顺序。

如对于上面这张图从12开始dfs，它的posorder就是$1,2,\ldots ,12$

以及在DAG中，posorder是拓扑序的反序。

在记录这个的posorder后，将这个图的边反向。

![Picture2.png](https://i.loli.net/2021/04/17/6JetWY47iaAwhkH.png)

从最后一个点开始(还是12)在反向图上跑一遍dfs，然后每一次dfs就访问一些点，可以发现这一些点就是一个强连通分量。

大概是因为posorder是DAG的拓扑序列的逆序，将原图的边反向之后，所以最终第二遍dfs的顺序其实就是缩点之后DAG的拓扑序。

![Picture3.png](https://i.loli.net/2021/04/17/bWnXtL2xo3FZAYm.png)

### 例题1

https://codeforces.ml/contest/949/problem/C

阅读理解题

题意 

$n$个点，每个点$i$有一个值$a_i$。$m$个条件，每个条件有2个点$x,y$且$a_x\neq a_y$。选择最少的$k$个点，使其值加$1$后，$m$个条件仍成立。

solution

考虑如果有一个人选了两个点$x,y$，且$(a_x+1)\bmod h=a_y$，那么就连一条从$x\to y$的有向边。表示如果选了$x$，就必须选$y$。然后将得到的图强连通缩点，容易发现一定是选最小的且出度为0的块。因为如果选了一个出度不为$0$的点，之后还要将其他出度为0的点选上，由于是DAG一定有出度为0的点