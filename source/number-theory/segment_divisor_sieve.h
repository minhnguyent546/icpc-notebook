const int MAXN = (int) 1e6; // R - L + 1 <= N.
int divisor_count[MAXN + 3];
void segment_divisor_sieve(long long L, long long R) {
    for (long long i = 1; i <= (long long) sqrt(R); ++i) {
        long long start1 = ((L + i - 1) / i) * i;
        long long start2 = i * i;
        long long j = max(start1, start2);
        if (j == start2) {
            divisor_count[j - L] += 1;
            j += i;
        }
        for ( ; j <= R; j += i) {
            divisor_count[j - L] += 2;
        }
    }
}
