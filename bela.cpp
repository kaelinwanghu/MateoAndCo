#include <bits/stdc++.h>
using namespace std;

int dominant_table[] = {11, 4, 3, 20, 10, 14, 0, 0};
int submissive_table[] = {11, 4, 3, 2, 10, 0, 0, 0};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char dominant, card, suit;
    int total = 0;
    int n;
    cin >> n >> dominant;
    for (int i = 0; i < 4 * n; ++i)
    {
        int* correct_table;
        cin >> card >> suit;
        if (suit == dominant)
        {
            correct_table = dominant_table;
        }
        else
        {
            correct_table = submissive_table;
        }
        switch (card)
        {
            case 'A':
                total += correct_table[0];
                break;
            case 'K':
                total += correct_table[1];
                break;
            break;
            case 'Q':
                total += correct_table[2];
                break;
            break;
            case 'J':
                total += correct_table[3];
                break;
            break;
            case 'T':
                total += correct_table[4];
                break;
            break;
            case '9':
                total += correct_table[5];
                break;
            break;
            case '8':
                total += correct_table[6];
                break;
            break;
            case '7':
                total += correct_table[7];
                break;
            break;
        }
    }
    cout << total << "\n";
    return 0;
}