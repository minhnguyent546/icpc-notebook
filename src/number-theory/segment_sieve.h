long long ceil_div(long long a, long long b) {
    return a / b + ((a ^ b) > 0 && (a % b != 0));
    // floor(x) <= x <= ceil(x) for both positive and negative.
}
long long floor_div(long long a, long long b) {
    return a / b - ((a ^ b) < 0 && (a % b != 0));
}

vector<bool> prime;
void segment_sieve(long long L, long long R) {
    // 1 <= L <= R, R - L + 1 <= 1e6.
    int n = R - L + 1;
    prime.assign(n, true);
    for (long long i = 2; i <= (long long) sqrt(R); ++i) {
        long long start = max(i * i, ceil_div(L, i) * i);
        for (long long j = start; j <= R; j += i) {
            prime[j - L] = false;
        }
    }
    if (L == 1) prime[1 - L] = false;
}
// input: 1000000000000 1000000100000.
// output should be: 3614.
