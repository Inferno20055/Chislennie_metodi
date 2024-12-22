#include <iostream>
#include <cmath>   

using namespace std;
//метод ньютона
double newton(double initialGuess,
    double tolerance,
    int maxIterations,
    double (*f)(double),
    double (*df)(double)) {
    double x = initialGuess;
    for (int i = 0; i < maxIterations; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (abs(dfx) < 1e-9) {
            cout << "Производная близка к нулю, метод не сходится." << endl;
            return NAN; 
        }
        double x_next = x - fx / dfx;

        if (abs(x_next - x) < tolerance) {
            cout << "Найдено решение на итерации: " << i + 1 << endl;
            return x_next; 
        }
        x = x_next;
    }
    cout << "Метод не сошелся за " << maxIterations << " итераций." << endl;
    return NAN; 
}


// Пример 1: x^3 - 2x - 5 = 0
double f1(double x) { return x * x * x - 2 * x - 5; }
double df1(double x) { return 3 * x * x - 2; }

// Пример 2: x^2 - 2 = 0
double f2(double x) { return x * x - 2; }
double df2(double x) { return 2 * x; }

// Пример 3: x^2 = 0
double f3(double x) { return x * x; }
double df3(double x) { return 2 * x; }
//metod Лагранжа
// Функция для вычисления базисного многочлена Лагранжа Li(x)
double lagrangeBasis(double x, int i, double* x_values, int n) {
    double result = 1.0;
    for (int j = 0; j < n; ++j) {
        if (i != j) {
            if (abs(x_values[i] - x_values[j]) < 1e-9) {
                return 0.0;
            }
            result *= (x - x_values[j]) / (x_values[i] - x_values[j]);
        }
    }
    return result;
}


// Функция для вычисления значения интерполяционного многочлена Лагранжа P(x)
double lagrangeInterpolation(double x, double* x_values, double* y_values, int n) {
    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        result += y_values[i] * lagrangeBasis(x, i, x_values, n);
    }
    return result;
}

int main() {
    setlocale(LC_ALL,"Ru");
   /* int n1 = 4;
    double x_values1[] = { 0, 1, 2, 3 };
    double y_values1[] = { 1, 2, 5, 10 };

    double x1 = 1.5;

   
    double result1 = lagrangeInterpolation(x1, x_values1, y_values1, n1);
    cout.precision(2);
    cout << "Интерполированное значение в точке x = " << fixed << x1 << " равно: " << result1 << endl;


    int n2 = 3;
    double x_values2[] = { 1, 2, 3 };
    double y_values2[] = { 3, 7, 13 };
    double x2 = 2.5;
    double result2 = lagrangeInterpolation(x2, x_values2, y_values2, n2);
    cout.precision(2);
    cout << "Интерполированное значение в точке x = " << fixed << x2 << " равно: " << result2 << endl;


    int n3 = 3;
    double x_values3[] = { 1, 1, 3 };
    double y_values3[] = { 3, 7, 13 };
    double x3 = 2;
    double result3 = lagrangeInterpolation(x3, x_values3, y_values3, n3);
    cout.precision(2);
    cout << "Интерполированное значение в точке x = " << fixed << x3 << " равно: " << result3 << endl;
    */
    double initialGuess1 = 2.0;
    double tolerance1 = 1e-6;
    int maxIterations1 = 100;

    double root1 = newton(initialGuess1, tolerance1, maxIterations1, f1, df1);
    if (!isnan(root1)) {
        cout.precision(10);
        cout << "Корень уравнения 1: " << fixed << root1 << endl;
        cout.precision(10);
        cout << "Значение функции в корне 1: " << fixed << f1(root1) << endl;
    }

    cout << endl;
    // Пример 2
    double initialGuess2 = 1.0;
    double tolerance2 = 1e-6;
    int maxIterations2 = 100;

    double root2 = newton(initialGuess2, tolerance2, maxIterations2, f2, df2);
    if (!isnan(root2)) {
        cout.precision(10);
        cout << "Корень уравнения 2: " << fixed << root2 << endl;
        cout.precision(10);
        cout << "Значение функции в корне 2: " << fixed << f2(root2) << endl;
    }
    cout << endl;
    // Пример 3
    double initialGuess3 = 0;
    double tolerance3 = 1e-6;
    int maxIterations3 = 100;
    double root3 = newton(initialGuess3, tolerance3, maxIterations3, f3, df3);
    return 0;


}