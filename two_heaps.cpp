/*
  дано множество камней с соответствующими весами.
  программа находит минимальную разность весов двух 
  куч, на которые можно разбить множество камней
*/

#include <iostream>

using namespace std;

int a[20];
int n;

void rec(int* a, int i, int n, int current_sum, int& answer, int& all_sum) {
    answer = min(answer, abs(all_sum - 2*current_sum));
    if (i == n) return;
    rec(a, i + 1, n, current_sum + a[i], answer, all_sum);
    rec(a, i + 1, n, current_sum, answer, all_sum);
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    int answer = sum;
    rec(a, 0, n, 0, answer, sum);
    cout << answer << '\n';
    return 0;
}
