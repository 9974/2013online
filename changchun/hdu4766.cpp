#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-6;
inline int dcmp(double x) {
    if (fabs(x) < eps)
        return x;
    return x > eps ? 1 : -1;
}
struct point {
    double x, y;
    inline point(double x, double y) :
            x(x), y(y) {
    }
    point(){}
    inline point operator-(const point &t) const {
        return point(x - t.x, y - t.y);
    }
    inline point operator+(const point &t) const {
        return point(x + t.x, y + t.y);
    }
    inline point operator*(const double &t) const {
        return point(x * t, y * t);
    }
   inline  point operator/(const double &t) const {
        return point(x/t, y/t);
    }
    double len() {
        return sqrt(x * x + y * y);
    }
    inline point normal() {
        return point(-y, x) / len();
    }
    bool operator==(const point &t) const {
        return !dcmp(x - t.x) && !dcmp(y - t.y);
    }
} o, p[1013];
double r;
int n;
double dis(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double dis2(point a, point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline bool cal(point a) {
    for (int i = 0; i < n; i++)
        if (dis(a, p[i]) > r + eps)
            return 0;
    return 1;
}
int main() {
    int i, j, k;
    while (~scanf("%lf%lf%lf%d", &o.x, &o.y, &r, &n)) {
        for (i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        bool ok = 1;
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++)
                if (dis(p[i], p[j]) > 2 * r + eps) {
                    ok = 0;
                    goto loop;
                }
        loop:
        if (!ok) {
            puts("X");
            continue;
        }

        if (cal(o)) {
            puts("0.00");
            continue;
        }


        double ans = 1e17;
        ok = 0;
        for (i = 0; i < n; i++) {
            point tp = p[i] + (o-p[i])  *(r/(p[i] - o).len());
            double val = dis(tp, o);
            if (val < ans && cal(tp)) {
                ok = 1;
                ans = val;
            }
        }
        double d, val;
        point m, tp, N;
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++) {
                if(p[i]== p[j]) continue;
                //    puts("~~~");
                m = (p[i] + p[j]) * 0.5;
                N = (p[i] - p[j]).normal();

                d = sqrt(r * r - dis2(m, p[i]));
                tp = m + N * d;
                val = dis(tp, o);
                if (val +eps < ans && cal(tp)) {
                    ans = val;
                    ok = 1;
                }
                tp = m - N * d;
                val = dis(tp, o);
                if (val +eps < ans && cal(tp)) {
                    ans = val;
                    ok = 1;
                }

            }
        if (ok)
            printf("%.2f\n", ans);
        else
            puts("X");
    }
    return 0;
}