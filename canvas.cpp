#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n; 
    cin >> n;
    while (n--)
    {
        int64_t n;
        int64_t c;
        cin >> n;
        priority_queue<int64_t, vector<int64_t>, greater<int64_t>> pq;
        for (int64_t i = 0; i < n; ++i)
        {
            cin >> c;
            pq.emplace(c);
        }
        int64_t cost = 0;
        while (pq.size() > 1)
        {
            int64_t a = pq.top(); pq.pop();
            int64_t b = pq.top(); pq.pop();
            int64_t s = a + b;
            cost += s;
            pq.emplace(s);
        }
        cout << cost << "\n";
    }
    return 0;
}
