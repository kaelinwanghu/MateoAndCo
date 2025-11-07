#include <bits/stdc++.h>

using namespace std;
using vecb = vector<bool>;
using vec = vector<int>;

void fastscan(int &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register int c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    if (c=='-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int q;
    fastscan(q);

    const int n{ 2000000 };
    const int sqrtn{(int)(sqrt(n))};

    vecb prime(n + 1, true);
    vec nonprime(n + 1, 1);
    prime[0] = false;
    prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (!prime[i]) continue;
        for (int j = i * i; j < n + 1; j += i) {
            if (prime[j]) {
                prime[j] = false;
                nonprime[j] += 1;
            }
        }
    }

    for (int i = 2; i * i < n; i++) {
        if (prime[i]) {
            for (int j = i + 1; j < (int)(n / i) + 1; j++) {
                if (prime[j]) continue;
                int m{i * j};
                nonprime[m] += 1;
            }
        }
        else {
            nonprime[i * i] += 1;
            for (int j = i + 1; j < (int)(n / i) + 1; j++) {
                int m{i * j};
                if (prime[j]) nonprime[m] += 1;
                else nonprime[m] += 2;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int query;
        fastscan(query);
        cout << nonprime[query] << '\n';
    }
}