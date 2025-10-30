#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    deque<char> stack;
    getline(cin, s);
    unordered_set<string> seen;
    string final;
    string current_object;
    string first_seen;
    int s_size = s.size();
    for (int i = 0; i < s_size; ++i)
    {
        char c = s[i];
        current_object += c;
        if (c == ')')
        {
            if (!stack.empty())
            {
                stack.pop_back();
                if (stack.empty())
                {
                    seen.insert(current_object);
                    if (first_seen.size() == 0)
                    {
                        first_seen = current_object;
                    }
                    else
                    {
                        final += current_object;
                    }
                    current_object = "";
                }
            }
        }
        else
        {
            stack.emplace_back(s[i]);
        }
    }

    if (seen.size() == 1)
    {
        printf("no\n");
    }
    else
    {
        cout << final << first_seen;
        cout << "\n";
    }
}