#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> count(3, 0);
    string s;
    cin >> s;
    int s_size = s.size();
    int total = 0;
    int min = INT32_MAX;
    for (int i = 0; i < s_size; ++i)
    {
        char c = s[i];
        if (c == 'T')
        {
            count[0]++;
        }
        else if (c == 'G')
        {
            count[1]++;
        }
        else
        {
            count[2]++;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        if (count[i] < min)
        {
            min = count[i];
        }
        total += count[i] * count[i];
    }
    cout << total + 7 * min << "\n";
    return 0;
}