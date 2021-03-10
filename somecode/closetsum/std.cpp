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
        // ����
        for (int i = 0; i < n; i++)
        {
            cin >> r[i];
            // ������Ĺ�����˳��ö�ٳ�����a[i]+a[j]
            for (int j = 0; j < i; j++)
                a[cnt++] = r[i] + r[j];
        }
        // ����
        sort(a, a + cnt);
        cin >> m;
        while (m--)
        {
            cin >> x;
            //cout << "Closest sum to " << x << " is ";
            // ����ÿ��ѯ�ʣ����ֲ��ҵ�һ�����ڵ���������
            int res = lower_bound(a, a + cnt, x) - a;
            // �Ƚϵ�һ�����ڵ��������������һ��С���������ĸ����ӽ�
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
