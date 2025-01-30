/**
 * Description: for two integers $a$ and $b$, extended Euclidean algorithm
 * allows computing $x$ and $y$ such that: $ax + by = \gcd(a, b)$. Note that such representation
 * always exists by Bézout's identity.
 * Time: $O(\log(\min(a, b)))$
 */

int64_t euclidean(int64_t a, int64_t b) {
    while (b > 0) {
        int64_t k = a / b;
        a -= k * b;
        swap(a, b);
    }
    return a;
}

array<int64_t, 3> extended_euclidean(int64_t a, int64_t b) {
    array<int64_t, 3> x{1, 0, a};
    array<int64_t, 3> y{0, 1, b};
    while (y[2] > 0) {
        int64_t k = x[2] / y[2];
        for (int i = 0; i < 3; ++i) x[i] -= k * y[i];
        x.swap(y);
    }
    return x; // (x, y, gcd)
}

int64_t inv(int64_t a, int64_t M) {
    array<int64_t, 3> x = extended_euclidean(a, M);
    int64_t ret = x[0] % M;
    if (ret < 0) ret += M;
    return ret;
}
