/**
 * Description: Dinic is a algorithm for solving maximum flow in $O(V^2E)$
 * Time: $O(V^2E)$.
 * Status: NOT tested
 */

struct Dinic {
    using ll = long long;
    int n, num_edge = 0;
    vector<int> point, head, next, dis, ptr;
    vector<ll> flow, cap;
    const ll flow_inf = (ll) 1e18;

    Dinic (int _n = 0) {
        n = _n;
        head.assign(n + 10, -1);
        ptr.assign(n + 10, -1);
        dis.assign(n + 10, 0);
    }

    void add_edge(int u, int v, ll c1, ll c2 = 0) {
        point.push_back(v);
        flow.push_back(0);
        cap.push_back(c1);
        next.push_back(head[u]);
        head[u] = num_edge++;

        point.push_back(u);
        flow.push_back(0);
        cap.push_back(c2);
        next.push_back(head[v]);
        head[v] = num_edge++;
    }

    int bfs(int s, int t) {
        queue<int> q;
        for (int i = 0; i <= n; i++)
            dis[i] = -1;

        dis[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = head[u]; i >= 0; i = next[i]) {
                int v = point[i];
                if (flow[i] < cap[i] && dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    if (v == t)
                        return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    int dfs(int u, int t, ll bottleneck) {
        if (bottleneck == 0)
            return bottleneck;
        if (u == t)
            return bottleneck;

        for (int &cid = ptr[u]; cid >= 0; cid = next[cid]) {
            int v = point[cid];
            if (flow[cid] < cap[cid] && dis[v] == dis[u] + 1) {
                ll mf = dfs(v, t, min(bottleneck, cap[cid] - flow[cid]));
                if (mf > 0) {
                    flow[cid] += mf;
                    flow[cid ^ 1] -= mf;
                    return mf;
                }
            }
        }
        return 0;
    }

    ll max_flow(int s, int t) {
        ll mf = 0;
        while (bfs(s, t)) {
            for (int i = 0; i <= n; i++)
                ptr[i] = head[i];
            while (true) {
                ll bottleneck = dfs(s, t, flow_inf);
                if (bottleneck == 0)
                    break;
                mf += bottleneck;
            }
        }
        return mf;
    }
};
