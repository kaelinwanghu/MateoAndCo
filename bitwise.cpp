#include <bits/stdc++.h>
using namespace std;

bool can(int n, int k, int x, vector<int> &numbers)
{
    if (x == 0) return false;
    vector<int> start_positions;
    for (int b = 0; b <= 30; ++b)
    {
        int where = -1;
        if (x & (1 << b))
        {
            for (int i = 0; i < n; ++i)
            {
                if (numbers[i] & (1 << b))
                {
                    where = i;
                    break;
                }
            }
            if (where == -1)
            {
                return false;
            }
            else
            {
                start_positions.emplace_back((where + 1) % n);
            }
        }
    }
    sort(start_positions.begin(), start_positions.end());
    start_positions.erase(unique(start_positions.begin(), start_positions.end()), start_positions.end());
    int start_positions_size = start_positions.size();
    for (int i = 0; i < start_positions_size; ++i)
    {
        int starting_point = start_positions[i];
        int current_sum = numbers[starting_point];
        int index = starting_point + 1;
        if (index == n)
        {
            index = 0;
        }
        int num_groups = 0;
        while (index != starting_point)
        {
            if ((current_sum & x) == x)
            {
                ++num_groups;
                current_sum = 0;
            }
            current_sum |= numbers[index];
            ++index;
            if (index == n)
            {
                index = 0;
            }
        }
        if ((current_sum & x) == x)
        {
            num_groups += 1;
        }
        if (num_groups >= k)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> numbers[i];
    }
    int bit = 1;
    int answer = 0;
    for (int i = 30; i >= 0; --i)
    {
        int actual_bit = bit << i;
        if (can(n, k, answer | actual_bit, numbers))
        {
            answer |= actual_bit;
        }
    }
    cout << answer << "\n";
}
