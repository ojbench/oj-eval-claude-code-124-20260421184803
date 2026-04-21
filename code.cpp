#include <bits/stdc++.h>
using namespace std;

static inline int readInt() {
    int c = getchar_unlocked();
    while (c != EOF && (c < '0' || c > '9')) {
        if (c == '-') break;
        c = getchar_unlocked();
    }
    int neg = 0;
    if (c == '-') { neg = 1; c = getchar_unlocked(); }
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return neg ? -x : x;
}

struct SegTree {
    int n;
    vector<long long> mx, lz;
    SegTree(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = max(1, n_);
        mx.assign(4*n+5, 0);
        lz.assign(4*n+5, 0);
    }
    inline void apply(int idx, long long v) {
        mx[idx] += v;
        lz[idx] += v;
    }
    inline void push(int idx) {
        long long z = lz[idx];
        if (z != 0) {
            apply(idx<<1, z);
            apply(idx<<1|1, z);
            lz[idx] = 0;
        }
    }
    inline void pull(int idx) {
        mx[idx] = max(mx[idx<<1], mx[idx<<1|1]);
    }
    void range_add(int ql, int qr, long long v, int idx, int l, int r) {
        if (ql <= l && r <= qr) { apply(idx, v); return; }
        push(idx);
        int mid = (l + r) >> 1;
        if (ql <= mid) range_add(ql, qr, v, idx<<1, l, mid);
        if (qr >  mid) range_add(ql, qr, v, idx<<1|1, mid+1, r);
        pull(idx);
    }
    long long range_max(int ql, int qr, int idx, int l, int r) {
        if (ql <= l && r <= qr) return mx[idx];
        push(idx);
        int mid = (l + r) >> 1;
        long long res = LLONG_MIN;
        if (ql <= mid) res = max(res, range_max(ql, qr, idx<<1, l, mid));
        if (qr >  mid) res = max(res, range_max(ql, qr, idx<<1|1, mid+1, r));
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, k, p;
    // Use fast reader for large input
    x = readInt();
    if (x == 0 && feof(stdin)) return 0;
    k = readInt();
    p = readInt();

    int segments = max(0, x - 1);
    SegTree st(segments == 0 ? 1 : segments);

    string out;
    out.reserve(p + 8);

    for (int i = 0; i < p; ++i) {
        int u = readInt();
        int v = readInt();
        int n = readInt();
        if (segments == 0) {
            out.push_back('T');
            out.push_back('\n');
            continue;
        }
        int l = max(1, min(u, v));
        int r = max(u, v) - 1;
        if (r < l) { // no travel or invalid; treat as no segments occupied
            out.push_back('T');
            out.push_back('\n');
            continue;
        }
        long long curMax = st.range_max(l, r, 1, 1, segments);
        if (curMax + n <= (long long)k) {
            st.range_add(l, r, n, 1, 1, segments);
            out.push_back('T');
        } else {
            out.push_back('N');
        }
        out.push_back('\n');
    }

    fwrite(out.c_str(), 1, out.size(), stdout);
    return 0;
}
