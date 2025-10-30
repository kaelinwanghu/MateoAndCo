#include <bits/stdc++.h>
using namespace std;

bool comp(const vector<int>& a, const vector<int>& b)
{
    if (a[1] == b[1])
    {
        return a[2] > b[2];
    }
    return a[1] < b[1];
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_teams, num_events;
    int team, penalty;
    cin >> num_teams >> num_events;
    unordered_map<int, pair<int, int>> scores;
    unordered_map<int, pair<int, int>> ahead;
    unordered_map<int, pair<int, int>> same;
    int min_ahead = -1;
    int current_rank = 1, current_score = 0, current_penalty = 0;
    vector<vector<int>> same_sorter;
    for (int i = 0; i < num_events; ++i)
    {
        // cout << "I: " << i << "\n";
        cin >> team >> penalty;
        scores[team].first += 1;
        scores[team].second += penalty;
        int new_score = scores[team].first;
        int penalty = scores[team].second;
        if (team == 1)
        {
            // cout << "FlAG FLAG\n";
            
            same.clear();
            for (int i = same_sorter.size() - 1; i >= 0; --i)
            {
                if (same_sorter[i][0] == 1)
                {
                    break;
                }
                --current_rank;
            }
            unordered_set<int> to_remove;
            current_score = new_score;
            current_penalty = penalty;
            if (min_ahead != -1 && new_score >= min_ahead)
            {
                int new_min = 1e7;
                for (auto it = ahead.begin(); it != ahead.end(); ++it)
                {
                    int current_score = it->second.first;
                    if (current_score == min_ahead)
                    {
                        to_remove.insert(it->first);
                    }
                    if (current_score > min_ahead && current_score < new_min)
                    {
                        new_min = current_score;
                    }
                }
                if (new_min == 1e7)
                {
                    min_ahead = -1;
                }
                else
                {
                    min_ahead = new_min;
                }
                // cout << "size: " << to_remove.size() << "\n";
                for (auto it = to_remove.begin(); it != to_remove.end(); ++it)
                {
                    ahead.erase(*it);
                    same[*it] = scores[*it];
                }
                same_sorter.clear();
                for (auto it = same.begin(); it != same.end(); ++it)
                {
                    same_sorter.push_back({it->first, it->second.first, it->second.second});
                }
                same_sorter.push_back({1, current_score, current_penalty});
                sort(same_sorter.begin(), same_sorter.end(), comp);
                int actual_idx = 0;
                int same_sorter_size = same_sorter.size();
                for (int i = 0; i < same_sorter_size; ++i)
                {
                    if (same_sorter[i][0] == 1)
                    {
                        actual_idx = i;
                        break;
                    }
                }
                // cout << "sss: " << same_sorter_size << " | aci: " << actual_idx << "\n";
                current_rank -= (same_sorter_size - actual_idx - 1);
            }
        }
        else
        {
            if (new_score > current_score)
            {
                if (ahead.find(team) == ahead.end())
                {
                    current_rank += 1;
                    same.erase(team);
                    if (min_ahead == -1)
                    {
                        min_ahead = new_score;
                    }
                }
                ahead[team] = {new_score, penalty};
            }
            else if (new_score == current_score)
            {
                same[team] = {new_score, penalty};
                if (scores[team].second < current_penalty)
                {
                    current_rank += 1;
                }
            }
        }
        cout << current_rank << "\n";
    }
    return 0;
}