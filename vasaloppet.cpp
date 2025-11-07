#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t, s;
    cin >> n >> t >> s;
    vector<pair<int, int>> ad_breaks(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> ad_breaks[i].first >> ad_breaks[i].second;
    }

    vector<int> potential_positions;
    potential_positions.emplace_back(0);

    for (auto [ad_start, ad_end] : ad_breaks)
    {
        potential_positions.emplace_back(ad_start);
        if (ad_end >= s)
        {
            potential_positions.emplace_back(ad_end - s);
        }
    }
    sort(potential_positions.begin(), potential_positions.end()); // Note that because the ad breaks are already sorted and disjoint this requires N swaps and should thus be near-linear/linear

    int potential_start = potential_positions[0];
    int start = potential_start;
    int end = min(potential_start + s, t);

    int start_idx = 0;
    while (start_idx < n && ad_breaks[start_idx].second <= start)
        ++start_idx;
    int temp = start_idx;

    int end_idx = 0;

    int ad_time = 0;
    while (temp < n && ad_breaks[temp].first < end)
    {
        int overlap_l = max(start, ad_breaks[temp].first);
        int overlap_r = min(end, ad_breaks[temp].second);
        ad_time += overlap_r - overlap_l;

        if (ad_breaks[temp].second <= end)
        {
            ++temp;
        }
        else
        {
            break;
        }
    }

    end_idx = temp;
    int max_ad_time = ad_time;

    int positions_size = potential_positions.size();
    for (int i = 1; i < positions_size; ++i)
    {
        int next_start = potential_positions[i];
        int dx = next_start - potential_start;
        {
            int seg_start = start;
            int seg_end = start + dx;

            while (start_idx < n && ad_breaks[start_idx].second <= seg_start)
            {
                ++start_idx;
            }

            int p = start_idx;
            while (p < n && ad_breaks[p].first < seg_end)
            {
                int overlap_start = max(seg_start, ad_breaks[p].first);
                int overlap_end = min(seg_end, ad_breaks[p].second);
                if (overlap_end > overlap_start)
                {
                    ad_time -= (overlap_end - overlap_start);
                }

                if (ad_breaks[p].second <= seg_end)
                {
                    ++p;
                }
                else
                {
                    break;
                }
            }
            start_idx = p;
        }

        potential_start = next_start;
        start += dx;
        end = min(end + dx, t);

        {
            int seg_start = end - dx;
            int seg_end = end;

            while (end_idx < n && ad_breaks[end_idx].second <= seg_start)
            {
                ++end_idx;
            }

            int q = end_idx;
            while (q < n && ad_breaks[q].first < seg_end)
            {
                int add_l = max(seg_start, ad_breaks[q].first);
                int add_r = min(seg_end, ad_breaks[q].second);
                if (add_r > add_l)
                {
                    ad_time += (add_r - add_l);
                }

                if (ad_breaks[q].second <= seg_end)
                {
                    ++q;
                }
                else
                {
                    break;
                }
            }
            end_idx = q;
        }

        max_ad_time = max(max_ad_time, ad_time);
    }

    cout << (s - max_ad_time) << "\n";
    return 0;
}
