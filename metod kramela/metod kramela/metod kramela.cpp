#include <iostream>
#include <cmath> 

using namespace std;

// Функция для вычисления определителя матрицы
double determinant(double** matrix, int n) {
    if (n == 1) return matrix[0][0];
    if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double det = 0;
    for (int p = 0; p < n; p++) {
        double** subMatrix = new double* [n - 1];
        for (int i = 0; i < n - 1; ++i) {
            subMatrix[i] = new double[n - 1];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j < p) subMatrix[i - 1][j] = matrix[i][j];
                else if (j > p) subMatrix[i - 1][j - 1] = matrix[i][j];
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * matrix[0][p] * determinant(subMatrix, n - 1);

      
        for (int i = 0; i < n - 1; ++i) {
            delete[] subMatrix[i];
        }
        delete[] subMatrix;
    }
    return det;
}

// Функция для решения системы уравнений методом Крамера
void cramer(double** matrix, double* b, int n) {
    double det = determinant(matrix, n);

    if (fabs(det) < 1e-9) {
        cout << "Система не имеет единственного решения." << endl;
        return;
    }

    double* solutions = new double[n];

    for (int i = 0; i < n; i++) {
        double** tempMatrix = new double* [n];
        for (int j = 0; j < n; ++j) {
            tempMatrix[j] = new double[n];
            for (int k = 0; k < n; k++) {
                tempMatrix[j][k] = matrix[j][k];
            }
        }
        for (int j = 0; j < n; j++) {
            tempMatrix[j][i] = b[j]; 
        }
        solutions[i] = determinant(tempMatrix, n) / det;
        for (int j = 0; j < n; ++j) {
            delete[] tempMatrix[j];
        }
        delete[] tempMatrix;
    }
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << solutions[i] << endl;
    }
    delete[] solutions;

}

int main() {
    setlocale(LC_ALL, "Ru");
   
    int n = 3;
    double** matrix = new double* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[n];
    }
    //для изминения матрицы  размерностью 3 х 3.
    matrix[0][0] = 2; matrix[0][1] = 3; matrix[0][2] = 9;
    matrix[1][0] = 2; matrix[1][1] = 1; matrix[1][2] = 4;
    matrix[2][0] = 0; matrix[2][1] = 2; matrix[2][2] = 3;

    double* b = new double[n];
    b[0] = 1; b[1] = 2; b[2] = 3;


    cramer(matrix, b, n);


   
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] b;
    return 0;
}