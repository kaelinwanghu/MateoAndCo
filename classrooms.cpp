#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<pair<int, int>> activities(N);
    int i = 0;
    FOR(i, 0, N){
        int start, end;
        cin >> start >> end;
        activities[i] = {start, end};
    }

    // sort by nondecreasing end time
    sort(activities.begin(), activities.end(), [](pair<int, int> a1, pair<int, int> a2){
        if(a1.second == a2.second){
            // if equal return smaller activity
            return a1.first > a2.first;
        } else {
            return a1.second < a2.second;
        }
    });

    multiset<int> classrooms;
    int result = 0;
    FOR(i, 0, N){
        auto it = classrooms.lower_bound(activities[i].first); // get first classroom that can accommodate activity i
        if(it == classrooms.begin()){ 
            if(classrooms.size()<K){ // there is a classroom we can use
                result++;
                classrooms.insert(activities[i].second);
            }
        } else { // activity ended
            result++;
            --it;
            classrooms.erase(it); // remove activity and add next
            classrooms.insert(activities[i].second);
        }
    }
    
    cout << result << endl;
    return 0;
}