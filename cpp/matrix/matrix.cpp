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

std::size_t Matrix::rows() const {
    throw std::logic_error("not implemented");
}

std::size_t Matrix::cols() const {
    throw std::logic_error("not implemented");
}

double& Matrix::at(std::size_t, std::size_t) {
    throw std::logic_error("not implemented");
}

double Matrix::at(std::size_t, std::size_t) const {
    throw std::logic_error("not implemented");
}

bool operator==(const Matrix&, const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix operator+(const Matrix&, const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix operator-(const Matrix&, const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix operator*(double, const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix operator*(const Matrix&, double) {
    throw std::logic_error("not implemented");
}

Matrix transpose(const Matrix&) {
    throw std::logic_error("not implemented");
}

double trace(const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix operator*(const Matrix&, const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix power(const Matrix&, unsigned long long) {
    throw std::logic_error("not implemented");
}

double determinant(const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix rref(const Matrix&) {
    throw std::logic_error("not implemented");
}

std::size_t rank(const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix inverse(const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix solve(const Matrix&, const Matrix&) {
    throw std::logic_error("not implemented");
}

LU lu_decompose(const Matrix&) {
    throw std::logic_error("not implemented");
}

QR qr_decompose(const Matrix&) {
    throw std::logic_error("not implemented");
}

Matrix least_squares(const Matrix&, const Matrix&) {
    throw std::logic_error("not implemented");
}

std::vector<double> symmetric_eigenvalues(const Matrix&) {
    throw std::logic_error("not implemented");
}

}
