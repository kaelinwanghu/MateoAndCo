// KMP TOOLKIT — GENERIC (C++17+)
// Works for any vector-like container (e.g. vector<int32_t>, vector<char>, vector<long long>).
// Same conventions as string KMP version.
// - Overlapping matches supported
// - Empty pattern matches at every position 0..n
//
// Usage:
//   vector<int32_t> text = {1, 2, 3, 1, 2, 3, 1};
//   vector<int32_t> pattern = {1, 2, 3};
//   auto matches = kmp_search_all_seq(text, pattern);  // returns {0, 3}
//   auto first = kmp_find_first_seq(text, pattern);    // returns 0
//   auto count = kmp_count_occurrences_seq(text, pattern); // returns 2

#include <bits/stdc++.h>
using namespace std;

// Build LPS array for generic vector<T>
template <typename T>
vector<int32_t> kmp_build_lps_seq(const vector<T>& pattern)
{
    const int32_t m = static_cast<int32_t>(pattern.size());
    vector<int32_t> lps(m, 0);
    int32_t len = 0;

    for (int32_t i = 1; i < m; )
    {
        if (pattern[i] == pattern[len])
        {
            lps[i++] = ++len;
        }
        else if (len > 0)
        {
            len = lps[len - 1];
        }
        else
        {
            lps[i++] = 0;
        }
    }
    return lps;
}

// Return all starting indices where pattern occurs in text (overlapping allowed)
template <typename T>
vector<int32_t> kmp_search_all_seq(const vector<T>& text, const vector<T>& pattern)
{
    const int32_t n = static_cast<int32_t>(text.size());
    const int32_t m = static_cast<int32_t>(pattern.size());
    vector<int32_t> matches;

    if (m == 0)
    {
        matches.reserve(n + 1);
        for (int32_t i = 0; i <= n; ++i) matches.push_back(i);
        return matches;
    }
    if (n < m) return matches;

    vector<int32_t> lps = kmp_build_lps_seq(pattern);
    int32_t i = 0, j = 0;

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            ++i; ++j;
            if (j == m)
            {
                matches.push_back(i - m);
                j = lps[j - 1];
            }
        }
        else if (j > 0)
        {
            j = lps[j - 1];
        }
        else
        {
            ++i;
        }
    }
    return matches;
}

// Return the index of the first occurrence of pattern in text, or -1 if not found.
template <typename T>
int32_t kmp_find_first_seq(const vector<T>& text, const vector<T>& pattern)
{
    const int32_t n = static_cast<int32_t>(text.size());
    const int32_t m = static_cast<int32_t>(pattern.size());

    if (m == 0) return 0;
    if (n < m) return -1;

    vector<int32_t> lps = kmp_build_lps_seq(pattern);
    int32_t i = 0, j = 0;

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            ++i; ++j;
            if (j == m) return i - m;
        }
        else if (j > 0)
        {
            j = lps[j - 1];
        }
        else
        {
            ++i;
        }
    }
    return -1;
}

// Count occurrences (overlapping) of pattern in text.
template <typename T>
int32_t kmp_count_occurrences_seq(const vector<T>& text, const vector<T>& pattern)
{
    return static_cast<int32_t>(kmp_search_all_seq(text, pattern).size());
}
