/**
 * Time: $O(N\log{N})$.
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
}