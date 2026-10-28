#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace linalg {

inline constexpr double kEpsilon = 1e-9;

class Matrix {
public:
    Matrix(std::size_t rows, std::size_t cols);

    Matrix(std::initializer_list<std::initializer_list<double>> rows);

    static Matrix identity(std::size_t n);

    std::size_t rows();
    std::size_t cols();

    double& at(std::size_t row, std::size_t col);

private:
};

bool operator==(Matrix a, Matrix b);

Matrix operator+(Matrix a, Matrix b);
Matrix operator-(Matrix a, Matrix b);

Matrix operator*(double scalar, Matrix m);
Matrix operator*(Matrix m, double scalar);

Matrix transpose(Matrix m);

double trace(Matrix m);

Matrix operator*(Matrix a, Matrix b);

Matrix power(Matrix m, unsigned long long exponent);

double determinant(Matrix m);

Matrix rref(Matrix m);

std::size_t rank(Matrix m);

Matrix inverse(Matrix m);

Matrix solve(Matrix a, Matrix b);

struct LU {
    Matrix p;
    Matrix l;
    Matrix u;
};

LU lu_decompose(Matrix m);

struct QR {
    Matrix q;
    Matrix r;
};

QR qr_decompose(Matrix m);

Matrix least_squares(Matrix a, Matrix b);

std::vector<double> symmetric_eigenvalues(Matrix m);

}

#endif
