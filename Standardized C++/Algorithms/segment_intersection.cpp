// GEOMETRY TOOLBOX — SEGMENT INTERSECTION & DISTANCES (C++17+)
// - Robust-ish EPS comparisons for doubles
// - Intersection classification: NONE / POINT / OVERLAP (segment)
// - Distance: point↔point, point↔segment, segment↔segment
// - Boolean intersection fast path
//
// Conventions:
//   * Coordinates are double.
//   * "On segment" uses bounding-box check with EPS.
//   * For exact-geometry problems with integer coords, consider long double.
//
// If you want the legacy exact-equality behavior, set EPS = 0.

#include <bits/stdc++.h>
using namespace std;

// -----------------------------
// Types & constants
// -----------------------------
struct point { double x, y; };

static constexpr double EPS = 1e-12;

inline int sign(double v) {
    if (v >  EPS) return  1;
    if (v < -EPS) return -1;
    return 0;
}

inline bool nearly_equal(double a, double b) {
    return fabs(a - b) <= EPS;
}

// -----------------------------
// Vector helpers
// -----------------------------
inline point operator+(const point& a, const point& b) { return {a.x + b.x, a.y + b.y}; }
inline point operator-(const point& a, const point& b) { return {a.x - b.x, a.y - b.y}; }
inline point operator*(const point& a, double k)       { return {a.x * k, a.y * k}; }

inline double dot_product(const point& a, const point& b) { return a.x * b.x + a.y * b.y; }
inline double cross_product(const point& a, const point& b){ return a.x * b.y - a.y * b.x; }
inline double cross_product(const point& o, const point& a, const point& b) {
    // (a - o) x (b - o)
    return cross_product(a - o, b - o);
}

// Orientation / direction: +1 CCW, -1 CW, 0 collinear (with EPS)
inline int orientation(const point& a, const point& b, const point& c) {
    return sign(cross_product(a, b, c));
}

// -----------------------------
// Bounding box & on-segment
// -----------------------------
inline bool in_range(double v, double lo, double hi) {
    return v + EPS >= min(lo, hi) && v - EPS <= max(lo, hi);
}

inline bool on_segment_bbox(const point& a, const point& b, const point& p) {
    // assumes collinearity checked by caller if needed
    return in_range(p.x, a.x, b.x) && in_range(p.y, a.y, b.y);
}

inline bool on_segment(const point& a, const point& b, const point& p) {
    // collinear + bbox
    return orientation(a, b, p) == 0 && on_segment_bbox(a, b, p);
}

// -----------------------------
// Fast boolean segment intersection
// -----------------------------
inline bool segments_intersect_bool(const point& p1, const point& p2,
                                    const point& p3, const point& p4)
{
    int d1 = orientation(p3, p4, p1);
    int d2 = orientation(p3, p4, p2);
    int d3 = orientation(p1, p2, p3);
    int d4 = orientation(p1, p2, p4);

    if (d1 * d2 < 0 && d3 * d4 < 0) return true; // proper intersection

    // collinear cases (touching)
    if (d1 == 0 && on_segment_bbox(p3, p4, p1)) return true;
    if (d2 == 0 && on_segment_bbox(p3, p4, p2)) return true;
    if (d3 == 0 && on_segment_bbox(p1, p2, p3)) return true;
    if (d4 == 0 && on_segment_bbox(p1, p2, p4)) return true;

    return false;
}

// -----------------------------
// Intersection classification
// -----------------------------
struct segment_intersection_result {
    enum kind_t { NONE, POINT, OVERLAP } kind = NONE;
    point p;        // valid if kind == POINT
    point a, b;     // valid if kind == OVERLAP (segment [a,b] in lexicographic order)
};

// Lexicographic compare for points
inline bool point_lex_lt(const point& a, const point& b) {
    if (!nearly_equal(a.x, b.x)) return a.x < b.x;
    return a.y < b.y - EPS;
}

inline point lex_min(point u, point v) { return point_lex_lt(u, v) ? u : v; }
inline point lex_max(point u, point v) { return point_lex_lt(u, v) ? v : u; }

// Line intersection (p1,p2) with (p3,p4) when not parallel.
// Returns the intersection point of the *lines* (not checking segment bounds).
inline point line_intersection_point(const point& p1, const point& p2,
                                     const point& p3, const point& p4)
{
    // Solve: p1 + t*(p2-p1)  ==  p3 + u*(p4-p3)
    point r = p2 - p1;
    point s = p4 - p3;
    double denom = cross_product(r, s);
    // Caller ensures not parallel (|denom| > EPS)
    double t = cross_product(p3 - p1, s) / denom;
    return p1 + r * t;
}

