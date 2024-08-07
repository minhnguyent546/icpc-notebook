const int MAXN = (int) 1e6;
int divisor_count[MAXN + 3];
void divisor_sieve(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            divisor_count[j]++;
        }
    }
    // Time complexity: O(NlogN).
}
void better_divisor_sieve(int n) {
    for (int i = 1; i <= (int) sqrt(n); ++i) {
        divisor_count[i * i] += 1;
        for (int j = i * (i + 1); j <= n; j += i) {
            divisor_count[j] += 2;
        }
    }
    // Better than O(NlogN).
}