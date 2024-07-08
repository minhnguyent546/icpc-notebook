/**
 * Description: a fast algorithm for multiplying two polynomials.
 * Time: $O(N\log{N})$.
 */

const double PI = acos(-1);
using Comp = complex<double>;
int reverse_bit(int n, int lg) {
    int res = 0;
    for (int i = 0; i < lg; ++i) {
        if (n & (1 << i)) {
            res |= (1 << (lg - i - 1));
        }
    }
    return res;
}
void fft(vector<Comp> &a, bool invert = false) {
    int n = (int) a.size();
    int lg = 0;
    while (1 << (lg) < n) ++lg;
    for (int i = 0; i < n; ++i) {
        int rev_i = reverse_bit(i, lg);
        if (i < rev_i) swap(a[i], a[rev_i]);
    }
    for (int len = 2; len <= n; len *= 2) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        Comp w_base(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            Comp w(1);
            for (int j = i; j < i + len / 2; ++j) {
                Comp u = a[j], v = a[j + len / 2];
                a[j] = u + w * v;
                a[j + len / 2] = u - w * v;
                w *= w_base;
            }
        }
    }
    if (invert) for (int i = 0; i < n; ++i) a[i] /= n;
}
vector<int> mult(vector<int> &a, vector<int> &b) {
    vector<Comp> A(a.begin(), a.end()), B(b.begin(), b.end());
    int n = (int) a.size(), m = (int) b.size(), p = 1;
    while (p < n + m) p *= 2;
    A.resize(p), B.resize(p);
    fft(A, false);
    fft(B, false);
    for (int i = 0; i < p; ++i) {
        A[i] *= B[i];
    }
    fft(A, true);
    vector<int> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
        res[i] = (int) round(A[i].real());
    }
    return res;
}