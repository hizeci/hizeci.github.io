#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 10005
int T;
int n, r[MAXN], m, x;
int a[MAXN * MAXN];
int main()
{
    while (cin >> n && n)
    {
        int cnt = 0;
        //cout << "Case " << ++T << ":" << endl;
        // 输入
        for (int i = 0; i < n; i++)
        {
            cin >> r[i];
            // 在输入的过程中顺便枚举出所有a[i]+a[j]
            for (int j = 0; j < i; j++)
                a[cnt++] = r[i] + r[j];
        }
        // 排序
        sort(a, a + cnt);
        cin >> m;
        while (m--)
        {
            cin >> x;
            //cout << "Closest sum to " << x << " is ";
            // 对于每次询问，二分查找第一个大于等于它的数
            int res = lower_bound(a, a + cnt, x) - a;
            // 比较第一个大于等于它的数与最后一个小于它的数哪个更接近
            if (res == 0 || (res < cnt && a[res] - x < x - a[res - 1]))
                cout << a[res];
            else
                cout << a[res - 1];
            //cout << "." << endl;
            cout<<endl;
        } 
    }
	return 0;
}
