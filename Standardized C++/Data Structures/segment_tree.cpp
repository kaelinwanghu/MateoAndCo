#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 2) SEGMENT TREE (sum) — point update, range sum query
//    - 0-indexed interface
//    - int64_t for sums
// ============================================================
struct segment_tree_sum
{
    int32_t n = 0;              // original array size
    int32_t size_pow2 = 0;      // internal power-of-two size
    vector<int64_t> tree;       // tree nodes

    segment_tree_sum() = default;
    explicit segment_tree_sum(int32_t n_) { init(n_); }

    void init(int32_t n_)
    {
        n = n_;
        size_pow2 = 1;
        while (size_pow2 < n) size_pow2 <<= 1;
        tree.assign(2 * size_pow2, 0);
    }

    // build from 0-indexed array a[0..n-1]
    void build_from(const vector<int64_t>& a)
    {
        init(static_cast<int32_t>(a.size()));
        for (int32_t i = 0; i < n; ++i) tree[size_pow2 + i] = a[i];
        for (int32_t i = size_pow2 - 1; i >= 1; --i)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    // point set: a[pos] = value
    void point_set(int32_t pos, int64_t value)
    {
        int32_t p = size_pow2 + pos;
        tree[p] = value;
        for (p >>= 1; p >= 1; p >>= 1)
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }

    // point add: a[pos] += delta
    void point_add(int32_t pos, int64_t delta)
    {
        int32_t p = size_pow2 + pos;
        tree[p] += delta;
        for (p >>= 1; p >= 1; p >>= 1)
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }

    // range sum on [l, r], 0-indexed inclusive
    int64_t range_sum(int32_t l, int32_t r) const
    {
        int64_t res = 0;
        int32_t L = l + size_pow2, R = r + size_pow2;
        while (L <= R)
        {
            if (L & 1) res += tree[L++];
            if (!(R & 1)) res += tree[R--];
            L >>= 1; R >>= 1;
        }
        return res;
    }
};