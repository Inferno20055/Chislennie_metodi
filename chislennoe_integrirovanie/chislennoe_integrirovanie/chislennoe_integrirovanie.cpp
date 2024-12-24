#include <iostream>
#include <cmath>

using namespace std;

// Пример функции 
double f(double x) {
    return x * x; 
}

// Метод трапеций для численного интегрирования
double trapezoidalRule(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double integral = 0.5 * (func(a) + func(b)); 

    for (int i = 1; i < n; i++) {
        integral += func(a + i * h); 
    }

    integral *= h; 
    return integral;
}

int main() {
    setlocale(LC_ALL,"Ru");
    double a, b;
    int n;

    cout << "Введите нижний предел интегрирования (a): ";
    cin >> a;
    cout << "Введите верхний предел интегрирования (b): ";
    cin >> b;
    cout << "Введите количество подинтервалов (n): ";
    cin >> n;

    double result = trapezoidalRule(f, a, b, n);
    cout << "Приближенное значение интеграла: " << result << endl;

    return 0;
}