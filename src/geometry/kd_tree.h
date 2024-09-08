/**
 * Description: KD-tree searching for closest point to the given point, can also
 * be changed to find farthest point.
 * Source: KACTL
 * Time: average-case complexity is $O(3^d\log{N})$ where $d$ is the number of dimensions
 * Status: tested on https://judge.yosupo.jp/problem/closest_pair
 */

using T = long long;
const T INF = numeric_limits<T>::max();
struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0): x(_x), y(_y) {}
    T dist(const Point &other) const {
        T dx = x - other.x, dy = y - other.y;
        return dx * dx + dy * dy;
    }
    bool operator<(const Point &other) const { return tie(x, y) < tie(other.x, other.y); }
    bool operator==(const Point &other) const { return tie(x, y) == tie(other.x, other.y); }
};

bool comp_x(const Point &a, const Point &b) { return a.x < b.x; }
bool comp_y(const Point &a, const Point &b) { return a.y < b.y; }

struct Node {
    Point point; // a single point if this Node is a leaf
    T x_left = INF, x_right = -INF, y_left = INF, y_right = -INF;
    Node *first = nullptr, *second = nullptr; // two children of this node
    T dist(const Point &A) {
        // MIN squared distance between the point A and this box, 0 if inside
        // to compute MAX distance, calculate MAX distance from A to the
        // four corner points of this box
        T x = (A.x < x_left ? x_left : A.x > x_right ? x_right : A.x);
        T y = (A.y < y_left ? y_left : A.y > y_right ? y_right : A.y);
        return A.dist(Point(x, y));

        // MAX squared distance
        // T x, y;
        // if (A.x < x_left) x = x_right;
        // else if (A.x > x_right) x = x_left;
        // else x = A.x - x_left > x_right - A.x ? x_left : x_right;

        // if (A.y < y_left) y = y_right;
        // else if (A.y > y_right) y = y_left;
        // else y = A.y - y_left > y_right - A.y ? y_left : y_right;
        return A.dist(Point(x, y));
    }
    Node(vector<Point> &&points): point(points[0]) {
        for (auto &p : points) {
            x_left = min(x_left, p.x); x_right = max(x_right, p.x);
            y_left = min(y_left, p.y); y_right = max(y_right, p.y);
        }
        int sz = (int) points.size();
        if (sz > 1) {
            // split on x if width >= height (not ideal...)
            sort(points.begin(), points.end(), x_right - x_left >= y_right - y_left ? comp_x : comp_y);
            // divide by taking half the array for each child (not
            // best performance with many duplicates in the middle)
            int half = sz / 2;
            first = new Node({points.begin(), points.begin() + half});
            second = new Node({points.begin() + half, points.end()});
        }
    }
};

struct KDTree {
    Node *root;
    KDTree(const vector<Point> &points): root(new Node({points.begin(), points.end()})) {}
    pair<T, Point> search(Node *node, const Point &point) {
        if (!node->first) {
            // uncomment if we SHOULD NOT find the point itself
            // if (node->point == point) return pair{INF, Point{}};
            return pair{point.dist(node->point), node->point};
        }
        Node *first = node->first, *second = node->second;
        T bfirst = first->dist(point), bsecond = second->dist(point);
        if (bfirst > bsecond) swap(bfirst, bsecond), swap(first, second);

        // search closest side first, other side if needed
        auto best = search(first, point);
        if (bsecond < best.first) {
            best = min(best, search(second, point));
        }
        return best;
    }
    pair<T, Point> search(const Point &point) {
        return search(root, point);
    }
};
