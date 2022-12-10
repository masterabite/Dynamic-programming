#include <iostream>
#include <vector>

using namespace std;

int a[100];
int n, sum = 0;

struct elem {
    bool exist = false;
    bool used[100];
} dp[10000];

int main() {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }

    if ((sum % 2)) {
        cout << "NO\n";
        return 0;
    }

    dp[0].exist = true;
    for (int i = 0; i <= sum / 2; ++i) {
        if (dp[i].exist) {
            for (int j = 0; j < n; ++j) {
                if (!dp[i].used[j] && !dp[i+a[j]].exist) {
                    int next_i = i + a[j];

                    dp[next_i].exist = true;
                    for (int k = 0; k < n; ++k) {
                        if (dp[i].used[k]) {
                            dp[next_i].used[k] = true;
                        }
                    }
                    dp[next_i].used[j] = true;
                }
            }
        }
    }

    cout << (dp[sum / 2].exist ? "YES" : "NO");
    return 0;
}
