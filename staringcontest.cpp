#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<tuple<int, int, int>> estimated;
    set<int> known;
    vector<int> values(n + 1, -1);

    int next_pos = 2;
    int response;
    
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);

    mt19937 rng(0);
    shuffle(order.begin(), order.end(), rng);

    int first_idx = order[0];
    int second_idx = order[1];
    cout << "? " << first_idx << " " << second_idx << endl;
    cin >> response;
    estimated.emplace_back(first_idx, second_idx, response);


    while ((int)known.size() < n - 2)
    {
        auto [prev_first_idx, prev_second_idx, estimate] = estimated.back();
        int next_new_guess = order[next_pos];
        cout << "? " << prev_second_idx << " " << next_new_guess << endl;
        cin >> response;
        if (response > estimate)
        {
            known.emplace(prev_first_idx);
            values[prev_first_idx] = estimate;
            estimated.emplace_back(prev_second_idx, next_new_guess, response);
        }
        else if (response < estimate)
        {
            known.emplace(next_new_guess);
            values[next_new_guess] = response;
            estimated.emplace_back(prev_first_idx, prev_second_idx, estimate);
        }
        else
        {   
            known.emplace(prev_second_idx);
            values[prev_second_idx] = response;
            cout << "? " << prev_first_idx << " " << next_new_guess << endl;
            cin >> response;
            estimated.emplace_back(prev_first_idx, next_new_guess, response);
        }
        next_pos++;
    }
    auto [last_idx_one, last_idx_two, estimate] = estimated.back();
    values[last_idx_one] = estimate;
    values[last_idx_two] = estimate;

    cout << "! ";
    for (int i = 1; i <= n; ++i)
    {
        cout << values[i];
        if (i != n) cout << " ";
    }
    cout << endl;
    return 0;
}