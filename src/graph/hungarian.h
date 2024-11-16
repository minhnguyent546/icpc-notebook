/**
 * Description: Hungarian algorithm for solving the assignment problem:
 * there are $n$ jobs and $m >= n$ workers. Each worker specifies
 * the amount of money they expect for a particular job.
 * Each worker can be assigned to only one job. The objective is to assign jobs
 * to workers in a way that minimizes the total cost.
 * Status: tested on https://judge.yosupo.jp/problem/assignment
 * Time: $O(N^2M)$.
 */

const long long INF = 0x3f3f3f3f3f3f3f3f;
void solve_assignment_problem(const vector<vector<int>> &A) {
    // NOTE: all are 1-indexed
    int n = A.size() - 1, m = A[0].size() - 1;
    vector<int> u(n + 1), perm(m + 1), way(m + 1);
    vector<long long> v(m + 1);
    for (int i = 1; i <= n; ++i) {
        perm[0] = i;
        int j0 = 0;
        vector<long long> min_v(m + 1, INF);
        vector<bool> used(m + 1);
        do {
            used[j0] = true;
            int i0 = perm[j0], j1;
            long long delta = INF;
            for (int j = 1; j <= m; ++j) {
                if (used[j]) continue;
                int cur = A[i0][j] - u[i0] - v[j];
                if (cur < min_v[j]) {
                    min_v[j] = cur; way[j] = j0;
                }
                if (min_v[j] < delta) {
                    delta = min_v[j]; j1 = j;
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[perm[j]] += delta;
                    v[j] -= delta;
                } else {
                    min_v[j] -= delta;
                }
            }
            j0 = j1;
        } while (perm[j0] != 0);
        do {
            int j1 = way[j0];
            perm[j0] = perm[j1];
            j0 = j1;
        } while (j0 > 0);
    }
    vector<int> ans(n + 1);
    for (int j = 1; j <= m; ++j) {
        ans[perm[j]] = j;
    }

    long long cost = -v[0];
    cout << cost << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " \n"[i == n];
    }
}
