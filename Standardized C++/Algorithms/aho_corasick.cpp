#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   AHO–CORASICK (MULTI-PATTERN STRING MATCHING)
   - Fixed alphabet [a..z] by default (fast).
   - Insert patterns (optionally with your own IDs), build(), then scan text.
   - find_all(text): returns (end_position, pattern_id) for every match.
   - count_occurrences(text, num_patterns): returns counts per pattern_id.

   Notes:
   - If you need a different alphabet, set SIGMA and base_char.
   - Pattern IDs are 0..k-1 unless you pass explicit ids to add_string().
   ============================================================ */
struct aho_corasick
{
    static constexpr int32_t SIGMA = 26;
    char base_char = 'a';

    vector<array<int32_t, SIGMA>> next; // trie transitions
    vector<int32_t> link;               // suffix link
    vector<int32_t> out_link;           // link to next state with output (dict suffix link)
    vector<vector<int32_t>> out;        // out[state] = pattern_ids ending here

    aho_corasick() { reset(); }

    void reset()
    {
        next.clear(); link.clear(); out.clear(); out_link.clear();
        next.push_back({}); for (int32_t c=0;c<SIGMA;++c) next[0][c] = 0;
        link.push_back(0);
        out.push_back({});
        out_link.push_back(0);
    }

    inline int32_t char_id(char ch) const { return (int32_t)(ch - base_char); }

    // Add a pattern; if id < 0, assign the next available id
    int32_t add_string(const string& s, int32_t id = -1)
    {
        if (id < 0) id = (int32_t)assigned_count();
        int32_t v = 0;
        for (char ch : s)
        {
            int32_t c = char_id(ch);
            if (c < 0 || c >= SIGMA) { /* skip/handle as needed */ continue; }
            if (!next[v][c])
            {
                next[v][c] = (int32_t)next.size();
                next.push_back({}); for (int32_t i=0;i<SIGMA;++i) next.back()[i] = 0;
                link.push_back(0);
                out.push_back({});
                out_link.push_back(0);
            }
            v = next[v][c];
        }
        out[v].push_back(id);
        return id;
    }

    // Build suffix links & dict suffix links
    void build()
    {
        queue<int32_t> q;
        // depth 1
        for (int32_t c = 0; c < SIGMA; ++c)
        {
            int32_t u = next[0][c];
            if (u) { link[u] = 0; q.push(u); }
        }
        // BFS
        while (!q.empty())
        {
            int32_t v = q.front(); q.pop();
            // dict suffix link: first suffix state with outputs
            out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];

            for (int32_t c = 0; c < SIGMA; ++c)
            {
                int32_t u = next[v][c];
                if (u)
                {
                    link[u] = next[link[v]][c];
                    q.push(u);
                }
                else
                {
                    next[v][c] = next[link[v]][c];
                }
            }
        }
        // root dict link = 0 by default
    }

    // Return (end_pos, pattern_id) for each match
    vector<pair<int32_t,int32_t>> find_all(const string& text) const
    {
        vector<pair<int32_t,int32_t>> matches;
        int32_t v = 0;
        for (int32_t i = 0; i < (int32_t)text.size(); ++i)
        {
            char ch = text[i];
            int32_t c = char_id(ch);
            if (c < 0 || c >= SIGMA) { v = 0; continue; } // reset on out-of-alphabet

            v = next[v][c];

            // Emit outputs at v
            for (int32_t pid : out[v]) matches.emplace_back(i, pid);
            // Follow dict suffix links
            int32_t u = out_link[v];
            while (u)
            {
                for (int32_t pid : out[u]) matches.emplace_back(i, pid);
                u = out_link[u];
            }
        }
        return matches;
    }

    // Return counts per pattern id in [0..num_patterns-1]
    vector<int32_t> count_occurrences(const string& text, int32_t num_patterns) const
    {
        vector<int32_t> cnt(num_patterns, 0);
        int32_t v = 0;
        for (int32_t i = 0; i < (int32_t)text.size(); ++i)
        {
            int32_t c = char_id(text[i]);
            if (c < 0 || c >= SIGMA) { v = 0; continue; }

            v = next[v][c];

            for (int32_t pid : out[v]) if (0 <= pid && pid < num_patterns) ++cnt[pid];
            int32_t u = out_link[v];
            while (u)
            {
                for (int32_t pid : out[u]) if (0 <= pid && pid < num_patterns) ++cnt[pid];
                u = out_link[u];
            }
        }
        return cnt;
    }

    size_t assigned_count() const
    {
        // Not strictly tracked: caller should pass num_patterns to count_occurrences()
        // Here we expose a helper if you auto-assign (use external counter in practice).
        size_t k = 0;
        for (auto &vec : out) k += vec.size();
        return k; // upper bound if duplicates; prefer your own id assignments.
    }
};
