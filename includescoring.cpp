#include <bits/stdc++.h>
using namespace std;

struct contestant
{
    int problems_solved;
    int time_penalty;
    int submission_time;
    int extra_points;
    int position;
};

bool comp(const contestant& a, const contestant& b)
{
    if (a.problems_solved != b.problems_solved)
    {
        return a.problems_solved > b.problems_solved;
    }
    else if (a.time_penalty != b.time_penalty)
    {
        return a.time_penalty < b.time_penalty;
    }
    return a.submission_time < b.submission_time;
}

int points_given[] = {100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, pos = 0;
    cin >> n;
    vector<contestant> ranking(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> ranking[i].problems_solved >> ranking[i].time_penalty >> ranking[i].submission_time >> ranking[i].extra_points;
        ranking[i].position = pos++;
    }
    int true_pos = 0;
    vector<vector<contestant>> tiebreak(n);
    vector<int> points(n);
    sort(ranking.begin(), ranking.end(), comp);
    int ranking_size = ranking.size();
    for (int i = 0; i < ranking_size; ++i) {
        tiebreak[true_pos].emplace_back(ranking[i]);
        if (i != ranking_size - 1 && (ranking[i].problems_solved != ranking[i + 1].problems_solved || ranking[i].time_penalty != ranking[i + 1].time_penalty || ranking[i].submission_time != ranking[i + 1].submission_time))
        {
            ++true_pos;
        }
    }

    true_pos = 0;
    int tie_break_size = tiebreak.size();
    for (int i = 0; i < tie_break_size; ++i) {
        int point_count = 0;
        int tie_size = tiebreak[i].size();
        if (tie_size != 0)
        {
            for (int j = 0; j < tie_size; ++j)
            {
                if (true_pos + j < 30) {
                    point_count += points_given[true_pos + j];
                }
            }
            true_pos += tie_size;
            int actual_points = (point_count + tie_size - 1) / tie_size;
            for (int j = 0; j < tie_size; ++j)
            {
                points[tiebreak[i][j].position] = tiebreak[i][j].extra_points + actual_points;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << points[i] << "\n";
    }
}