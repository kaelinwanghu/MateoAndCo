#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, t, s;
    cin >> n >> t >> s;
    vector<pair<int, int>> ad_breaks(n);
    int start_time, end_time;
    int skipped_time = 0, max_skipped_time = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> start_time >> end_time;
        ad_breaks[i] = {start_time, end_time};
    }
    int current_idx = 0, start = ad_breaks[0].first;

    while (current_idx < n)
    {
        int ad_break_start = ad_breaks[current_idx].first;
        int ad_break_end = ad_breaks[current_idx].second;
        int ad_break_time = ad_break_end - ad_break_start;
        cerr << "current skipped time: " << skipped_time << "\n";
        if (ad_break_start - start >= s)
        {
            max_skipped_time = max(max_skipped_time, skipped_time);
            if (current_idx != 0)
            {
                skipped_time -= min(ad_break_end - ad_break_start, s);
            }
            current_idx++;
            if (current_idx < n - 1)
                start = ad_breaks[current_idx].first;
        }
        else if (ad_break_end - start >= s)
        {
            skipped_time += min(ad_break_time, s);
            max_skipped_time = max(max_skipped_time, skipped_time);
            if (current_idx != 0)
            {
                skipped_time -= min((ad_break_end - ad_break_start), s);
            }
            current_idx++;
            if (current_idx < n - 1)
                start = ad_breaks[current_idx].first;
        }
        else
        {
            skipped_time += ad_break_time;
            current_idx++;
        }
    }

    reverse(ad_breaks.begin(), ad_breaks.end());
    for (int i = 0; i < n; ++i)
    {
        ad_breaks[i] = {t - ad_breaks[i].second, t - ad_breaks[i].first};
    }

    current_idx = 0;
    start = ad_breaks[0].first;
    skipped_time = 0;
    while (current_idx < n)
    {
        int ad_break_start = ad_breaks[current_idx].first;
        int ad_break_end = ad_breaks[current_idx].second;
        int ad_break_time = ad_break_end - ad_break_start;
        cerr << "current skipped time: " << skipped_time << "\n";
        if (ad_break_start - start >= s)
        {
            max_skipped_time = max(max_skipped_time, skipped_time);
            if (current_idx != 0)
            {
                skipped_time -= min(ad_break_end - ad_break_start, s);
            }
            current_idx++;
            if (current_idx < n - 1)
                start = ad_breaks[current_idx].first;
        }
        else if (ad_break_end - start >= s)
        {
            skipped_time += min(ad_break_time, s);
            max_skipped_time = max(max_skipped_time, skipped_time);
            if (current_idx != 0)
            {
                skipped_time -= min((ad_break_end - ad_break_start), s);
            }
            current_idx++;
            if (current_idx < n - 1)
                start = ad_breaks[current_idx].first;
        }
        else
        {
            skipped_time += ad_break_time;
            current_idx++;
        }
    }

    cout << (s - max_skipped_time) << "\n";
}
