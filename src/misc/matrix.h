const int MOD = (int) 1e9 + 7;
const long long SMOD = 1LL * MOD * MOD;

template<typename T> struct Matrix {
    int N, M;
    vector<vector<T>> mat;
    Matrix(int _N, int _M, T v = 0) : N(_N), M(_M) {
        mat.assign(N, vector<T>(M, v));
    }
    static Matrix identity(int n) { // return identity matrix. 
        Matrix I(n, n);
        for (int i = 0; i < n; ++i) I[i][i] = 1;
        return I;
    }
    vector<T>& operator[](int r) { return mat[r]; }
    const vector<T>& operator[](int r) const { return mat[r]; }
    Matrix& operator*=(const Matrix &other) {
        assert(M == other.N); // [N x M] [other.N x other.M]
        Matrix res(N, other.M);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < other.M; ++c) {
                long long sum = 0;
                for (int g = 0; g < M; ++g) {
                    sum += (long long) mat[r][g] * other[g][c];
                    if (sum >= SMOD) sum -= SMOD;
                }
                res[r][c] = sum % MOD;
            }
        }
        mat.swap(res.mat); return *this;
    }
    friend Matrix powmod(Matrix a, long long e) {
        assert(a.N == a.M);
        Matrix res = Matrix::identity(a.N);
        while (e > 0) {
            if (e & 1) res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
};
