using matrix_type = int;
const int MOD = (int) 1e9 + 7;
struct Matrix {
    static const matrix_type INF = numeric_limits<matrix_type>::max();
    int N, M;
    vector<vector<matrix_type>> mat;
    
    Matrix(int _N, int _M, matrix_type v = 0) : N(_N), M(_M) {
        mat.assign(N, vector<matrix_type>(M, v));
    }
    static Matrix identity(int n) { // return identity matrix. 
        Matrix I(n, n);
        for (int i = 0; i < n; ++i) {
            I[i][i] = 1;
        }
        return I;
    }

    vector<matrix_type>& operator[](int r) { return mat[r]; }
    const vector<matrix_type>& operator[](int r) const { return mat[r]; }
    
    Matrix& operator*=(const Matrix &other) {
        assert(M == other.N); // [N x M] [other.N x other.M]
        Matrix res(N, other.M);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < other.M; ++c) {
                long long square_mod = (long long) MOD * MOD;
                long long sum = 0;
                for (int g = 0; g < M; ++g) {
                    sum += (long long) mat[r][g] * other[g][c];
                    if (sum >= square_mod) sum -= square_mod;
                }
                res[r][c] = sum % MOD;
            }
        }
        mat.swap(res.mat); return *this;
    }
};
