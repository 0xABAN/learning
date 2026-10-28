#include "matrix.h"

#include <stdexcept>

namespace linalg {

/* ------------------------------------------------------------------------- */
/* Level 1: the Matrix type                                                  */
/* ------------------------------------------------------------------------- */

Matrix::Matrix(std::size_t /*rows*/, std::size_t /*cols*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> /*rows*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix Matrix::identity(std::size_t /*n*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

std::size_t Matrix::rows() const {
    // TODO: implement
    throw std::logic_error("not implemented");
}

std::size_t Matrix::cols() const {
    // TODO: implement
    throw std::logic_error("not implemented");
}

double& Matrix::at(std::size_t /*row*/, std::size_t /*col*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

double Matrix::at(std::size_t /*row*/, std::size_t /*col*/) const {
    // TODO: implement
    throw std::logic_error("not implemented");
}

bool operator==(const Matrix& /*a*/, const Matrix& /*b*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 2: entry-wise operations                                            */
/* ------------------------------------------------------------------------- */

Matrix operator+(const Matrix& /*a*/, const Matrix& /*b*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix operator-(const Matrix& /*a*/, const Matrix& /*b*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix operator*(double /*scalar*/, const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix operator*(const Matrix& /*m*/, double /*scalar*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix transpose(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

double trace(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 3: multiplication and powers                                        */
/* ------------------------------------------------------------------------- */

Matrix operator*(const Matrix& /*a*/, const Matrix& /*b*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix power(const Matrix& /*m*/, unsigned long long /*exponent*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 4: determinants                                                     */
/* ------------------------------------------------------------------------- */

double determinant(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 5: row reduction and rank                                           */
/* ------------------------------------------------------------------------- */

Matrix rref(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

std::size_t rank(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 6: inverses and linear systems                                      */
/* ------------------------------------------------------------------------- */

Matrix inverse(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix solve(const Matrix& /*a*/, const Matrix& /*b*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 7: LU decomposition                                                 */
/* ------------------------------------------------------------------------- */

LU lu_decompose(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 8: QR decomposition and least squares                               */
/* ------------------------------------------------------------------------- */

QR qr_decompose(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

Matrix least_squares(const Matrix& /*a*/, const Matrix& /*b*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

/* ------------------------------------------------------------------------- */
/* Level 9: eigenvalues of symmetric matrices                                */
/* ------------------------------------------------------------------------- */

std::vector<double> symmetric_eigenvalues(const Matrix& /*m*/) {
    // TODO: implement
    throw std::logic_error("not implemented");
}

}  // namespace linalg
