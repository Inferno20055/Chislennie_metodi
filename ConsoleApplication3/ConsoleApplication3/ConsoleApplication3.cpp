#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct CubicPolynomial {
    double a, b, c, d;
};

vector<double> solveTridiagonal(const vector<double>& a, const vector<double>& b, const vector<double>& c, const vector<double>& d) {
    int n = d.size();
    vector<double> x(n);
    vector<double> ac(n), bc(n), dc(n);
    ac[0] = a[0];
    bc[0] = b[0];
    dc[0] = d[0];
    for (int i = 1; i < n; i++) {
        double m = ac[i - 1] / bc[i - 1];
        bc[i] = b[i] - m * c[i - 1];
        dc[i] = d[i] - m * dc[i - 1];
        ac[i] = a[i];
    }
    x[n - 1] = dc[n - 1] / bc[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = (dc[i] - c[i] * x[i + 1]) / bc[i];
    }
    return x;
}
vector<CubicPolynomial> computeSplineCoefficients(const vector<double>& x, const vector<double>& y) {
    int n = x.size() - 1;
    vector<double> h(n);
    for (int i = 0; i < n; i++) {
        h[i] = x[i + 1] - x[i];
    }
    vector<double> a(n - 1), b(n - 1), c(n - 1), d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        a[i] = h[i];
        b[i] = 2 * (h[i] + h[i + 1]);
        c[i] = h[i + 1];
        d[i] = 3 * ((y[i + 2] - y[i + 1]) / h[i + 1] - (y[i + 1] - y[i]) / h[i]);
    }

    vector<double> m = solveTridiagonal(a, b, c, d);
    vector<double> secondDerivatives(n + 1);
    secondDerivatives[0] = 0;
    for (int i = 0; i < m.size(); i++) {
        secondDerivatives[i + 1] = m[i];
    }
    secondDerivatives[n] = 0;

    vector<CubicPolynomial> polynomials(n);
    for (int i = 0; i < n; ++i) {
        polynomials[i].a = (secondDerivatives[i + 1] - secondDerivatives[i]) / (6 * h[i]);
        polynomials[i].b = secondDerivatives[i] / 2;
        polynomials[i].c = (y[i + 1] - y[i]) / h[i] - h[i] * (2 * secondDerivatives[i] + secondDerivatives[i + 1]) / 6;
        polynomials[i].d = y[i];

    }

    return polynomials;
}

double interpolate(const vector<CubicPolynomial>& polynomials, const vector<double>& x, double t) {
    int n = x.size() - 1;
    if (t < x[0] || t > x[n]) {
        
        return NAN; 
    }

    int i = 0;
    while (i < n && t > x[i + 1]) {
        ++i;
    }

    double dx = t - x[i];
    return polynomials[i].a * pow(dx, 3) + polynomials[i].b * pow(dx, 2) + polynomials[i].c * dx + polynomials[i].d;
}

int main() {
    setlocale(LC_ALL,"Ru");
    vector<double> x = { 0, 1, 2, 3, 4 };
    vector<double> y = { 1, 3, 2, 4, 0 };
    vector<CubicPolynomial> polynomials = computeSplineCoefficients(x, y);

    for (double t = 0.0; t <= 4.0; t += 0.5) {
        double interpolatedValue = interpolate(polynomials, x, t);
        cout << "t = " << t << ", интерполированное значение = " << interpolatedValue << endl;
    }
    return 0;
}