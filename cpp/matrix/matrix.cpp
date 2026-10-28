#include "matrix.h"

#include <stdexcept>

namespace linalg {

Matrix::Matrix(std::size_t, std::size_t) {
    throw std::logic_error("not implemented");
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>>) {
    throw std::logic_error("not implemented");
}

Matrix Matrix::identity(std::size_t) {
    throw std::logic_error("not implemented");
}

std::size_t Matrix::rows() {
    throw std::logic_error("not implemented");
}

std::size_t Matrix::cols() {
    throw std::logic_error("not implemented");
}

double& Matrix::at(std::size_t, std::size_t) {
    throw std::logic_error("not implemented");
}

bool operator==(Matrix, Matrix) {
    throw std::logic_error("not implemented");
}

Matrix operator+(Matrix, Matrix) {
    throw std::logic_error("not implemented");
}

Matrix operator-(Matrix, Matrix) {
    throw std::logic_error("not implemented");
}

Matrix operator*(double, Matrix) {
    throw std::logic_error("not implemented");
}

Matrix operator*(Matrix, double) {
    throw std::logic_error("not implemented");
}

Matrix transpose(Matrix) {
    throw std::logic_error("not implemented");
}

double trace(Matrix) {
    throw std::logic_error("not implemented");
}

Matrix operator*(Matrix, Matrix) {
    throw std::logic_error("not implemented");
}

Matrix power(Matrix, unsigned long long) {
    throw std::logic_error("not implemented");
}

double determinant(Matrix) {
    throw std::logic_error("not implemented");
}

Matrix rref(Matrix) {
    throw std::logic_error("not implemented");
}

std::size_t rank(Matrix) {
    throw std::logic_error("not implemented");
}

Matrix inverse(Matrix) {
    throw std::logic_error("not implemented");
}

Matrix solve(Matrix, Matrix) {
    throw std::logic_error("not implemented");
}

LU lu_decompose(Matrix) {
    throw std::logic_error("not implemented");
}

QR qr_decompose(Matrix) {
    throw std::logic_error("not implemented");
}

Matrix least_squares(Matrix, Matrix) {
    throw std::logic_error("not implemented");
}

std::vector<double> symmetric_eigenvalues(Matrix) {
    throw std::logic_error("not implemented");
}

}
