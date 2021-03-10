#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000
using namespace std;
char ch1[MAXN], ch2[MAXN];
int num1[MAXN], num2[MAXN], len1, len2, len, ans[MAXN];
int main() {
    gets(ch1);
    gets(ch2);
    len1 = strlen(ch1);
    len2 = strlen(ch2);
    for (int i = 0, j = len1; i < len1, j >= 1; i++, j--) {
        num1[j] = int(ch1[i]) - 48;
    }
    for (int i = 0, j = len2; i < len2, j >= 1; i++, j--) {
        num2[j] = int(ch2[i]) - 48;
    }
    if (num1[1] == 0 && num2[1] == 0) {
        cout << 0;
        return 0;
    }
    if (len1 == 1 && len2 == 1) {
        cout << num1[1] + num2[1];
        return 0;
    }
    len = max(len1, len2);
    if (len1 > len2) {
        for (int i = len2 + 1; i <= len1; i++) num2[i] = 0;
    }
    if (len2 > len1) {
        for (int i = len1 + 1; i <= len2; i++) num1[i] = 0;
    }
    for (int i = 1; i <= len; i++) {
        ans[i] += num1[i] + num2[i];
        if (ans[i] >= 10) {
            ans[i + 1]++;
            ans[i] %= 10;
        }
    }
    while (ans[len + 1] == 0) {
        len--;
    }
    for (int i = len + 1; i >= 1; i--) {
        if (ans[i] >= 0 && ans[i] <= 9)
            cout << ans[i];
        else
            return 0;
    }
    return 0;
}
