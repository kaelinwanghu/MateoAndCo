#include <bits/stdc++.h>
using namespace std;

struct city
{
    int ballot_boxes;
    int population;
    double ratio;
    int id;
    city() : ballot_boxes(0), population(0), ratio(0.0), id(0) {}
    city(int _bb, int _p, double _r, int _id) : ballot_boxes(_bb), population(_p), ratio(_r), id(_id) {}
};

class comp
{
    public:
    bool operator()(city& a, city& b) const
    {
        return a.ratio < b.ratio;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, b;
    cin >> n >> b;
    while (n != -1 && b != -1)
    {
        b -= n;
        vector<double> ratio(n);
        priority_queue<city, vector<city>, comp> pq;
        for (int i = 0; i < n; ++i)
        {
            cin >> ratio[i];
            pq.emplace(1, ratio[i], ratio[i], i);
        }
        for (int i = 0; i < b; ++i)
        {
            city c = pq.top();
            // cout << "city c: " << c.id << " with ratio: " << c.ratio << " and ballet boxes: " << c.ballot_boxes  << " and pop " << c.population << "\n";
            pq.pop();
            if (ratio[c.id] != c.ratio)
            {
                continue;
            }
            c.ballot_boxes += 1;
            c.ratio = static_cast<double>(c.population) / c.ballot_boxes;
            // cout << "new city c: " << c.id << " with ratio: " << c.ratio << " and ballet boxes: " << c.ballot_boxes  << " and pop " << c.population << "\n";
            pq.push(c);
            ratio[c.id] = c.ratio;
        }
        int final_ratio = ceil(pq.top().ratio);
        cout << final_ratio << "\n";

        cin >> n >> b;
    }
    return 0;
}