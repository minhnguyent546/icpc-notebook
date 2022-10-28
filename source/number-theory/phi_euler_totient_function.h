const int MAXN = (int) 2e5;
int etf[MAXN + 1];
void sieve(int n) {                                                                                                          
    for (int i = 0; i <= n; ++i) {
        etf[i] = i;
    }
    for (int i = 2; i <= n; ++i) {
        if (etf[i] == i) {
            for (int j = i; j <= n; j += i) {
                etf[j] -= etf[j] / i;
            }
        }
    }
    // Time complexity: O(NlogN).
}
