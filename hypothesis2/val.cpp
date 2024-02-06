#include <bits/stdc++.h>
using namespace std;
int main() {
    vector < pair <double, int> > v;
    double a;
    int b;
    while (cin >> a >> b) v.push_back({a, b});
    sort(v.begin(), v.end());
    int _max = 0;
    double res = 0;
    for (auto [a, b] : v) {
        _max = max(_max, b);
        res = max(res, 1. * _max / b);
    }
    printf("%.3lf\n", res);
}