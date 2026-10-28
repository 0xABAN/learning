#ifndef MATRIX_H
#define MATRIX_H

/*
 * Matrix algebra exercises in nine levels of increasing difficulty. Implement
 * each level in matrix.cpp, then build and run the tests:
 *
 *     c++ -std=c++23 -g -Wall -Wextra -fsanitize=address,undefined \
 *         matrix.cpp matrix_tests.cpp -o matrix_tests && ./matrix_tests
 *
 * Pass a level to run only its tests, e.g. ./matrix_tests 3.
 *
 * Every matrix has at least one row and one column, and its entries are
 * doubles. Rows and columns are numbered from 0. The tests accept results
 * within 1e-9 of the exact value, or within a relative error of 1e-9 when the
 * exact value is larger than 1 in magnitude.
 */

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace linalg {

/* Levels 5, 6, 8 and 9 treat values whose magnitude is below this as zero. */
inline constexpr double kEpsilon = 1e-9;

/* ------------------------------------------------------------------------- */
/* Level 1: the Matrix type                                                  */
/* ------------------------------------------------------------------------- */

class Matrix {
public:
    /* A rows x cols matrix of zeros. Throws std::invalid_argument if rows or cols is 0. */
    Matrix(std::size_t rows, std::size_t cols);

    /*
     * A matrix with the given rows, so Matrix{{1, 2, 3}, {4, 5, 6}} is 2 x 3.
     * Throws std::invalid_argument if there are no rows, a row is empty, or
     * the rows have different lengths.
     */
    Matrix(std::initializer_list<std::initializer_list<double>> rows);

    /* The n x n identity matrix. Throws std::invalid_argument if n is 0. */
    static Matrix identity(std::size_t n);

    std::size_t rows() const;
    std::size_t cols() const;

    /* The entry at (row, col). Throws std::out_of_range if row >= rows() or col >= cols(). */
    double& at(std::size_t row, std::size_t col);
    double at(std::size_t row, std::size_t col) const;

private:
    // Your data members go here. A copy of a Matrix must not share entries with the original.
};

/* True if a and b have the same shape and exactly equal entries. */
bool operator==(const Matrix& a, const Matrix& b);

/* ------------------------------------------------------------------------- */
/* Level 2: entry-wise operations                                            */
/* ------------------------------------------------------------------------- */

/* a + b and a - b. Throw std::invalid_argument if a and b have different shapes. */
Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);

/* Every entry of m multiplied by scalar. */
Matrix operator*(double scalar, const Matrix& m);
Matrix operator*(const Matrix& m, double scalar);

/* The transpose of m: entry (i, j) of the result is entry (j, i) of m. */
Matrix transpose(const Matrix& m);

/* The sum of m's diagonal entries. Throws std::invalid_argument if m is not square. */
double trace(const Matrix& m);

/* ------------------------------------------------------------------------- */
/* Level 3: multiplication and powers                                        */
/* ------------------------------------------------------------------------- */

/* The matrix product a * b. Throws std::invalid_argument if a.cols() != b.rows(). */
Matrix operator*(const Matrix& a, const Matrix& b);

/*
 * m multiplied by itself `exponent` times, where m^0 is the identity.
 * Throws std::invalid_argument if m is not square.
 * Must run in O(n^3 log exponent) time for an n x n matrix.
 */
Matrix power(const Matrix& m, unsigned long long exponent);

/* ------------------------------------------------------------------------- */
/* Level 4: determinants                                                     */
/* ------------------------------------------------------------------------- */

/*
 * The determinant of m. Throws std::invalid_argument if m is not square.
 * Must run in O(n^3) time for an n x n matrix.
 */
double determinant(const Matrix& m);

/* ------------------------------------------------------------------------- */
/* Level 5: row reduction and rank                                           */
/* ------------------------------------------------------------------------- */

/*
 * The reduced row echelon form of m: the matrix reachable from m by row
 * operations (swapping two rows, scaling a row by a nonzero number, adding a
 * multiple of one row to another) in which
 *   - every all-zero row is below every other row;
 *   - the leftmost nonzero entry of each other row, its pivot, is 1 and lies
 *     to the right of the pivot in the row above;
 *   - every other entry in a pivot's column is 0.
 * Values whose magnitude is below kEpsilon count as zero.
 */
Matrix rref(const Matrix& m);

/*
 * The rank of m: its number of linearly independent rows.
 * Values whose magnitude is below kEpsilon count as zero.
 */
std::size_t rank(const Matrix& m);

/* ------------------------------------------------------------------------- */
/* Level 6: inverses and linear systems                                      */
/* ------------------------------------------------------------------------- */

/*
 * The inverse of m. Throws std::invalid_argument if m is not square, and
 * std::domain_error if m is singular (rank(m) < m.rows()).
 */
Matrix inverse(const Matrix& m);

/*
 * The x that satisfies a * x = b, for an n x n matrix a and an n x k matrix b
 * (each column of b is a separate right-hand side).
 * Throws std::invalid_argument if a is not square or b.rows() != a.rows(),
 * and std::domain_error if a is singular.
 */
Matrix solve(const Matrix& a, const Matrix& b);

/* ------------------------------------------------------------------------- */
/* Level 7: LU decomposition                                                 */
/* ------------------------------------------------------------------------- */

/* The factors of p * m = l * u returned by lu_decompose. */
struct LU {
    Matrix p;
    Matrix l;
    Matrix u;
};

/*
 * Factors a square matrix m as p * m = l * u, where
 *   - p is a permutation matrix: the identity with its rows reordered;
 *   - l is lower triangular, has 1s on its diagonal, and has no entry whose
 *     magnitude is above 1;
 *   - u is upper triangular.
 * Singular matrices can be factored too.
 * Throws std::invalid_argument if m is not square.
 */
LU lu_decompose(const Matrix& m);

/* ------------------------------------------------------------------------- */
/* Level 8: QR decomposition and least squares                               */
/* ------------------------------------------------------------------------- */

/* The factors of m = q * r returned by qr_decompose. */
struct QR {
    Matrix q;
    Matrix r;
};

/*
 * Factors a matrix m with at least as many rows as columns as m = q * r, where
 *   - q has m's shape and orthonormal columns (transpose(q) * q is the identity);
 *   - r is square, upper triangular, and has positive diagonal entries.
 * Throws std::invalid_argument if m has more columns than rows, and
 * std::domain_error if m's columns are linearly dependent (rank(m) < m.cols()).
 */
QR qr_decompose(const Matrix& m);

/*
 * The x that minimizes the sum of the squared entries of a * x - b, for an
 * r x c matrix a with r >= c and an r x k matrix b.
 * Throws std::invalid_argument if a has more columns than rows or
 * b.rows() != a.rows(), and std::domain_error if a's columns are linearly
 * dependent.
 */
Matrix least_squares(const Matrix& a, const Matrix& b);

/* ------------------------------------------------------------------------- */
/* Level 9: eigenvalues of symmetric matrices                                */
/* ------------------------------------------------------------------------- */

/*
 * The eigenvalues of a symmetric matrix m in ascending order, each listed as
 * many times as its multiplicity. The tests accept an error of 1e-8 here
 * instead of 1e-9.
 * Throws std::invalid_argument if m is not square, or if it is not symmetric:
 * some |m(i, j) - m(j, i)| is at least kEpsilon.
 */
std::vector<double> symmetric_eigenvalues(const Matrix& m);

}  // namespace linalg

#endif
