/*
  даны количество слитков n, и вес, максимально вместимый в рюкзак
  далее вводятся n весов, каждый слиток можно положить один раз.
  программа выводит максимальный вес, который можно набрать в рюкзак
*/


#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 301;
const int MAXR = 100001;

int n, ans, a[MAXN], m, x;
bool dp[MAXR];

int main()
{

    cin >> n >> m;

    dp[0] = true;

    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        for (int j = m - x; j >= 0; --j)
            if (dp[j])
                dp[j + x] = true;
    }

    for (ans = m; !dp[ans]; --ans);

    cout << ans;

    return 0;
}
