
快速取模

<!--more-->

代码出自 [KATCL](https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h) 。

```c++
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

int main() {
    int M = 1000000007; F = FastMod(M);
    ull x = 10ULL*M+3; 
    cout << x << " " << F.reduce(x) << "\n"; // 10000000073 3
}
```

使用方法$:$

假设当前程序中需要取模的数为$p$,那么就在 `main` 函数开头处调用 `F = FastMod(p);`.

计算$a\bmod p$的时候调用 `F.reduce(a);`， 返回值就是$a\bmod p$的值。