/*
+ For a positive integer N = p1^k1 * p2^k2 * ... * px^kx.
+ mu(1) = 1.
+ mu(N) = 0, if there is exist i such that ki > 1.
+ mu(N) = (-1)^x, otherwise.
*/
const int MAXN = (int) 2e5;
int mu[MAXN + 1];
void sieve(int n) {
    mu[1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 2 * i; j <= n; j += i) {
            mu[j] -= mu[i];
        }
    }
    // Time complexity: O(Nlog(N)).
}
