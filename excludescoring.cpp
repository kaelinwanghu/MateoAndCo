#include <bits/stdc++.h>
using namespace std;

bool comp(const int a, const int b)
{
    return a > b;
}

bool pair_comp(const pair<int, int>& a, const pair<int, int>& b)
{
    return a.second > b.second;
}

int points_given[] = {100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num_contests, num_people;
    cin >> num_contests >> num_people;
    vector<vector<int>> scores(num_people, vector<int>(num_contests - 1, 0));
    vector<pair<int, int>> total_scores(num_people, pair<int, int>(0, 0));
    int your_score = 0;
    int worst_pos = 1;
    for (int i = 0; i < num_people; ++i)
    {
        for (int j = 0; j < num_contests - 1; ++j)
        {
            cin >> scores[i][j];
        }
    }
    
    for (int i = 0; i < num_people; ++i)
    {
        sort(scores[i].begin(), scores[i].end(), comp);
        scores[i].resize(4);
        for (int j = 0; j < 4; ++j)
        {
            total_scores[i].second += scores[i][j];
        }
    }
    your_score = total_scores[0].second;
    sort(total_scores.begin(), total_scores.end(), pair_comp);
    int cutoff_index = -1;
    for (int i = 0; i < num_people; ++i)
    {
        if (total_scores[i].second - your_score >= 101)
        {
            cutoff_index = i;
        }
    }
    if (cutoff_index != -1)
    {
        total_scores.resize(cutoff_index);
    }
    int total_scores_size = total_scores.size();
    for (int i = 0; i < total_scores_size; ++i)
    {

    }

    return 0;
}