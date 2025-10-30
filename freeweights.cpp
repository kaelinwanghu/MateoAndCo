#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    int n;
    cin >> n;
    vector<int> weights(2 * n + 2);
    int max = INT32_MIN;
    for (int i = 0; i < n; ++ i)
    {
        cin >> weights[i];
        if (weights[i] > max)
        {
            max = weights[i];
        }
    }
    weights[n] = INT32_MAX;
    weights[n + 1] = INT32_MAX;
    for (int i = n + 2; i < 2 * n + 2; ++i)
    {
        cin >> weights[i];
        if (weights[i] > max)
        {
            max = weights[i];
        }
    }
    int mini = 0;
    while (mini < max)
    {
        int test_weight = (mini + max) / 2;
        bool can_move = true;
        int cannot_move_weight = INT32_MIN;
        bool works = true;
        for (int i = 0; i < 2 * n + 2; ++i)
        {
            if (!can_move)
            {
                if (test_weight < weights[i])
                {
                    if (cannot_move_weight == weights[i])
                    {
                        can_move = true;
                    }
                    else
                    {
                        works = false;
                        break;
                    }
                }
            }
            else if (test_weight < weights[i])
            {
                can_move = false;
                cannot_move_weight = weights[i];
            }
        }
        if (works)
        {
            max = test_weight;
        }
        else
        {
            mini = test_weight + 1;
        }
    }
    cout << mini << "\n";
    return 0;
}