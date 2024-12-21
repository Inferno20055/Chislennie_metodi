#include <iostream>
#include <cmath> 

using namespace std;

void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout.precision(2);
            cout << fixed << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------------" << endl;
}

// Функция для решения системы методом Гаусса
double* gauss(double** A, double* b, int n) {
   
    double** extendedMatrix = new double* [n];
    for (int i = 0; i < n; ++i) {
        extendedMatrix[i] = new double[n + 1];
        for (int j = 0; j < n; ++j) {
            extendedMatrix[i][j] = A[i][j];
        }
        extendedMatrix[i][n] = b[i];
    }

    // Прямой ход (Элиминация)
    for (int i = 0; i < n; i++) {
       
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(extendedMatrix[k][i]) > fabs(extendedMatrix[maxRow][i])) {
                maxRow = k;
            }
        }
        if (maxRow != i) { 
            double* temp = extendedMatrix[i];
            extendedMatrix[i] = extendedMatrix[maxRow];
            extendedMatrix[maxRow] = temp;
        }
        if (fabs(extendedMatrix[i][i]) < 1e-9) {
            cout << "Система не имеет единственного решения или бесконечное множество решений." << endl;
            for (int i = 0; i < n; ++i) {
                delete[] extendedMatrix[i];
            }
            delete[] extendedMatrix;
            return nullptr; 
        }

        for (int k = i + 1; k < n; k++) {
            double factor = extendedMatrix[k][i] / extendedMatrix[i][i];
            for (int j = i; j <= n; j++) {
                extendedMatrix[k][j] -= factor * extendedMatrix[i][j];
            }
        }
    }
   //обратный ход
    double* solutions = new double[n];
    for (int i = n - 1; i >= 0; i--) {
        solutions[i] = extendedMatrix[i][n];
        for (int j = i + 1; j < n; j++) {
            solutions[i] -= extendedMatrix[i][j] * solutions[j];
        }
        solutions[i] /= extendedMatrix[i][i];
    }
    for (int i = 0; i < n; ++i) {
        delete[] extendedMatrix[i];
    }
    delete[] extendedMatrix;
    return solutions;
}

int main() {

    // Пример 1 
    // системы 3x3
    setlocale(LC_ALL, "Ru");
    cout << "Система 3x3:" << endl;
    int n = 3;
    double** A = new double* [n];
    for (int i = 0; i < n; ++i) {
        A[i] = new double[n];
    }
    A[0][0] = 2; A[0][1] = 1; A[0][2] = -1;
    A[1][0] = -3; A[1][1] = -1; A[1][2] = 2;
    A[2][0] = -2; A[2][1] = 1; A[2][2] = 2;
    double* b = new double[n];
    b[0] = 8; b[1] = -11; b[2] = -3;

    double* result = gauss(A, b, n);
    if (result != nullptr) {
        cout << "x = " << result[0] << ", y = " << result[1] << ", z = " << result[2] << endl;
        delete[] result;
    }


    cout << endl;

    // Пример 2 
    // системы 2x2
    cout << "Система 2x2:" << endl;
    int n2 = 2;
    double** A2 = new double* [n2];
    for (int i = 0; i < n2; ++i) {
        A2[i] = new double[n2];
    }
    A2[0][0] = 1; A2[0][1] = 2;
    A2[1][0] = 3; A2[1][1] = 4;
    double* b2 = new double[n2];
    b2[0] = 5; b2[1] = 6;

    double* result2 = gauss(A2, b2, n2);
    if (result2 != nullptr) {
        cout << "x = " << result2[0] << ", y = " << result2[1] << endl;
        delete[] result2;
    }
    cout  << endl;

    // Пример 3
    // системы с вырожденной матрицей
    cout << "Система с нулевым определителем:" << endl;
    int n_singular = 2;
    double** A_singular = new double* [n_singular];
    for (int i = 0; i < n_singular; ++i) {
        A_singular[i] = new double[n_singular];
    }
    A_singular[0][0] = 1; A_singular[0][1] = 2;
    A_singular[1][0] = 2; A_singular[1][1] = 4;
    double* b_singular = new double[n_singular];
    b_singular[0] = 3; b_singular[1] = 6;

    double* result_singular = gauss(A_singular, b_singular, n_singular);


    for (int i = 0; i < n; ++i) {
        delete[] A[i];
    }
    delete[] A;
    delete[] b;
    for (int i = 0; i < n2; ++i) {
        delete[] A2[i];
    }
    delete[] A2;
    delete[] b2;
    for (int i = 0; i < n_singular; ++i) {
        delete[] A_singular[i];
    }
    delete[] A_singular;
    delete[] b_singular;

    return 0;
}