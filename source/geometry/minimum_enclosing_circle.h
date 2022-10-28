/**
 * Description: computes the minimum circle that encloses all the given points. 
 */
double abs(point a) { return sqrt(a.X * a.X + a.Y * a.Y); }

point center_from(double bx, double by, double cx, double cy) {
    double B = bx * bx + by * by, C = cx * cx + cy * cy, D = bx * cy - by * cx;
    return point((cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D));
}

circle circle_from(point A, point B, point C) {
    point I = center_from(B.X - A.X, B.Y - A.Y, C.X - A.X, C.Y - A.Y);
    return circle(I + A, abs(I));
}

const int N = 100005;
int n, x[N], y[N];
point a[N];

circle emo_welzl(int n, vector<point> T) {
    if (T.size() == 3 || n == 0) {
        if (T.size() == 0) return circle(point(0, 0), -1);
        if (T.size() == 1) return circle(T[0], 0);
        if (T.size() == 2) return circle((T[0] + T[1]) / 2, abs(T[0] - T[1]) / 2);
        return circle_from(T[0], T[1], T[2]);
    }
    random_shuffle(a + 1, a + n + 1);
    circle Result = emo_welzl(0, T);
    for (int i = 1; i <= n; i++)
        if (abs(Result.X - a[i]) > Result.Y + 1e-9) {
            T.push_back(a[i]);
            Result = emo_welzl(i - 1, T);
            T.pop_back();
        }
    return Result;
}