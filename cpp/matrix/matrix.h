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

    std::size_t rows() const;
    std::size_t cols() const;

    double& at(std::size_t row, std::size_t col);
    double at(std::size_t row, std::size_t col) const;

private:
};

bool operator==(const Matrix& a, const Matrix& b);

Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);

Matrix operator*(double scalar, const Matrix& m);
Matrix operator*(const Matrix& m, double scalar);

Matrix transpose(const Matrix& m);

double trace(const Matrix& m);

Matrix operator*(const Matrix& a, const Matrix& b);

Matrix power(const Matrix& m, unsigned long long exponent);

double determinant(const Matrix& m);

Matrix rref(const Matrix& m);

std::size_t rank(const Matrix& m);

Matrix inverse(const Matrix& m);

Matrix solve(const Matrix& a, const Matrix& b);

struct LU {
    Matrix p;
    Matrix l;
    Matrix u;
};

LU lu_decompose(const Matrix& m);

struct QR {
    Matrix q;
    Matrix r;
};

QR qr_decompose(const Matrix& m);

Matrix least_squares(const Matrix& a, const Matrix& b);

std::vector<double> symmetric_eigenvalues(const Matrix& m);

}

#endif
