/**
 * Description: Bareiss algorithm for computing determinant of a square matrix A
 * with integer entries using only integer arithmetic.
 * Time: $O(N^3)$.
 * Usage:
 *   - Kirchhoff's theorem: finding the number of spanning trees.
 */

long long determinant(vector<vector<long long>> A) {
    int n = (int) A.size();
    long long prev = 1;
    int sign = 1;
    for (int i = 0; i < n - 1; ++i) {
        // find non-zero cell
        if (A[i][i] == 0) {
            int k = -1;
            for (int j = i + 1; j < n; ++j) {
                if (A[j][i] != 0) {
                    k = i;
                    break;
                }
            }
            if (k == -1) return 0;
            swap(A[i], A[k]);
            sign = -sign;
        }
        for (int j = i + 1; j < n; ++j) {
            for (int k = i + 1; k < n; ++k) {
                assert((A[j][k] * A[i][i] - A[j][i] * A[i][k]) % prev == 0);
                A[j][k] = (A[j][k] * A[i][i] - A[j][i] * A[i][k]) / prev;
            }
        }
        prev = A[i][i];
    }
    return sign * A[n - 1][n - 1];
}