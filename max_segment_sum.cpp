/*
  нахождение отрезка с максимальной суммой
*/
#include <iostream>

using namespace std;

long long max_sum;
int max_l, max_r;
int a[100000];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    max_sum = a[0];
    max_l = 0;
    max_r = 0;

    int sum = 0, l = 0, r = 0;

    for (int i = 0; i < n; ++i) {
        sum += a[i];
        if (sum > max_sum) {
            r = i;
            max_sum = sum;
            max_l = l;
            max_r = r;
        }
        if (sum < 0) {
            l = i + 1;
            sum = 0;
        }
    }

    cout << max_l+1 << " " << max_r+1 << " " << max_sum << '\n';
    
    return 0;
}
