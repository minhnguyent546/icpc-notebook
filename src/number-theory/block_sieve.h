/**
 * Source: kactl.
 * Description: a very fast sieve of eratosthenes for large n (up to $10^9$).
 * Time: time and space tested on codeforces:
 *   + For $n = 10^8$: ~160 ms, 60 MB.
 *   + For $n = 10^9$: ~1600 ms, 505 MB.
 */

const int N = (int) 1e8;
bitset<N + 1> is_prime;
vector<int> fast_sieve() {
    const int S = (int) sqrt(N), R = N / 2;
    vector<int> primes = {2};
    vector<bool> sieve(S + 1, true);
    vector<array<int, 2>> cp;
    for (int i = 3; i <= S; i += 2) {
        if (sieve[i]) {
            cp.push_back({i, i * i / 2});
            for (int j = i * i; j <= S; j += 2 * i) {
                sieve[j] = false;
            }
        }
    }
    for (int L = 1; L <= R; L += S) {
        array<bool, S> block{};
        for (auto &[p, idx] : cp) {
            for (; idx < S + L; idx += p) block[idx - L] = true;
        }
        for (int i = 0; i < min(S, R - L); ++i) {
            if (!block[i]) primes.push_back((L + i) * 2 + 1);
        }
    }
    for (int p : primes) is_prime[p] = true;
    return primes;
}