/**
 * Source: https://github.com/icpcvn/icpcvn.github.io/blob/master/2017/
 * national/solutions/E/RR_ternary.cpp
 */

Point A, B, C;
double f(Point P) {
    return (P - A).len() + (P - B).len() + (P - C).len();
}
double f(double x, double& y) {
    double l = -2000, r = 2000;
    for (int i = 0; i < 500; ++i) {
        double y1 = (l * 2 + r) / 3.0;
        double y2 = (l + r * 2) / 3.0;

        double f1 = f(Point(x, y1));
        double f2 = f(Point(x, y2));

        if (f1 < f2) r = y2;
        else l = y1;
    }
    y = (l + r) / 2.0;
    return f(Point(x, y));
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(9) << boolalpha;
    cin >> A >> B >> C;

    double l = -2000, r = 2000;
    for (int i = 0; i < 500; ++i) {
        double x1 = (l * 2 + r) / 3.0;
        double x2 = (l + r * 2) / 3.0;

        double y;
        double f1 = f(x1, y);
        double f2 = f(x2, y);

        if (f1 < f2) r = x2;
        else l = x1;
    }
    double y;
    f(l, y);
    cout << l << ' ' << y << '\n';
    return 0;
}

