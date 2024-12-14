#include <iostream>
#include <cmath>
using namespace std;

const double TARGET_VALUE = pow(0.2,3); //для изминения чисел
const double PI = 3.14; 
const double EPSILON = 1e-6; 
const int MAX_ITERATIONS = 10000;
//метод простых итераций

double g(double x) {
    return acos(TARGET_VALUE);
}
void simpleIteration(double& initialGuess) {
    double x = initialGuess; 
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        double x_new = g(x); 
        
        if (fabs(x_new - x) < EPSILON) {
            cout << "Приближенное значение x: " << x_new << " радиан" << endl;
            return;
        }
        x = x_new; 
    }
    cout << "Метод не сошелся за " << MAX_ITERATIONS << " итераций." << endl;
}
//метод половинного деления
double f(double x) {
    return cos(x) - TARGET_VALUE;
}
void bisectionMethod(double a, double b) {
    if (f(a) * f(b) >= 0) {
        cout << "Функция не изменяет знак на данном интервале." << endl;
        return;
    }

    double c;
    while ((b - a) >= EPSILON) {
        c = (a + b) / 2; 
        if (f(c) == 0.0) 
            break;
        else if (f(c) * f(a) < 0) 
            b = c;
        else 
            a = c;
    }

    cout << "Приближенное значение x: " << c << " радиан" << endl;
}
int main()
{
    setlocale(LC_ALL,"Ru");
    
    //метод простых итераций
    cout << "Решение уравнения с помощью метода половинного деления. " << endl;//для примера числа 0.2 и 3
    double a = 0; 
    double b = PI / 2; 

    bisectionMethod(a, b);
    //метод простых итераций 
    cout << "Решение уравнения с помощью метода простых итераций." << endl;
    double initialGuess = 0.0; 
    simpleIteration(initialGuess); 
    return 0; 
}
