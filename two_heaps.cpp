#include <iostream>

using namespace std;

int a[20];
int n, answer, all_sum;

void rec(int i, int current_sum) {
    answer = min(answer, abs(all_sum - 2 * current_sum));
    if (i == n) return;
    rec(i + 1, current_sum + a[i]);
    rec(i + 1, current_sum);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        all_sum += a[i];
    }
    answer = all_sum;
    rec(0, 0);
    cout << answer << '\n';
    return 0;
}
