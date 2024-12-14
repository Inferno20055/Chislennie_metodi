#include <iostream>
#include <cmath>
using namespace std;
const double EPSILON = 1e-6; 
double f_prime(double x) {
    return (2 / ((x + 7) * log(10))) - 5 * cos(x); 
}
double f(double x) {
    return 2 * log10(x + 7) - 5 * sin(x);
}
//метод комбинированных
double combinedMethod(double a, double b) {
    if (f(a) * f(b) >= 0) {
        cout << "Функция не изменяет знак на отрезке [" << a << ", " << b << "]\n";
        return NAN;
    }

    double x0 = a; 
    double x1 = b; 
    double x_next;

   
    while (true) {
        x_next = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));

        if (fabs(f(x_next)) < EPSILON || fabs(x_next - x1) < EPSILON) {
            break; 
        }

        x0 = x1;
        x1 = x_next;
    }

    double x_refined = x_next;
    while (true) {
        double derivative = f_prime(x_refined);
        if (fabs(derivative) < EPSILON) {
            cout << "Производная слишком мала, решить уравнение не удалось.\n";
            return NAN; 
        }

        double x_new = x_refined - f(x_refined) / derivative;

       
        if (fabs(f(x_new)) < EPSILON || fabs(x_new - x_refined) < EPSILON) {
            return x_new; 
        }

      
        x_refined = x_new;
    }
}
//метод касательных
void tangentMethod(double x0) {
    double x_next;

    while (true) {
      
        double derivative = f_prime(x0);
        if (fabs(derivative) < EPSILON) {
            cout << "Производная слишком мала, решить уравнение не удалось.\n";
            return;
        }
 
        x_next = x0 - f(x0) / derivative;
  
        if (fabs(f(x_next)) < EPSILON || fabs(x_next - x0) < EPSILON) {
            cout << "Приближенное значение x: " << x_next << "\n";
            return;
        }

        x0 = x_next;
    }
}
//метод хорды


void chordMethod(double a, double b) {
    if (f(a) * f(b) >= 0) {
        cout << "Функция не изменяет знак на отрезке [" << a << ", " << b << "]\n";
        return;
    }

    double x0 = a; 
    double x1 = b; 
    double x_next;

    while (true) {
        x_next = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));

        if (fabs(f(x_next)) < EPSILON || fabs(x_next - x1) < EPSILON) {
            cout << "Приближенное значение x: " << x_next << " на отрезке ["
                << a << ", " << b << "]\n";
            return;
        }

        x0 = x1;
        x1 = x_next;
    }
}
int main() {
    setlocale(LC_ALL, "Ru");
    cout << "Метод хорды"<<endl;
    cout << "Решение уравнения 2 lg(x + 7) - 5 sin(x) = 0\n";
    //примечание для себя: вводить до 10 чисел иначе программа не будет работать 
    double a1 = 2;
    double b1 = 7;
    chordMethod(a1, b1); 
    double a2 = 2;
    double b2 = 8;
    chordMethod(a2, b2);
    double a3 = 1;
    double b3 = 9;
    chordMethod(a3, b3);
    cout << endl;
    cout << "метод косательной"<<endl;
    //метод косательной
    double initial_guess1 = 3.0; // Начальная точка для интервала (2, 7)
    double initial_guess2 = 3.5; // Начальная точка для интервала (2, 8)
    cout << "Решение уравнения 2 lg(x + 7) - 5 sin(x) = 0\n";
    cout << "Поиск корня на интервале (2, 7):\n";
    tangentMethod(initial_guess1);
    cout << "Поиск корня на интервале (2, 8):\n";
    tangentMethod(initial_guess2);
    //комбинированный метод
    cout << endl;
    cout << "комбинированный метод хорд и касательных " << endl;
    cout << "Решение уравнения 2 lg(x + 7) - 5 sin(x) = 0\n";

    // Задаем интервал (2, 7)
    double a4 = 2.0;
    double b4 = 7.0;
    cout << "Поиск корня на интервале (2, 7):\n";
    double root1 = combinedMethod(a4, b4);
    if (!isnan(root1)) {
        cout << "Приближенное значение корня: " << root1 << "\n";
    }

    // Задаем интервал (2, 8)
    double a5 = 2.0;
    double b5 = 8.0;
    cout << "Поиск корня на интервале (2, 8):\n";
    double root2 = combinedMethod(a5, b5);
    if (!isnan(root2)) {
        cout << "Приближенное значение корня: " << root2 << "\n";
    }
    return 0; 
}




   