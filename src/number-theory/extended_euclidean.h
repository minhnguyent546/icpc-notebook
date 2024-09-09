/**
 * Description: for two integers $a$ and $b$, extended Euclidean algorithm
 * allows computing $x$ and $y$ such that: $ax + by = \gcd(a, b)$. Note that such representation
 * always exists by Bézout's identity.
 * Time: $O(\log(\min(a, b)))$
 */

template<typename T>
T extended_euclidean(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    T x1, y1;
    T d = extended_euclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
