#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ms = multiset<ll>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    cin >> n >> k;

    ms bags{};
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        bags.insert(a);
    }

    for (ll bag : bags) {
        if (bags.contains(k - bag)) {
            if (k == 2 * bag && bags.count(bag) == 1) continue;
            cout << bag << ' ' << k - bag << '\n';
            return 0;
        }
    }
    cout << "Neibb\n";
}