#include <bits/stdc++.h>
using namespace std;

// ============================================================
// SUFFIX ARRAY + LCP + PATTERN SEARCH + LCE (C++17)
//   - Indices: int32_t, text is std::string
//   - SA: sa[i] = start index of i-th smallest suffix
//   - LCP: lcp[i] = LCP(SA[i], SA[i-1]), with lcp[0] = 0 (size n)
// ============================================================

// ---------- Suffix Array (O(n log n), doubling) ----------
vector<int32_t> build_suffix_array(const string& s) {
    int32_t n = (int32_t)s.size();
    vector<int32_t> sa(n), rankv(n), tmp(n);

    // Initial ranking by character (0..255)
    for (int32_t i = 0; i < n; ++i) {
        sa[i] = i;
        rankv[i] = (unsigned char)s[i];
    }

    for (int32_t k = 1;; k <<= 1) {
        auto key2 = [&](int32_t i) { return i + k < n ? rankv[i + k] : -1; };

        // Sort by (rankv[i], rankv[i+k]) using lambda comparator
        sort(sa.begin(), sa.end(), [&](int32_t a, int32_t b) {
            if (rankv[a] != rankv[b]) return rankv[a] < rankv[b];
            return key2(a) < key2(b);
        });

        tmp[sa[0]] = 0;
        for (int32_t i = 1; i < n; ++i) {
            tmp[sa[i]] = tmp[sa[i-1]]
                       + (rankv[sa[i-1]] != rankv[sa[i]] || key2(sa[i-1]) != key2(sa[i]));
        }
        for (int32_t i = 0; i < n; ++i) rankv[i] = tmp[i];
        if (rankv[sa.back()] == n - 1) break; // all ranks unique
    }
    return sa;
}

