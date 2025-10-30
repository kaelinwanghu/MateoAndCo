#include <bits/stdc++.h>
using namespace std;

int main(void)
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, index1, index2;
    string symbol1, symbol2;
    cin >> n >> k;
    vector<pair<string, bool>> known(n + 1, pair<string, bool>("", false));
    unordered_map<string, pair<int, int>> matches;
    matches.reserve(n);
    int can_match = 0;
    int half_matches = 0;
    int known_matches = 0;
    for (int i = 0; i < k; ++i)
    {
        cin >> index1 >> index2 >> symbol1 >> symbol2;
        if (symbol1 == symbol2)
        {
            known[index1].second = true;
            known[index2].second = true;
            known_matches += 2;
        }
        known[index1].first = symbol1;
        known[index2].first = symbol2;
    }
    for (int i = 1; i < n + 1; ++i)
    {
        if (known[i].first == "")
        {
            continue;
        }
        if (!known[i].second && matches.find(known[i].first) == matches.end())
        {
            matches[known[i].first].first = i;
            ++half_matches;
            matches[known[i].first].second = -1;
        }
        else if (!known[i].second && matches.find(known[i].first) != matches.end())
        {
            matches[known[i].first].second = i;
            --half_matches;
            ++can_match;
        }
    }
    if (can_match * 2 + known_matches >= n - 2)
    {

        cout << can_match + ((can_match * 2 + known_matches == n) ? 0 : 1) << "\n";
    }
    else if (n - can_match * 2 - known_matches - half_matches <= half_matches)
    {
        cout << can_match + half_matches << "\n";
    }
    else
    {
        cout << can_match << "\n";
    }
    return 0;
}