int st[MAXN][K + 1];
for (int i = 0; i < N; i++) {
    st[i][0] = f(array[i]);
}
for (int j = 1; j <= K; j++) {
    for (int i = 0; i + (1 << j) <= N; i++) {
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}
// Range Minimum Queries.
int lg[MAXN + 1];
lg[1] = 0;
for (int i = 2; i <= MAXN; i++) {
    lg[i] = lg[i / 2] + 1;
}
int j = lg[R - L + 1];
int minimum = min(st[L][j], st[R - (1 << j) + 1][j]);
// Range Sum Queries.
long long sum = 0;
for (int j = K; j >= 0; j--) {
    if ((1 << j) <= R - L + 1) {
        sum += st[L][j];
        L += 1 << j;
    }
}
