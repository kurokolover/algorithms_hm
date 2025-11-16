#include <iomanip>
#include <iostream>
#include <random>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long double x1 = 1.0L, y1 = 1.0L, r1 = 1.0L;
    const long double x2 = 1.5L, y2 = 2.0L, r2 = sqrtl(5.0L) / 2.0L;
    const long double x3 = 2.0L, y3 = 1.5L, r3 = sqrtl(5.0L) / 2.0L;
    long long N;
    int mode;
    if (!(cin >> N >> mode)) return 0;

    long double xmin, xmax, ymin, ymax;
    if (mode == 0) {
        xmin = 0.0L;
        xmax = 3.0L;
        ymin = 0.0L;
        ymax = 3.0L;
    } else {
        xmin = 0.88L;
        xmax = 2.0L;
        ymin = 0.88L;
        ymax = 2.0L;
    }

    mt19937_64 rng(123456789);
    uniform_real_distribution<long double> distX(xmin, xmax);
    uniform_real_distribution<long double> distY(ymin, ymax);
    long long inside = 0;
    long double r1sq = r1 * r1;
    long double r2sq = r2 * r2;
    long double r3sq = r3 * r3;

    for (long long i = 0; i < N; ++i) {
        long double x = distX(rng);
        long double y = distY(rng);
        long double dx1 = x - x1, dy1 = y - y1;
        long double dx2 = x - x2, dy2 = y - y2;
        long double dx3 = x - x3, dy3 = y - y3;

        if (dx1 * dx1 + dy1 * dy1 <= r1sq &&
            dx2 * dx2 + dy2 * dy2 <= r2sq &&
            dx3 * dx3 + dy3 * dy3 <= r3sq) {
            ++inside;
        }
    }

    long double areaRect = (xmax - xmin) * (ymax - ymin);
    long double estimate = areaRect *
        (static_cast<long double>(inside) /
         static_cast<long double>(N));
    cout.setf(ios::fixed);
    cout << setprecision(10)
         << static_cast<double>(estimate) << '\n';
    return 0;
}
