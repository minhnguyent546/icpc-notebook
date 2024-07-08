/**
 * Description: computing determinant of a square matrix A by applying
 * Gauss elimination to produces a row echolon matrix B, then the
 * determinant of A is equal to product of the elements of the diagonal of B.
 * Time: $O(N^3)$.
 */

const double EPS = 1e-9;
double determinant(vector<vector<double>> A) {
    int n = (int) A.size();
    double det = 1;
    for (int i = 0; i < n; ++i) {
        // find non-zero cell
        int k = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(A[j][i]) > abs(A[k][i])) k = j;
        }
        if (abs(A[k][i]) < EPS) {
            det = 0;
            break;
        }
        if (i != k) {
            swap(A[i], A[k]);
            det = -det;
        }
        det *= A[i][i];
        for (int j = i + 1; j < n; ++j) {
            A[i][j] /= A[i][i];
        }
        for (int j = 0; j < n; ++j) {
            if (j != i && abs(A[j][i]) > EPS) {
                for (int k = i + 1; k < n; ++k) {
                    A[j][k] -= A[i][k] * A[j][i];
                }
            }
        }
    }
    return det;
}