// ---------- Kasai LCP (O(n)) ----------
vector<int32_t> build_lcp_kasai(const string& s, const vector<int32_t>& sa) {
    int32_t n = (int32_t)s.size();
    vector<int32_t> rankv(n, 0), lcp(n, 0);
    for (int32_t i = 0; i < n; ++i) rankv[sa[i]] = i;

    int32_t k = 0;
    for (int32_t i = 0; i < n; ++i) {
        int32_t r = rankv[i];
        if (r == 0) { k = 0; continue; }
        int32_t j = sa[r - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[r] = k; // LCP between sa[r] and sa[r-1]
        if (k) --k;
    }
    return lcp; // lcp[0]=0
}

// ---------- Pattern search over SA (returns [lo, hi) in SA where suffixes start with pattern) ----------
pair<int32_t,int32_t> sa_find_range(const string& s, const vector<int32_t>& sa, const string& pat) {
    auto cmp_lower = [&](int32_t suf_idx) {
        // compare suffix s.substr(suf_idx) with pat
        int32_t i = suf_idx, j = 0, n = (int32_t)s.size(), m = (int32_t)pat.size();
        while (i < n && j < m) {
            if (s[i] != pat[j]) return s[i] < pat[j];
            ++i; ++j;
        }
        return j < m; // true => suffix is shorter/less than pattern → go right
    };
    auto cmp_upper = [&](int32_t suf_idx) {
        int32_t i = suf_idx, j = 0, n = (int32_t)s.size(), m = (int32_t)pat.size();
        while (i < n && j < m) {
            if (s[i] != pat[j]) return s[i] < pat[j];
            ++i; ++j;
        }
        return false; // equal → not strictly less than "next" → upper bound skips equal range
    };

    int32_t n = (int32_t)sa.size();
    int32_t lo = 0, hi = n; // lower_bound
    while (lo < hi) {
        int32_t mid = (lo + hi) >> 1;
        if (cmp_lower(sa[mid])) lo = mid + 1; else hi = mid;
    }
    int32_t L = lo;

    lo = 0; hi = n; // upper_bound on pattern's last suffix start
    while (lo < hi) {
        int32_t mid = (lo + hi) >> 1;
        if (cmp_upper(sa[mid])) lo = mid + 1; else hi = mid;
    }
    int32_t R = lo;

    // Validate first position actually matches
    if (L >= R) return {-1, -1};
    // quick check: confirm prefix at SA[L]
    {
        int32_t i = sa[L], j = 0, n2 = (int32_t)s.size(), m2 = (int32_t)pat.size();
        while (i < n2 && j < m2 && s[i] == pat[j]) { ++i; ++j; }
        if (j != m2) return {-1, -1};
    }
    return {L, R};
}

// ---------- Sparse Table for RMQ(min) over LCP (for LCE queries) ----------
struct sparse_table_min {
    int32_t n = 0, K = 0;
    vector<int32_t> lg2;
    vector<vector<int32_t>> st; // st[k][i] = min on [i, i+2^k)

    void build(const vector<int32_t>& a) {
        n = (int32_t)a.size();
        lg2.resize(n + 1);
        lg2[1] = 0;
        for (int32_t i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
        K = lg2[n];
        st.assign(K + 1, vector<int32_t>(n));
        st[0] = a;
        for (int32_t k = 1; k <= K; ++k) {
            int32_t len = 1 << k;
            int32_t half = len >> 1;
            for (int32_t i = 0; i + len <= n; ++i)
                st[k][i] = min(st[k-1][i], st[k-1][i + half]);
        }
    }

    // min on [l, r] inclusive
    int32_t query(int32_t l, int32_t r) const {
        if (l > r) swap(l, r);
        int32_t len = r - l + 1;
        int32_t k = lg2[len];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

// ---------- LCE (Longest Common Extension) using SA + rank + LCP RMQ ----------
// Returns LCP of suffixes starting at i and j.
struct lce_query {
    vector<int32_t> rankv;  // rankv[pos] = rank of suffix at pos
    sparse_table_min rmq;   // RMQ over LCP
    // lcp[i] = LCP(sa[i], sa[i-1]), lcp[0]=0

    void build(const string& s, const vector<int32_t>& sa, const vector<int32_t>& lcp) {
        int32_t n = (int32_t)s.size();
        rankv.assign(n, 0);
        for (int32_t i = 0; i < n; ++i) rankv[sa[i]] = i;
        rmq.build(lcp);
    }

    int32_t lce(int32_t i, int32_t j) const {
        if (i == j) return (int32_t)rankv.size() - i;
        int32_t ri = rankv[i], rj = rankv[j];
        if (ri > rj) swap(ri, rj);
        // LCP between sa[ri]..sa[rj] is min over lcp[ri+1..rj]
        if (ri + 1 > rj) return 0;
        return rmq.query(ri + 1, rj);
    }
};

// ============================================================
// OPTIONAL: usage demo (compile with -DLOCAL_TEST_SA)
// ============================================================
#ifdef LOCAL_TEST_SA
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s = "banana$"; // include a terminal smaller than all other chars
    auto sa  = build_suffix_array(s);
    auto lcp = build_lcp_kasai(s, sa);

    // Print SA
    cout << "SA: ";
    for (int32_t i = 0; i < (int32_t)sa.size(); ++i) cout << sa[i] << " ";
    cout << "\nLCP: ";
    for (int32_t i = 0; i < (int32_t)lcp.size(); ++i) cout << lcp[i] << " ";
    cout << "\n";

    // Pattern search
    string pat = "ana";
    auto [L, R] = sa_find_range(s, sa, pat);
    if (L != -1) {
        cout << "Matches of \"" << pat << "\" at positions: ";
        for (int32_t i = L; i < R; ++i) cout << sa[i] << " ";
        cout << "\n";
    } else {
        cout << "No match for \"" << pat << "\"\n";
    }

    // LCE example
    lce_query lq;
    lq.build(s, sa, lcp);
    cout << "LCE(1,3) = " << lq.lce(1, 3) << "\n"; // "anana$" vs "ana$" -> 3

    return 0;
}
#endif
