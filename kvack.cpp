#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 1000000001

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int32_t t, r, upper, lower, remaining;
    int middle;
    cin >> t;
    set<int32_t> ducks;
    cout << "? " << (int32_t)(2e9) << "\n" << flush;
    deque<pair<int32_t, int32_t>> stack;
    cin >> r;
    remaining = r;
    ducks.insert(r);
    upper = r;
    cout << "? " << (int32_t)(-1e9) << "\n" << flush;
    cin >> r;
    ducks.insert(r);
    lower = r;
    stack.emplace_back(lower, upper);
    while (!stack.empty())
    {
        pair<int32_t, int32_t> p = stack.front();
        stack.pop_front();
        upper = p.second;
        lower = p.first;
        if (upper <= lower + 1)
        {
            continue;
        }
        middle = (int) (upper + lower) / 2;
        int32_t quack = p.first + middle;
        cout << "? " << quack << "\n" << flush;
        cin >> r;
        if (reply != lower && reply != upper)
        {
            if (ducks.insert(reply).second)
            {
                stack.emplace_front(lower, reply);
                stack.emplace_front(reply, upper);
            }
            continue;
        }

        if (m + 1 < upper) {
            int32_t reply2 = ask(m + 1);
            if (reply2 != lower && reply2 != upper) {
                if (ducks.insert(reply2).second) {
                    stack.emplace_front(lower, reply2);
                    stack.emplace_front(reply2, upper);
                }
                continue;
            }
        }
    }
    int32_t duck_size = ducks.size();
    cout << "! " << duck_size << "\n" << flush;
    for (auto it = ducks.begin(); it != ducks.end(); ++it)      
    {
        cout << *it << " " << flush;
    }
    cout << endl;
    return 0;
}