segment_intersection_result segment_intersection(const point& p1, const point& p2,
                                                 const point& p3, const point& p4)
{
    segment_intersection_result res;

    int o1 = orientation(p1, p2, p3);
    int o2 = orientation(p1, p2, p4);
    int o3 = orientation(p3, p4, p1);
    int o4 = orientation(p3, p4, p2);

    // Proper intersection at a single point
    if (o1 * o2 < 0 && o3 * o4 < 0) {
        // lines are guaranteed non-parallel here
        res.kind = segment_intersection_result::POINT;
        res.p = line_intersection_point(p1, p2, p3, p4);
        return res;
    }

    // Collinear or touching endpoints
    if (o1 == 0 && on_segment_bbox(p1, p2, p3)) { res.kind = segment_intersection_result::POINT; res.p = p3; return res; }
    if (o2 == 0 && on_segment_bbox(p1, p2, p4)) { res.kind = segment_intersection_result::POINT; res.p = p4; return res; }
    if (o3 == 0 && on_segment_bbox(p3, p4, p1)) { res.kind = segment_intersection_result::POINT; res.p = p1; return res; }
    if (o4 == 0 && on_segment_bbox(p3, p4, p2)) { res.kind = segment_intersection_result::POINT; res.p = p2; return res; }

    // Check collinearity for potential overlap
    if (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0) {
        // All four are collinear → compute overlapping segment (if any).
        // Normalize each segment so start <= end (lexicographically).
        point a = lex_min(p1, p2), b = lex_max(p1, p2);
        point c = lex_min(p3, p4), d = lex_max(p3, p4);

        point start = lex_max(a, c);
        point finish = lex_min(b, d);

        if (!point_lex_lt(finish, start) && !point_lex_lt(start, finish)) {
            // single shared point
            res.kind = segment_intersection_result::POINT;
            res.p = start; // == finish
            return res;
        }
        if (point_lex_lt(start, finish)) {
            res.kind = segment_intersection_result::OVERLAP;
            res.a = start; res.b = finish;
            return res;
        }
        // Collinear but disjoint
        res.kind = segment_intersection_result::NONE;
        return res;
    }

    // Disjoint
    res.kind = segment_intersection_result::NONE;
    return res;
}

// -----------------------------
// Distances
// -----------------------------
inline double distance_point_point(const point& a, const point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

// Distance from point p to segment ab
inline double distance_point_segment(const point& p, const point& a, const point& b)
{
    point ab = b - a;
    double len2 = dot_product(ab, ab);
    if (len2 <= EPS) return distance_point_point(p, a); // a==b
    // Project p onto line a->b, clamp to [0,1]
    double t = dot_product(p - a, ab) / len2;
    if (t <= 0.0) return distance_point_point(p, a);
    if (t >= 1.0) return distance_point_point(p, b);
    point proj = a + ab * t;
    return distance_point_point(p, proj);
}

// Distance between segments p1p2 and p3p4
inline double distance_segment_segment(const point& p1, const point& p2,
                                       const point& p3, const point& p4)
{
    if (segments_intersect_bool(p1, p2, p3, p4)) return 0.0;
    double d1 = distance_point_segment(p1, p3, p4);
    double d2 = distance_point_segment(p2, p3, p4);
    double d3 = distance_point_segment(p3, p1, p2);
    double d4 = distance_point_segment(p4, p1, p2);
    return min(min(d1, d2), min(d3, d4));
}

// -----------------------------
// OPTIONAL: demo main (comment out or compile with -DLOCAL_TEST_GEOM)
// -----------------------------
#ifdef LOCAL_TEST_GEOM
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int32_t t;
    if (!(cin >> t)) return 0;
    cout.setf(std::ios::fixed); cout << setprecision(2);

    while (t--) {
        point p1, p2, p3, p4;
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;

        auto inter = segment_intersection(p1, p2, p3, p4);
        if (inter.kind == segment_intersection_result::OVERLAP) {
            // overlapping segment [a,b]
            auto fix0 = [](double v){ return nearly_equal(v, 0.0) ? 0.0 : v; };
            cout << fix0(inter.a.x) << " " << fix0(inter.a.y) << " "
                 << fix0(inter.b.x) << " " << fix0(inter.b.y) << "\n";
        } else if (inter.kind == segment_intersection_result::POINT) {
            auto fix0 = [](double v){ return nearly_equal(v, 0.0) ? 0.0 : v; };
            cout << fix0(inter.p.x) << " " << fix0(inter.p.y) << "\n";
        } else {
            // no intersection → print min distance
            double d = distance_segment_segment(p1, p2, p3, p4);
            cout << d << "\n";
        }
    }
    return 0;
}
#endif
