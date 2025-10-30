#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_correct, differences = 0;
    string f_answers, y_answers;
    cin >> num_correct >> f_answers >> y_answers;
    int num_answers = f_answers.size();
    for (int i = 0; i < num_answers; ++i)
    {
        if (f_answers[i] != y_answers[i])
        {
            ++differences;
        }
    }
    cout << min(differences, num_answers - num_correct) + min(num_answers - differences, num_correct) << "\n";
    return 0;
}