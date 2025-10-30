#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    vector<int> count(10, 0);
    for (char c : s)
    {
        count[c - '0']++;
    }

    for (int d = 1; d < 10; ++d)
    {
        if (count[d] == 0)
        {
            cout << d << "\n";
            return 0;
        }
    }

    int z_count = count[0];
    int min = count[1];
    int best_digit = 1;
    for (int d = 2; d <= 9; ++d)
    {
        if (count[d] < min || (count[d] == min && d < best_digit))
        {
            min = count[d];
            best_digit = d;
        }
    }

    if (z_count < min)
    {
        cout << '1';
        for (int i = 0; i < z_count + 1; ++i)
        {
            cout << '0';
        }
    }
    else
    {
        for (int i = 0; i < min + 1; ++i)
        {
            cout << best_digit;
        }
    }
    cout << "\n";
    return 0;
}