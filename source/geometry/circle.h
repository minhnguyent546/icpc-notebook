int insideCircle(const point& p, const point& center, ftype r) {
    ftype d = norm(p - center);
    ftype rSq = r * r;
    return fabs(d - rSq) < EPS ? 0 : (d - rSq >= EPS ? 1 : -1);
}
bool circle2PointsR(const point& p1, const point& p2, ftype r, point& c) {
    double h = r * r - norm(p1 - p2) / 4.0;
    if (fabs(h) < 0) return false;
    h = sqrt(h);
    point perp = (p2 - p1).rotate(PI / 2.0);
    point m = (p1 + p2) / 2.0;
    c = m + perp * (h / abs(perp));
    return true;
}