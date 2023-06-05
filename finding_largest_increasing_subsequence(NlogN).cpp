#include <iostream>

using namespace std;


int a[100000], d[100000];
const int INF = 1000000000;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        d[i + 1] = INF;
    } d[0] = -INF;
   
    for (int i = 0; i < n; ++i) {
        int l = 0;
        int r = n;
        int mid;
        while (l < r-1) {
            mid = (l + r) / 2;
            (d[mid] > a[i] ? r = mid : l = mid); 
            
        }
        if (a[i] > d[l] && a[i] < d[l + 1]) {
            d[l + 1] = a[i];
        }
    }


    for (int i = n; i >= 0; --i) {
        if (d[i] != INF) {
            cout << i;
            break;
        }
    }

    return 0;
}
