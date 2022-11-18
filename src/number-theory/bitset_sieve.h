/**
 * Description: sieve of eratosthenes for large n (up to 1e9).
 * Time and space (tested on codeforces): 
 *  + For n = 1e8: ~200 ms, 6 MB.
 *  + For n = 1e9: ~4000 ms, 60 MB. 
 */
const int N = (int) 1e8;
bitset<N / 2 + 1> isPrime;
void sieve(int n = N) {
    isPrime.flip();
    isPrime[0] = false;
    for (int i = 3; i <= (int) sqrt(n); i += 2) {
        if (isPrime[i >> 1]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                isPrime[j >> 1] = false;
            }
        }
    }
}
void example(int n) {
    sieve(n);
    int primeCnt = (n >= 2);
    for (int i = 3; i <= n; i += 2) {
        if (isPrime[i >> 1]) {
            primeCnt++;
        }
    }
    cout << primeCnt << '\n';
}
