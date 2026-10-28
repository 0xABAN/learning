/*
 * matrix_tests.cpp
 *
 * Tests for the exercises in matrix.h, grouped by level. Set up the build once
 * from this folder:
 *
 *     cmake -B build
 *
 * then build them with your implementation in matrix.cpp and run:
 *
 *     cmake --build build && ./build/matrix_tests
 *
 * Pass a level to run only its tests, e.g. ./build/matrix_tests 3. A function
 * that still throws "not implemented" fails every test that calls it.
 */

#include "matrix.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <initializer_list>
#include <stdexcept>
#include <vector>

using namespace linalg;

namespace {

/* ------------------------------------------------------------------------- */
/* Test harness                                                              */
/* ------------------------------------------------------------------------- */

bool test_failed;

/* Fails the current test and returns from the enclosing test function. */
#define CHECK(condition, ...)                                                  \
    do {                                                                       \
        if (!(condition)) {                                                    \
            std::printf("    %s:%d: ", __FILE__, __LINE__);                    \
            std::printf(__VA_ARGS__);                                          \
            std::printf("\n");                                                 \
            test_failed = true;                                                \
            return;                                                            \
        }                                                                      \
    } while (0)

/*
 * Fails the current test unless the expression after exception_type throws
 * exception_type. Any other exception propagates and fails the test too.
 */
#define CHECK_THROWS(exception_type, ...)                                      \
    do {                                                                       \
        bool threw_expected = false;                                           \
        try {                                                                  \
            (void)(__VA_ARGS__);                                               \
        } catch (const exception_type&) {                                      \
            threw_expected = true;                                             \
        }                                                                      \
        CHECK(threw_expected, "%s should throw %s", #__VA_ARGS__, #exception_type); \
    } while (0)

const double kTolerance = 1e-9;
const double kEigenvalueTolerance = 1e-8;

double seconds_since(std::clock_t start) {
    return static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
}

/* Absolute error up to tolerance, or relative error once expected is larger than 1. */
bool near(double actual, double expected, double tolerance = kTolerance) {
    return std::fabs(actual - expected) <= tolerance * std::max(1.0, std::fabs(expected));
}

/* Returns true if actual has expected's shape and near entries; otherwise prints the first difference. */
bool matrices_match(const Matrix& actual, const Matrix& expected) {
    if (actual.rows() != expected.rows() || actual.cols() != expected.cols()) {
        std::printf("    expected a %zu x %zu matrix, got %zu x %zu\n",
                    expected.rows(), expected.cols(), actual.rows(), actual.cols());
        return false;
    }

    for (std::size_t row = 0; row < expected.rows(); row++) {
        for (std::size_t col = 0; col < expected.cols(); col++) {
            if (!near(actual.at(row, col), expected.at(row, col))) {
                std::printf("    entry (%zu, %zu): expected %.12g, got %.12g\n",
                            row, col, expected.at(row, col), actual.at(row, col));
                return false;
            }
        }
    }
    return true;
}

/* ------------------------------------------------------------------------- */
/* Reference operations, so checks don't depend on the code under test.      */
/* ------------------------------------------------------------------------- */

Matrix reference_product(const Matrix& a, const Matrix& b) {
    Matrix product(a.rows(), b.cols());
    for (std::size_t row = 0; row < a.rows(); row++) {
        for (std::size_t col = 0; col < b.cols(); col++) {
            for (std::size_t k = 0; k < a.cols(); k++) {
                product.at(row, col) += a.at(row, k) * b.at(k, col);
            }
        }
    }
    return product;
}

Matrix reference_difference(const Matrix& a, const Matrix& b) {
    Matrix difference(a.rows(), a.cols());
    for (std::size_t row = 0; row < a.rows(); row++) {
        for (std::size_t col = 0; col < a.cols(); col++) {
            difference.at(row, col) = a.at(row, col) - b.at(row, col);
        }
    }
    return difference;
}

Matrix reference_transpose(const Matrix& m) {
    Matrix transposed(m.cols(), m.rows());
    for (std::size_t row = 0; row < m.rows(); row++) {
        for (std::size_t col = 0; col < m.cols(); col++) {
            transposed.at(col, row) = m.at(row, col);
        }
    }
    return transposed;
}

/* A deterministic stream of doubles in [-1, 1), so every run tests the same matrices. */
class Random {
public:
    explicit Random(std::uint32_t seed) : state_(seed) {}

    double next() {
        state_ = state_ * 1664525u + 1013904223u;
        return static_cast<double>(state_ >> 8) / (1u << 24) * 2.0 - 1.0;
    }

private:
    std::uint32_t state_;
};

Matrix random_matrix(std::size_t rows, std::size_t cols, std::uint32_t seed) {
    Random random(seed);
    Matrix m(rows, cols);
    for (std::size_t row = 0; row < rows; row++) {
        for (std::size_t col = 0; col < cols; col++) {
            m.at(row, col) = random.next();
        }
    }
    return m;
}

/* A random matrix whose diagonal outweighs the rest of each row, so it is invertible and well-conditioned. */
Matrix diagonally_dominant(std::size_t n, std::uint32_t seed) {
    Matrix m = random_matrix(n, n, seed);
    for (std::size_t i = 0; i < n; i++) {
        m.at(i, i) = static_cast<double>(n) + 1.0;
    }
    return m;
}

/* The n x n identity with a rotation by `angle` in the plane of coordinates i and j. */
Matrix rotation(std::size_t n, std::size_t i, std::size_t j, double angle) {
    Matrix m = Matrix::identity(n);
    m.at(i, i) = std::cos(angle);
    m.at(j, j) = std::cos(angle);
    m.at(i, j) = -std::sin(angle);
    m.at(j, i) = std::sin(angle);
    return m;
}

/* ------------------------------------------------------------------------- */
/* Level 1: the Matrix type                                                  */
/* ------------------------------------------------------------------------- */

void test_shape_constructor_fills_zeros() {
    Matrix m(2, 3);
    CHECK(m.rows() == 2 && m.cols() == 3, "Matrix(2, 3) is %zu x %zu", m.rows(), m.cols());

    for (std::size_t row = 0; row < 2; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            CHECK(m.at(row, col) == 0, "Matrix(2, 3).at(%zu, %zu) is %g, expected 0",
                  row, col, m.at(row, col));
        }
    }

    Matrix single(1, 1);
    CHECK(single.rows() == 1 && single.cols() == 1 && single.at(0, 0) == 0,
          "Matrix(1, 1) should hold a single 0");

    Matrix row_vector(1, 5);
    CHECK(row_vector.rows() == 1 && row_vector.cols() == 5, "Matrix(1, 5) is %zu x %zu",
          row_vector.rows(), row_vector.cols());
}

void test_list_constructor_fills_rows_in_order() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    CHECK(m.rows() == 2 && m.cols() == 3, "{{1, 2, 3}, {4, 5, 6}} is %zu x %zu", m.rows(), m.cols());

    const double expected[2][3] = {{1, 2, 3}, {4, 5, 6}};
    for (std::size_t row = 0; row < 2; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            CHECK(m.at(row, col) == expected[row][col], "entry (%zu, %zu) is %g, expected %g",
                  row, col, m.at(row, col), expected[row][col]);
        }
    }

    Matrix column{{1}, {2}, {3}};
    CHECK(column.rows() == 3 && column.cols() == 1, "{{1}, {2}, {3}} is %zu x %zu",
          column.rows(), column.cols());
    CHECK(column.at(2, 0) == 3, "{{1}, {2}, {3}}.at(2, 0) is %g, expected 3", column.at(2, 0));

    Matrix single{{-7.5}};
    CHECK(single.rows() == 1 && single.cols() == 1 && single.at(0, 0) == -7.5,
          "{{-7.5}} should be 1 x 1 holding -7.5");
}

void test_at_reads_and_writes_entries() {
    Matrix m(2, 2);
    m.at(1, 0) = 7;
    m.at(0, 1) = -2.5;

    const Matrix& view = m;
    CHECK(view.at(1, 0) == 7, "after writing 7 to (1, 0), it reads %g", view.at(1, 0));
    CHECK(view.at(0, 1) == -2.5, "after writing -2.5 to (0, 1), it reads %g", view.at(0, 1));
    CHECK(view.at(0, 0) == 0 && view.at(1, 1) == 0, "writing two entries changed another one");
}

void test_identity() {
    Matrix i3 = Matrix::identity(3);
    CHECK(i3.rows() == 3 && i3.cols() == 3, "identity(3) is %zu x %zu", i3.rows(), i3.cols());

    for (std::size_t row = 0; row < 3; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            double expected = row == col ? 1 : 0;
            CHECK(i3.at(row, col) == expected, "identity(3).at(%zu, %zu) is %g, expected %g",
                  row, col, i3.at(row, col), expected);
        }
    }

    Matrix i1 = Matrix::identity(1);
    CHECK(i1.rows() == 1 && i1.cols() == 1 && i1.at(0, 0) == 1, "identity(1) should hold a single 1");
}

void test_rejects_zero_rows_or_columns() {
    CHECK_THROWS(std::invalid_argument, Matrix(0, 3));
    CHECK_THROWS(std::invalid_argument, Matrix(3, 0));
    CHECK_THROWS(std::invalid_argument, Matrix(0, 0));
    CHECK_THROWS(std::invalid_argument, Matrix::identity(0));
}

void test_rejects_empty_or_ragged_rows() {
    std::initializer_list<std::initializer_list<double>> no_rows = {};
    CHECK_THROWS(std::invalid_argument, Matrix(no_rows));
    CHECK_THROWS(std::invalid_argument, Matrix{{}});
    CHECK_THROWS(std::invalid_argument, Matrix{{1, 2}, {}});
    CHECK_THROWS(std::invalid_argument, Matrix{{1, 2}, {3}});
    CHECK_THROWS(std::invalid_argument, Matrix{{1}, {2, 3}});
    CHECK_THROWS(std::invalid_argument, Matrix{{1, 2}, {3, 4}, {5, 6, 7}});
}

void test_rejects_out_of_range_indexes() {
    Matrix m(2, 3);
    const Matrix& view = m;
    std::size_t huge = static_cast<std::size_t>(-1);

    CHECK_THROWS(std::out_of_range, m.at(2, 0));
    CHECK_THROWS(std::out_of_range, m.at(0, 3));
    CHECK_THROWS(std::out_of_range, m.at(2, 3));
    CHECK_THROWS(std::out_of_range, m.at(huge, 0));
    CHECK_THROWS(std::out_of_range, m.at(0, huge));
    CHECK_THROWS(std::out_of_range, view.at(2, 0));
    CHECK_THROWS(std::out_of_range, view.at(0, 3));
    CHECK_THROWS(std::out_of_range, view.at(huge, huge));
}

void test_copies_are_independent() {
    Matrix original{{1, 2}, {3, 4}};

    Matrix copy = original;
    copy.at(0, 0) = 9;
    CHECK(original.at(0, 0) == 1, "changing a copy changed the original");
    CHECK(copy.at(1, 0) == 3, "a copy should keep the original's entries");

    Matrix assigned(1, 1);
    assigned = original;
    CHECK(assigned.rows() == 2 && assigned.cols() == 2, "after assignment the matrix is %zu x %zu, expected 2 x 2",
          assigned.rows(), assigned.cols());
    CHECK(assigned.at(0, 1) == 2, "assignment should copy the entries");

    assigned.at(1, 1) = 0;
    CHECK(original.at(1, 1) == 4, "changing an assigned copy changed the original");
}

void test_equality() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix same{{1, 2}, {3, 4}};
    Matrix different_entry{{1, 2}, {3, 4.000001}};
    Matrix row{{1, 2}};
    Matrix column{{1}, {2}};

    CHECK(a == same, "equal matrices should compare equal");
    CHECK(a == a, "a matrix should equal itself");
    CHECK(!(a == different_entry), "matrices with one different entry should not compare equal");
    CHECK(!(row == column), "a 1 x 2 and a 2 x 1 matrix should not compare equal");
    CHECK(Matrix(2, 3) == Matrix(2, 3), "zero matrices of the same shape should compare equal");
    CHECK(!(Matrix(2, 3) == Matrix(3, 2)), "zero matrices of different shapes should not compare equal");
}

/* ------------------------------------------------------------------------- */
/* Level 2: entry-wise operations                                            */
/* ------------------------------------------------------------------------- */

void test_add_and_subtract() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{5, -6}, {0.5, 8}};
    Matrix sum{{6, -4}, {3.5, 12}};
    Matrix difference{{-4, 8}, {2.5, -4}};

    CHECK(matrices_match(a + b, sum), "a + b is wrong");
    CHECK(matrices_match(b + a, sum), "b + a is wrong");
    CHECK(matrices_match(a - b, difference), "a - b is wrong");
    CHECK(matrices_match(a - a, Matrix(2, 2)), "a - a should be the zero matrix");

    Matrix wide_a{{1, 2, 3}, {4, 5, 6}};
    Matrix wide_b{{6, 5, 4}, {3, 2, 1}};
    Matrix sevens{{7, 7, 7}, {7, 7, 7}};
    CHECK(matrices_match(wide_a + wide_b, sevens), "adding 2 x 3 matrices is wrong");
}

void test_add_and_subtract_reject_shape_mismatch() {
    Matrix two_by_three(2, 3);
    Matrix three_by_two(3, 2);
    Matrix one_by_one(1, 1);
    Matrix one_by_two(1, 2);

    CHECK_THROWS(std::invalid_argument, two_by_three + three_by_two);
    CHECK_THROWS(std::invalid_argument, two_by_three - three_by_two);
    CHECK_THROWS(std::invalid_argument, one_by_one + one_by_two);
    CHECK_THROWS(std::invalid_argument, one_by_two - one_by_one);
}

void test_scalar_multiplication() {
    Matrix m{{1, -2}, {0.5, 4}};
    Matrix doubled{{2, -4}, {1, 8}};
    Matrix negated{{-1, 2}, {-0.5, -4}};

    CHECK(matrices_match(2.0 * m, doubled), "2 * m is wrong");
    CHECK(matrices_match(m * 2.0, doubled), "m * 2 is wrong");
    CHECK(matrices_match(-1.0 * m, negated), "-1 * m is wrong");
    CHECK(matrices_match(0.0 * m, Matrix(2, 2)), "0 * m should be the zero matrix");

    Matrix row{{3, 6, 9}};
    Matrix third{{1, 2, 3}};
    CHECK(matrices_match(row * (1.0 / 3), third), "{{3, 6, 9}} * (1 / 3) is wrong");
}

void test_transpose() {
    Matrix wide{{1, 2, 3}, {4, 5, 6}};
    Matrix tall{{1, 4}, {2, 5}, {3, 6}};
    CHECK(matrices_match(transpose(wide), tall), "transpose of a 2 x 3 matrix is wrong");
    CHECK(matrices_match(transpose(tall), wide), "transpose of a 3 x 2 matrix is wrong");

    Matrix square{{1, 2}, {3, 4}};
    Matrix square_transposed{{1, 3}, {2, 4}};
    CHECK(matrices_match(transpose(square), square_transposed), "transpose of a 2 x 2 matrix is wrong");

    Matrix single{{5}};
    CHECK(matrices_match(transpose(single), single), "transpose of a 1 x 1 matrix is wrong");

    Matrix row{{1, 2, 3}};
    Matrix column{{1}, {2}, {3}};
    CHECK(matrices_match(transpose(row), column), "transpose of a row should be a column");
    CHECK(matrices_match(transpose(transpose(wide)), wide), "transposing twice should give back the original");
}

void test_trace() {
    Matrix m{{1, 2}, {3, 4}};
    double value = trace(m);
    CHECK(near(value, 5), "trace of {{1, 2}, {3, 4}} is %g, expected 5", value);

    Matrix single{{-7}};
    value = trace(single);
    CHECK(near(value, -7), "trace of {{-7}} is %g, expected -7", value);

    value = trace(Matrix::identity(4));
    CHECK(near(value, 4), "trace of identity(4) is %g, expected 4", value);

    Matrix three{{1, 9, 9}, {9, -2, 9}, {9, 9, 0.5}};
    value = trace(three);
    CHECK(near(value, -0.5), "trace of a 3 x 3 matrix is %g, expected -0.5", value);
}

void test_trace_rejects_non_square() {
    CHECK_THROWS(std::invalid_argument, trace(Matrix(2, 3)));
    CHECK_THROWS(std::invalid_argument, trace(Matrix(3, 1)));
}

/* ------------------------------------------------------------------------- */
/* Level 3: multiplication and powers                                        */
/* ------------------------------------------------------------------------- */

void test_multiply() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{7, 8}, {9, 10}, {11, 12}};
    Matrix ab{{58, 64}, {139, 154}};
    Matrix ba{{39, 54, 69}, {49, 68, 87}, {59, 82, 105}};
    CHECK(matrices_match(a * b, ab), "2 x 3 times 3 x 2 is wrong");
    CHECK(matrices_match(b * a, ba), "3 x 2 times 2 x 3 is wrong");

    Matrix row{{1, 2, 3}};
    Matrix column{{4}, {5}, {6}};
    Matrix dot{{32}};
    CHECK(matrices_match(row * column, dot), "a row times a column should be 1 x 1");

    Matrix left_column{{1}, {-2}, {3}};
    Matrix right_row{{4, 5}};
    Matrix outer{{4, 5}, {-8, -10}, {12, 15}};
    CHECK(matrices_match(left_column * right_row, outer), "a column times a row is wrong");
}

void test_multiply_identity_and_order() {
    Matrix m{{1, -2, 3}, {0, 4.5, -1}};
    CHECK(matrices_match(Matrix::identity(2) * m, m), "identity(2) * m should be m");
    CHECK(matrices_match(m * Matrix::identity(3), m), "m * identity(3) should be m");

    Matrix a{{0, 1}, {0, 0}};
    Matrix b{{0, 0}, {1, 0}};
    Matrix ab{{1, 0}, {0, 0}};
    Matrix ba{{0, 0}, {0, 1}};
    CHECK(matrices_match(a * b, ab), "a * b is wrong");
    CHECK(matrices_match(b * a, ba), "b * a is wrong");

    Matrix cancels_left{{1, -1}, {2, -2}};
    Matrix cancels_right{{3, 4}, {3, 4}};
    CHECK(matrices_match(cancels_left * cancels_right, Matrix(2, 2)), "a product whose terms cancel should be zero");
}

void test_multiply_rejects_mismatched_shapes() {
    Matrix two_by_three(2, 3);
    Matrix three_by_two(3, 2);
    Matrix one_by_two(1, 2);

    CHECK_THROWS(std::invalid_argument, two_by_three * two_by_three);
    CHECK_THROWS(std::invalid_argument, three_by_two * three_by_two);
    CHECK_THROWS(std::invalid_argument, one_by_two * one_by_two);
}

void test_power_of_small_exponents() {
    Matrix m{{2, 1}, {0, 3}};
    Matrix m_cubed{{8, 19}, {0, 27}};
    CHECK(matrices_match(power(m, 0), Matrix::identity(2)), "m^0 should be the identity");
    CHECK(matrices_match(power(m, 1), m), "m^1 should be m");
    CHECK(matrices_match(power(m, 3), m_cubed), "m^3 is wrong");
    CHECK(matrices_match(power(Matrix(3, 3), 0), Matrix::identity(3)), "the zero matrix to the power 0 should be the identity");

    Matrix fibonacci{{1, 1}, {1, 0}};
    Matrix fibonacci_10{{89, 55}, {55, 34}};
    CHECK(matrices_match(power(fibonacci, 10), fibonacci_10), "{{1, 1}, {1, 0}}^10 is wrong");

    Matrix nilpotent{{0, 1}, {0, 0}};
    CHECK(matrices_match(power(nilpotent, 2), Matrix(2, 2)), "{{0, 1}, {0, 0}}^2 should be zero");

    Matrix cycle{{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
    CHECK(matrices_match(power(cycle, 3), Matrix::identity(3)), "a 3-cycle cubed should be the identity");
    CHECK(matrices_match(power(cycle, 4), cycle), "a 3-cycle to the power 4 should be itself");
}

void test_power_rejects_non_square() {
    Matrix two_by_three(2, 3);
    CHECK_THROWS(std::invalid_argument, power(two_by_three, 0));
    CHECK_THROWS(std::invalid_argument, power(two_by_three, 2));
}

void test_power_of_large_exponents_is_fast() {
    Matrix shear{{1, 1}, {0, 1}};
    Matrix shear_10_million{{1, 1e7}, {0, 1}};
    Matrix quarter_turn{{0, -1}, {1, 0}};
    Matrix three_quarter_turns{{0, 1}, {-1, 0}};

    std::clock_t start = std::clock();
    Matrix shear_result = power(shear, 10000000);
    Matrix turn_result = power(quarter_turn, 10000003);
    double elapsed = seconds_since(start);

    CHECK(matrices_match(shear_result, shear_10_million), "{{1, 1}, {0, 1}}^10000000 is wrong");
    CHECK(matrices_match(turn_result, three_quarter_turns), "{{0, -1}, {1, 0}}^10000003 is wrong");
    CHECK(elapsed < 0.01, "two powers with exponents near 10^7 took %.3fs; must be O(n^3 log exponent)", elapsed);

    // Exponents beyond 32 bits.
    Matrix shear_10_18{{1, 1e18}, {0, 1}};
    CHECK(matrices_match(power(shear, 1000000000000000000ULL), shear_10_18), "{{1, 1}, {0, 1}}^(10^18) is wrong");
    CHECK(matrices_match(power(quarter_turn, 4000000000003ULL), three_quarter_turns),
          "{{0, -1}, {1, 0}}^4000000000003 is wrong");
}

/* ------------------------------------------------------------------------- */
/* Level 4: determinants                                                     */
/* ------------------------------------------------------------------------- */

/* Returns true if determinant(m) is near expected; otherwise prints both values. */
bool determinant_is(const Matrix& m, double expected) {
    double actual = determinant(m);
    if (near(actual, expected)) {
        return true;
    }
    std::printf("    expected %.12g, got %.12g\n", expected, actual);
    return false;
}

void test_determinant_of_small_matrices() {
    Matrix single{{-3}};
    Matrix two{{1, 2}, {3, 4}};
    Matrix three{{6, 1, 1}, {4, -2, 5}, {2, 8, 7}};
    Matrix upper{{2, 5, -1}, {0, 3, 7}, {0, 0, -4}};
    Matrix lower{{2, 0, 0}, {5, 3, 0}, {-1, 7, -4}};

    CHECK(determinant_is(single, -3), "determinant of {{-3}} is wrong");
    CHECK(determinant_is(two, -2), "determinant of {{1, 2}, {3, 4}} is wrong");
    CHECK(determinant_is(three, -306), "determinant of {{6, 1, 1}, {4, -2, 5}, {2, 8, 7}} is wrong");
    CHECK(determinant_is(Matrix::identity(5), 1), "determinant of identity(5) is wrong");
    CHECK(determinant_is(upper, -24), "determinant of an upper triangular matrix is wrong");
    CHECK(determinant_is(lower, -24), "determinant of a lower triangular matrix is wrong");
}

void test_determinant_with_zero_on_the_diagonal() {
    Matrix swap{{0, 1}, {1, 0}};
    Matrix three{{0, 2, 1}, {1, 1, 1}, {2, 1, 0}};
    Matrix reversal{{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};
    Matrix anti_diagonal{{0, 0, 2}, {0, 3, 0}, {4, 0, 0}};

    CHECK(determinant_is(swap, -1), "determinant of {{0, 1}, {1, 0}} is wrong");
    CHECK(determinant_is(three, 3), "determinant of {{0, 2, 1}, {1, 1, 1}, {2, 1, 0}} is wrong");
    CHECK(determinant_is(reversal, -1), "determinant of {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}} is wrong");
    CHECK(determinant_is(anti_diagonal, -24), "determinant of {{0, 0, 2}, {0, 3, 0}, {4, 0, 0}} is wrong");
}

void test_determinant_of_singular_matrices() {
    Matrix proportional_rows{{1, 2}, {2, 4}};
    Matrix dependent_rows{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix zero_column{{1, 0, 3}, {2, 0, 5}, {4, 0, 6}};
    Matrix repeated_row{{1, 2, 3}, {1, 2, 3}, {4, 5, 6}};

    CHECK(determinant_is(proportional_rows, 0), "determinant of {{1, 2}, {2, 4}} is wrong");
    CHECK(determinant_is(dependent_rows, 0), "determinant of {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} is wrong");
    CHECK(determinant_is(zero_column, 0), "determinant of a matrix with a zero column is wrong");
    CHECK(determinant_is(repeated_row, 0), "determinant of a matrix with a repeated row is wrong");
    CHECK(determinant_is(Matrix(3, 3), 0), "determinant of the zero matrix is wrong");
}

void test_determinant_under_row_operations() {
    Matrix m{{2, -1, 0}, {1, 3, 2}, {0, 5, -4}};
    Matrix rows_swapped{{1, 3, 2}, {2, -1, 0}, {0, 5, -4}};
    Matrix row_tripled{{2, -1, 0}, {1, 3, 2}, {0, 15, -12}};
    Matrix row_added{{2, -1, 0}, {5, 1, 2}, {0, 5, -4}};
    Matrix transposed{{2, 1, 0}, {-1, 3, 5}, {0, 2, -4}};

    CHECK(determinant_is(m, -48), "determinant of {{2, -1, 0}, {1, 3, 2}, {0, 5, -4}} is wrong");
    CHECK(determinant_is(rows_swapped, 48), "swapping two rows should negate the determinant");
    CHECK(determinant_is(row_tripled, -144), "tripling a row should triple the determinant");
    CHECK(determinant_is(row_added, -48), "adding a multiple of one row to another should keep the determinant");
    CHECK(determinant_is(transposed, -48), "transposing should keep the determinant");
}

void test_determinant_rejects_non_square() {
    CHECK_THROWS(std::invalid_argument, determinant(Matrix(2, 3)));
    CHECK_THROWS(std::invalid_argument, determinant(Matrix(3, 1)));
}

void test_determinant_of_10x10_is_fast() {
    // m = lower * upper, where lower has 1s on its diagonal, so det(m) is the
    // product of upper's diagonal: (2 * -1 * 0.5)^3 * 2 = -2.
    const std::size_t n = 10;
    const double upper_diagonal[] = {2, -1, 0.5};
    Random random(7);
    Matrix lower = Matrix::identity(n);
    Matrix upper(n, n);

    for (std::size_t row = 0; row < n; row++) {
        for (std::size_t col = 0; col < n; col++) {
            if (col < row) {
                lower.at(row, col) = random.next();
            } else if (col > row) {
                upper.at(row, col) = random.next();
            } else {
                upper.at(row, col) = upper_diagonal[row % 3];
            }
        }
    }
    Matrix m = reference_product(lower, upper);

    std::clock_t start = std::clock();
    double actual = determinant(m);
    double elapsed = seconds_since(start);

    CHECK(near(actual, -2), "determinant of a 10 x 10 matrix is %.12g, expected -2", actual);
    CHECK(elapsed < 0.01, "a 10 x 10 determinant took %.3fs; must be O(n^3)", elapsed);
}

/* ------------------------------------------------------------------------- */
/* Level 5: row reduction and rank                                           */
/* ------------------------------------------------------------------------- */

/* Returns true if rank(m) is expected; otherwise prints both values. */
bool rank_is(const Matrix& m, std::size_t expected) {
    std::size_t actual = rank(m);
    if (actual == expected) {
        return true;
    }
    std::printf("    expected %zu, got %zu\n", expected, actual);
    return false;
}

void test_rref_of_invertible_matrices() {
    Matrix two{{2, 1}, {1, 3}};
    Matrix swap{{0, 1}, {1, 0}};
    Matrix three{{1, 2, 3}, {0, 1, 4}, {5, 6, 0}};

    CHECK(matrices_match(rref(two), Matrix::identity(2)), "rref of {{2, 1}, {1, 3}} is wrong");
    CHECK(matrices_match(rref(swap), Matrix::identity(2)), "rref of {{0, 1}, {1, 0}} is wrong");
    CHECK(matrices_match(rref(three), Matrix::identity(3)), "rref of {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}} is wrong");
    CHECK(matrices_match(rref(Matrix::identity(4)), Matrix::identity(4)), "rref of identity(4) is wrong");
}

void test_rref_of_singular_and_rectangular_matrices() {
    Matrix dependent{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix dependent_rref{{1, 0, -1}, {0, 1, 2}, {0, 0, 0}};
    CHECK(matrices_match(rref(dependent), dependent_rref), "rref of {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} is wrong");

    Matrix wide{{1, 2, 1}, {2, 4, 0}};
    Matrix wide_rref{{1, 2, 0}, {0, 0, 1}};
    CHECK(matrices_match(rref(wide), wide_rref), "rref of {{1, 2, 1}, {2, 4, 0}} is wrong");

    Matrix tall{{1, 2}, {3, 4}, {5, 6}};
    Matrix tall_rref{{1, 0}, {0, 1}, {0, 0}};
    CHECK(matrices_match(rref(tall), tall_rref), "rref of {{1, 2}, {3, 4}, {5, 6}} is wrong");

    Matrix zero_rows_first{{0, 0}, {0, 0}, {1, 2}};
    Matrix zero_rows_first_rref{{1, 2}, {0, 0}, {0, 0}};
    CHECK(matrices_match(rref(zero_rows_first), zero_rows_first_rref), "rref of {{0, 0}, {0, 0}, {1, 2}} is wrong");

    Matrix zero_first_column{{0, 3, 6}, {0, 1, 2}};
    Matrix zero_first_column_rref{{0, 1, 2}, {0, 0, 0}};
    CHECK(matrices_match(rref(zero_first_column), zero_first_column_rref), "rref of {{0, 3, 6}, {0, 1, 2}} is wrong");

    Matrix row{{2, 4, 6, 8}};
    Matrix row_rref{{1, 2, 3, 4}};
    CHECK(matrices_match(rref(row), row_rref), "rref of {{2, 4, 6, 8}} is wrong");

    Matrix column{{0}, {5}, {0}};
    Matrix column_rref{{1}, {0}, {0}};
    CHECK(matrices_match(rref(column), column_rref), "rref of {{0}, {5}, {0}} is wrong");

    CHECK(matrices_match(rref(Matrix(2, 3)), Matrix(2, 3)), "rref of the zero matrix should be itself");
}

void test_rref_treats_tiny_values_as_zero() {
    Matrix nearly_proportional{{1, 2}, {2, 4 + 1e-12}};
    Matrix nearly_proportional_rref{{1, 2}, {0, 0}};
    CHECK(matrices_match(rref(nearly_proportional), nearly_proportional_rref),
          "rref of {{1, 2}, {2, 4 + 1e-12}} is wrong");

    Matrix tiny_diagonal{{1e-12, 0}, {0, 1e-12}};
    CHECK(matrices_match(rref(tiny_diagonal), Matrix(2, 2)), "rref of {{1e-12, 0}, {0, 1e-12}} should be zero");
}

void test_rank() {
    Matrix dependent{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix wide{{1, 2, 1}, {2, 4, 0}};
    Matrix tall{{1, 2}, {3, 4}, {5, 6}};
    Matrix proportional{{1, 2}, {2, 4}};
    Matrix zero_single{{0}};
    Matrix single{{5}};

    CHECK(rank_is(Matrix::identity(4), 4), "rank of identity(4) is wrong");
    CHECK(rank_is(Matrix(3, 3), 0), "rank of the zero matrix is wrong");
    CHECK(rank_is(dependent, 2), "rank of {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} is wrong");
    CHECK(rank_is(wide, 2), "rank of {{1, 2, 1}, {2, 4, 0}} is wrong");
    CHECK(rank_is(tall, 2), "rank of {{1, 2}, {3, 4}, {5, 6}} is wrong");
    CHECK(rank_is(proportional, 1), "rank of {{1, 2}, {2, 4}} is wrong");
    CHECK(rank_is(zero_single, 0), "rank of {{0}} is wrong");
    CHECK(rank_is(single, 1), "rank of {{5}} is wrong");

    // A 4 x 2 times a 2 x 5 matrix has rank 2, and so does its transpose.
    Matrix rank_two = reference_product(random_matrix(4, 2, 1), random_matrix(2, 5, 2));
    CHECK(rank_is(rank_two, 2), "rank of a 4 x 5 product of 4 x 2 and 2 x 5 matrices is wrong");
    CHECK(rank_is(reference_transpose(rank_two), 2), "rank of its 5 x 4 transpose is wrong");
}

void test_rank_treats_tiny_values_as_zero() {
    Matrix nearly_proportional{{1, 2}, {2, 4 + 1e-12}};
    Matrix tiny_diagonal{{1e-12, 0}, {0, 1e-12}};
    Matrix tiny_single{{1e-12}};

    CHECK(rank_is(nearly_proportional, 1), "rank of {{1, 2}, {2, 4 + 1e-12}} is wrong");
    CHECK(rank_is(tiny_diagonal, 0), "rank of {{1e-12, 0}, {0, 1e-12}} is wrong");
    CHECK(rank_is(tiny_single, 0), "rank of {{1e-12}} is wrong");
}

/* ------------------------------------------------------------------------- */
/* Level 6: inverses and linear systems                                      */
/* ------------------------------------------------------------------------- */

void test_inverse_of_small_matrices() {
    Matrix two{{4, 7}, {2, 6}};
    Matrix two_inverse{{0.6, -0.7}, {-0.2, 0.4}};
    CHECK(matrices_match(inverse(two), two_inverse), "inverse of {{4, 7}, {2, 6}} is wrong");

    Matrix single{{4}};
    Matrix single_inverse{{0.25}};
    CHECK(matrices_match(inverse(single), single_inverse), "inverse of {{4}} is wrong");

    CHECK(matrices_match(inverse(Matrix::identity(3)), Matrix::identity(3)), "inverse of identity(3) is wrong");

    Matrix second_difference{{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    Matrix second_difference_inverse{{0.75, 0.5, 0.25}, {0.5, 1, 0.5}, {0.25, 0.5, 0.75}};
    CHECK(matrices_match(inverse(second_difference), second_difference_inverse),
          "inverse of {{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}} is wrong");

    Matrix zero_diagonal{{0, 2}, {3, 0}};
    Matrix zero_diagonal_inverse{{0, 1.0 / 3}, {0.5, 0}};
    CHECK(matrices_match(inverse(zero_diagonal), zero_diagonal_inverse), "inverse of {{0, 2}, {3, 0}} is wrong");
}

void test_inverse_of_20x20() {
    Matrix m = diagonally_dominant(20, 11);
    Matrix m_inverse = inverse(m);

    CHECK(matrices_match(reference_product(m, m_inverse), Matrix::identity(20)), "m * inverse(m) should be the identity");
    CHECK(matrices_match(reference_product(m_inverse, m), Matrix::identity(20)), "inverse(m) * m should be the identity");
}

void test_inverse_rejects_singular_and_non_square() {
    Matrix proportional{{1, 2}, {2, 4}};
    Matrix nearly_proportional{{1, 2}, {2, 4 + 1e-12}};
    Matrix zero_single{{0}};

    CHECK_THROWS(std::domain_error, inverse(proportional));
    CHECK_THROWS(std::domain_error, inverse(nearly_proportional));
    CHECK_THROWS(std::domain_error, inverse(zero_single));
    CHECK_THROWS(std::domain_error, inverse(Matrix(3, 3)));
    CHECK_THROWS(std::invalid_argument, inverse(Matrix(2, 3)));
}

void test_solve_small_systems() {
    Matrix a{{2, 1}, {1, 3}};
    Matrix b{{3}, {5}};
    Matrix x{{0.8}, {1.4}};
    CHECK(matrices_match(solve(a, b), x), "solving {{2, 1}, {1, 3}} x = {{3}, {5}} is wrong");

    Matrix two_sides{{3, 1}, {5, 0}};
    Matrix two_solutions{{0.8, 0.6}, {1.4, -0.2}};
    CHECK(matrices_match(solve(a, two_sides), two_solutions), "solving with two right-hand sides is wrong");

    Matrix zero_corner{{0, 1}, {1, 1}};
    Matrix zero_corner_b{{2}, {3}};
    Matrix zero_corner_x{{1}, {2}};
    CHECK(matrices_match(solve(zero_corner, zero_corner_b), zero_corner_x), "solving {{0, 1}, {1, 1}} x = {{2}, {3}} is wrong");

    Matrix single{{2}};
    Matrix single_b{{5}};
    Matrix single_x{{2.5}};
    CHECK(matrices_match(solve(single, single_b), single_x), "solving {{2}} x = {{5}} is wrong");

    Matrix rhs{{1, -2}, {3, 4}, {0.5, 0}};
    CHECK(matrices_match(solve(Matrix::identity(3), rhs), rhs), "solving identity(3) x = b should give b");
}

void test_solve_20x20_with_several_right_hand_sides() {
    Matrix a = diagonally_dominant(20, 5);
    Matrix b = random_matrix(20, 3, 9);
    Matrix x = solve(a, b);

    CHECK(x.rows() == 20 && x.cols() == 3, "x is %zu x %zu, expected 20 x 3", x.rows(), x.cols());
    CHECK(matrices_match(reference_product(a, x), b), "a * x should equal b");
}

void test_solve_rejects_bad_input() {
    Matrix proportional{{1, 2}, {2, 4}};
    Matrix consistent_b{{1}, {2}};

    CHECK_THROWS(std::invalid_argument, solve(Matrix(2, 3), Matrix(2, 1)));
    CHECK_THROWS(std::invalid_argument, solve(Matrix::identity(2), Matrix(3, 1)));
    CHECK_THROWS(std::domain_error, solve(proportional, consistent_b));
    CHECK_THROWS(std::domain_error, solve(Matrix(2, 2), Matrix(2, 1)));
}

/* ------------------------------------------------------------------------- */
/* Level 7: LU decomposition                                                 */
/* ------------------------------------------------------------------------- */

bool has_shape(const Matrix& m, std::size_t rows, std::size_t cols, const char* name) {
    if (m.rows() == rows && m.cols() == cols) {
        return true;
    }
    std::printf("    %s is %zu x %zu, expected %zu x %zu\n", name, m.rows(), m.cols(), rows, cols);
    return false;
}

/* Returns true if p is the identity with its rows reordered; otherwise prints why not. */
bool is_permutation(const Matrix& p) {
    std::vector<int> ones_in_column(p.cols(), 0);

    for (std::size_t row = 0; row < p.rows(); row++) {
        int ones_in_row = 0;
        for (std::size_t col = 0; col < p.cols(); col++) {
            double entry = p.at(row, col);
            if (entry == 1) {
                ones_in_row++;
                ones_in_column[col]++;
            } else if (entry != 0) {
                std::printf("    p(%zu, %zu) is %g; a permutation matrix holds only 0s and 1s\n", row, col, entry);
                return false;
            }
        }
        if (ones_in_row != 1) {
            std::printf("    row %zu of p has %d 1s, expected exactly one\n", row, ones_in_row);
            return false;
        }
    }

    for (std::size_t col = 0; col < p.cols(); col++) {
        if (ones_in_column[col] != 1) {
            std::printf("    column %zu of p has %d 1s, expected exactly one\n", col, ones_in_column[col]);
            return false;
        }
    }
    return true;
}

/* Returns true if lu_decompose(m) meets its contract in matrix.h; otherwise prints the first problem. */
bool lu_is_valid(const Matrix& m) {
    std::size_t n = m.rows();
    LU lu = lu_decompose(m);

    if (!has_shape(lu.p, n, n, "p") || !has_shape(lu.l, n, n, "l") || !has_shape(lu.u, n, n, "u")) {
        return false;
    }
    if (!is_permutation(lu.p)) {
        return false;
    }

    for (std::size_t row = 0; row < n; row++) {
        for (std::size_t col = 0; col < n; col++) {
            double l = lu.l.at(row, col);
            if (row == col && !near(l, 1)) {
                std::printf("    l(%zu, %zu) is %.12g; l's diagonal must be 1\n", row, col, l);
                return false;
            }
            if (row < col && !near(l, 0)) {
                std::printf("    l(%zu, %zu) is %.12g; l must be lower triangular\n", row, col, l);
                return false;
            }
            if (row > col && !(std::fabs(l) <= 1 + kTolerance)) {
                std::printf("    l(%zu, %zu) is %.12g; l's entries must be at most 1 in magnitude\n", row, col, l);
                return false;
            }

            double u = lu.u.at(row, col);
            if (row > col && !near(u, 0)) {
                std::printf("    u(%zu, %zu) is %.12g; u must be upper triangular\n", row, col, u);
                return false;
            }
        }
    }

    if (!matrices_match(reference_product(lu.l, lu.u), reference_product(lu.p, m))) {
        std::printf("    l * u should equal p * m\n");
        return false;
    }
    return true;
}

void test_lu_of_small_matrices() {
    Matrix two{{1, 2}, {3, 4}};
    Matrix swap{{0, 1}, {1, 0}};
    Matrix three{{2, 1, 1}, {4, -6, 0}, {-2, 7, 2}};
    Matrix single{{5}};

    CHECK(lu_is_valid(Matrix::identity(3)), "lu_decompose(identity(3)) is wrong");
    CHECK(lu_is_valid(two), "lu_decompose({{1, 2}, {3, 4}}) is wrong");
    CHECK(lu_is_valid(swap), "lu_decompose({{0, 1}, {1, 0}}) is wrong");
    CHECK(lu_is_valid(three), "lu_decompose({{2, 1, 1}, {4, -6, 0}, {-2, 7, 2}}) is wrong");
    CHECK(lu_is_valid(single), "lu_decompose({{5}}) is wrong");
}

void test_lu_of_singular_matrices() {
    Matrix zero_single{{0}};
    Matrix dependent{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix zero_first_columns{{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};
    Matrix ones{{1, 1}, {1, 1}};

    CHECK(lu_is_valid(zero_single), "lu_decompose({{0}}) is wrong");
    CHECK(lu_is_valid(Matrix(3, 3)), "lu_decompose of the 3 x 3 zero matrix is wrong");
    CHECK(lu_is_valid(dependent), "lu_decompose({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}) is wrong");
    CHECK(lu_is_valid(zero_first_columns), "lu_decompose({{0, 0, 1}, {0, 0, 2}, {0, 0, 3}}) is wrong");
    CHECK(lu_is_valid(ones), "lu_decompose({{1, 1}, {1, 1}}) is wrong");
}

void test_lu_of_30x30() {
    CHECK(lu_is_valid(random_matrix(30, 30, 3)), "lu_decompose of a random 30 x 30 matrix is wrong");
}

void test_lu_rejects_non_square() {
    CHECK_THROWS(std::invalid_argument, lu_decompose(Matrix(2, 3)));
    CHECK_THROWS(std::invalid_argument, lu_decompose(Matrix(3, 2)));
}

/* ------------------------------------------------------------------------- */
/* Level 8: QR decomposition and least squares                               */
/* ------------------------------------------------------------------------- */

/* Returns true if qr_decompose(m) meets its contract in matrix.h; otherwise prints the first problem. */
bool qr_is_valid(const Matrix& m) {
    std::size_t rows = m.rows();
    std::size_t cols = m.cols();
    QR qr = qr_decompose(m);

    if (!has_shape(qr.q, rows, cols, "q") || !has_shape(qr.r, cols, cols, "r")) {
        return false;
    }

    if (!matrices_match(reference_product(reference_transpose(qr.q), qr.q), Matrix::identity(cols))) {
        std::printf("    transpose(q) * q should be the identity\n");
        return false;
    }

    for (std::size_t row = 0; row < cols; row++) {
        for (std::size_t col = 0; col < cols; col++) {
            double r = qr.r.at(row, col);
            if (row > col && !near(r, 0)) {
                std::printf("    r(%zu, %zu) is %.12g; r must be upper triangular\n", row, col, r);
                return false;
            }
            if (row == col && !(r > 0)) {
                std::printf("    r(%zu, %zu) is %.12g; r's diagonal must be positive\n", row, col, r);
                return false;
            }
        }
    }

    if (!matrices_match(reference_product(qr.q, qr.r), m)) {
        std::printf("    q * r should equal m\n");
        return false;
    }
    return true;
}

void test_qr_of_small_matrices() {
    // With r's diagonal positive, the factors are unique, so these are exact.
    Matrix two{{3, 0}, {4, 5}};
    Matrix two_q{{0.6, -0.8}, {0.8, 0.6}};
    Matrix two_r{{5, 4}, {0, 3}};
    QR two_qr = qr_decompose(two);
    CHECK(matrices_match(two_qr.q, two_q), "q of {{3, 0}, {4, 5}} is wrong");
    CHECK(matrices_match(two_qr.r, two_r), "r of {{3, 0}, {4, 5}} is wrong");

    Matrix negative{{-2}};
    Matrix negative_q{{-1}};
    Matrix negative_r{{2}};
    QR negative_qr = qr_decompose(negative);
    CHECK(matrices_match(negative_qr.q, negative_q), "q of {{-2}} is wrong");
    CHECK(matrices_match(negative_qr.r, negative_r), "r of {{-2}} is wrong");

    Matrix column{{0}, {3}, {4}};
    Matrix column_q{{0}, {0.6}, {0.8}};
    Matrix column_r{{5}};
    QR column_qr = qr_decompose(column);
    CHECK(matrices_match(column_qr.q, column_q), "q of {{0}, {3}, {4}} is wrong");
    CHECK(matrices_match(column_qr.r, column_r), "r of {{0}, {3}, {4}} is wrong");

    Matrix tall{{1, 1}, {1, 0}, {0, 1}};
    Matrix second_difference{{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    CHECK(qr_is_valid(Matrix::identity(3)), "qr_decompose(identity(3)) is wrong");
    CHECK(qr_is_valid(tall), "qr_decompose({{1, 1}, {1, 0}, {0, 1}}) is wrong");
    CHECK(qr_is_valid(second_difference), "qr_decompose({{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}}) is wrong");
}

void test_qr_of_40x10() {
    CHECK(qr_is_valid(random_matrix(40, 10, 17)), "qr_decompose of a random 40 x 10 matrix is wrong");
}

void test_qr_rejects_bad_input() {
    Matrix wide{{1, 0, 0}, {0, 1, 0}};
    Matrix dependent_columns{{1, 2}, {2, 4}, {3, 6}};
    Matrix zero_column{{1, 0}, {2, 0}};
    Matrix zero_single{{0}};

    CHECK_THROWS(std::invalid_argument, qr_decompose(wide));
    CHECK_THROWS(std::domain_error, qr_decompose(dependent_columns));
    CHECK_THROWS(std::domain_error, qr_decompose(zero_column));
    CHECK_THROWS(std::domain_error, qr_decompose(zero_single));
}

void test_least_squares_with_an_exact_fit() {
    // The points (0, 1), (1, 3), (2, 5), (3, 7) lie on y = 1 + 2x.
    Matrix line{{1, 0}, {1, 1}, {1, 2}, {1, 3}};
    Matrix ys{{1}, {3}, {5}, {7}};
    Matrix coefficients{{1}, {2}};
    CHECK(matrices_match(least_squares(line, ys), coefficients), "fitting points on y = 1 + 2x is wrong");

    // A square invertible system has an exact solution.
    Matrix a{{2, 1}, {1, 3}};
    Matrix b{{3}, {5}};
    Matrix x{{0.8}, {1.4}};
    CHECK(matrices_match(least_squares(a, b), x), "least squares of an invertible system should solve it");
}

void test_least_squares_without_an_exact_fit() {
    // Best line through (0, 1), (1, 2), (2, 2) is y = 7/6 + x/2; through (0, 0), (1, 1), (2, 2) it is y = x.
    Matrix line{{1, 0}, {1, 1}, {1, 2}};
    Matrix ys{{1, 0}, {2, 1}, {2, 2}};
    Matrix coefficients{{7.0 / 6, 0}, {0.5, 1}};
    CHECK(matrices_match(least_squares(line, ys), coefficients), "fitting lines to three points is wrong");

    // For a larger system, the residual a * x - b must be orthogonal to a's columns.
    Matrix a = random_matrix(50, 5, 21);
    Matrix b2 = random_matrix(50, 2, 22);
    Matrix x2 = least_squares(a, b2);
    CHECK(x2.rows() == 5 && x2.cols() == 2, "x is %zu x %zu, expected 5 x 2", x2.rows(), x2.cols());

    Matrix residual = reference_difference(reference_product(a, x2), b2);
    CHECK(matrices_match(reference_product(reference_transpose(a), residual), Matrix(5, 2)),
          "transpose(a) * (a * x - b) should be zero for a random 50 x 5 system");
}

void test_least_squares_rejects_bad_input() {
    Matrix wide{{1, 0, 0}, {0, 1, 0}};
    Matrix tall{{1, 0}, {0, 1}, {1, 1}};
    Matrix dependent_columns{{1, 2}, {2, 4}, {3, 6}};

    CHECK_THROWS(std::invalid_argument, least_squares(wide, Matrix(2, 1)));
    CHECK_THROWS(std::invalid_argument, least_squares(tall, Matrix(2, 1)));
    CHECK_THROWS(std::domain_error, least_squares(dependent_columns, Matrix(3, 1)));
}

/* ------------------------------------------------------------------------- */
/* Level 9: eigenvalues of symmetric matrices                                */
/* ------------------------------------------------------------------------- */

/* Returns true if symmetric_eigenvalues(m) matches expected; otherwise prints the first difference. */
bool eigenvalues_are(const Matrix& m, const std::vector<double>& expected) {
    std::vector<double> actual = symmetric_eigenvalues(m);
    if (actual.size() != expected.size()) {
        std::printf("    expected %zu eigenvalues, got %zu\n", expected.size(), actual.size());
        return false;
    }

    for (std::size_t i = 0; i < expected.size(); i++) {
        if (!near(actual[i], expected[i], kEigenvalueTolerance)) {
            std::printf("    eigenvalue %zu: expected %.12g, got %.12g\n", i, expected[i], actual[i]);
            return false;
        }
    }
    return true;
}

void test_eigenvalues_of_small_matrices() {
    Matrix single{{5}};
    Matrix diagonal{{3, 0, 0}, {0, -1, 0}, {0, 0, 2}};
    Matrix two{{2, 1}, {1, 2}};
    Matrix swap{{0, 1}, {1, 0}};
    Matrix second_difference{{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    double root_two = std::sqrt(2.0);

    CHECK(eigenvalues_are(single, {5}), "eigenvalues of {{5}} are wrong");
    CHECK(eigenvalues_are(diagonal, {-1, 2, 3}), "eigenvalues of a diagonal matrix are wrong");
    CHECK(eigenvalues_are(two, {1, 3}), "eigenvalues of {{2, 1}, {1, 2}} are wrong");
    CHECK(eigenvalues_are(swap, {-1, 1}), "eigenvalues of {{0, 1}, {1, 0}} are wrong");
    CHECK(eigenvalues_are(second_difference, {2 - root_two, 2, 2 + root_two}),
          "eigenvalues of {{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}} are wrong");
    CHECK(eigenvalues_are(Matrix(2, 2), {0, 0}), "eigenvalues of the zero matrix are wrong");
}

void test_repeated_eigenvalues() {
    Matrix scaled_identity{{3, 0, 0}, {0, 3, 0}, {0, 0, 3}};
    Matrix ones{{1, 1}, {1, 1}};

    // Reflection across the plane orthogonal to (1, 1, 1).
    double third = 1.0 / 3;
    Matrix reflection{{third, -2 * third, -2 * third}, {-2 * third, third, -2 * third}, {-2 * third, -2 * third, third}};

    CHECK(eigenvalues_are(scaled_identity, {3, 3, 3}), "eigenvalues of 3 * identity(3) are wrong");
    CHECK(eigenvalues_are(ones, {0, 2}), "eigenvalues of {{1, 1}, {1, 1}} are wrong");
    CHECK(eigenvalues_are(reflection, {-1, 1, 1}), "eigenvalues of a reflection are wrong");
}

void test_eigenvalues_of_a_rotated_diagonal_matrix() {
    // q * d * transpose(q) has d's diagonal as its eigenvalues when q is a rotation.
    Matrix d(5, 5);
    const double diagonal[] = {5, -2, 0.5, 3, -2};
    for (std::size_t i = 0; i < 5; i++) {
        d.at(i, i) = diagonal[i];
    }

    Matrix q = Matrix::identity(5);
    q = reference_product(q, rotation(5, 0, 1, 0.3));
    q = reference_product(q, rotation(5, 1, 2, 0.7));
    q = reference_product(q, rotation(5, 2, 3, 1.1));
    q = reference_product(q, rotation(5, 3, 4, 0.4));
    q = reference_product(q, rotation(5, 0, 4, 0.9));
    q = reference_product(q, rotation(5, 1, 3, 1.3));
    Matrix m = reference_product(reference_product(q, d), reference_transpose(q));

    CHECK(eigenvalues_are(m, {-2, -2, 0.5, 3, 5}), "eigenvalues of a rotated diagonal 5 x 5 matrix are wrong");
}

void test_eigenvalues_of_20x20_second_difference() {
    // 2 on the diagonal and -1 beside it has eigenvalues 2 - 2 cos(k pi / 21) for k = 1..20.
    const std::size_t n = 20;
    const double pi = std::acos(-1.0);
    Matrix m(n, n);
    std::vector<double> expected;

    for (std::size_t i = 0; i < n; i++) {
        m.at(i, i) = 2;
        if (i + 1 < n) {
            m.at(i, i + 1) = -1;
            m.at(i + 1, i) = -1;
        }
        expected.push_back(2 - 2 * std::cos(static_cast<double>(i + 1) * pi / (n + 1)));
    }

    CHECK(eigenvalues_are(m, expected), "eigenvalues of the 20 x 20 second-difference matrix are wrong");
}

void test_eigenvalues_check_symmetry() {
    Matrix nearly_symmetric{{1, 2}, {2 + 1e-12, 1}};
    CHECK(eigenvalues_are(nearly_symmetric, {-1, 3}), "{{1, 2}, {2 + 1e-12, 1}} counts as symmetric; its eigenvalues are wrong");

    Matrix asymmetric{{1, 2}, {3, 4}};
    Matrix slightly_asymmetric{{1, 2, 0}, {2, 1, 0}, {0, 1e-6, 1}};
    CHECK_THROWS(std::invalid_argument, symmetric_eigenvalues(asymmetric));
    CHECK_THROWS(std::invalid_argument, symmetric_eigenvalues(slightly_asymmetric));
    CHECK_THROWS(std::invalid_argument, symmetric_eigenvalues(Matrix(2, 3)));
}

/* ------------------------------------------------------------------------- */
/* Runner                                                                    */
/* ------------------------------------------------------------------------- */

const int kLevelCount = 9;

const char* const kLevelNames[kLevelCount + 1] = {
    "",
    "the Matrix type",
    "entry-wise operations",
    "multiplication and powers",
    "determinants",
    "row reduction and rank",
    "inverses and linear systems",
    "LU decomposition",
    "QR decomposition and least squares",
    "eigenvalues of symmetric matrices",
};

struct Test {
    int level;
    const char* name;
    void (*run)();
};

const Test kTests[] = {
    {1, "shape constructor fills zeros", test_shape_constructor_fills_zeros},
    {1, "list constructor fills rows in order", test_list_constructor_fills_rows_in_order},
    {1, "at reads and writes entries", test_at_reads_and_writes_entries},
    {1, "identity", test_identity},
    {1, "rejects zero rows or columns", test_rejects_zero_rows_or_columns},
    {1, "rejects empty or ragged rows", test_rejects_empty_or_ragged_rows},
    {1, "rejects out-of-range indexes", test_rejects_out_of_range_indexes},
    {1, "copies are independent", test_copies_are_independent},
    {1, "equality", test_equality},

    {2, "add and subtract", test_add_and_subtract},
    {2, "add and subtract reject shape mismatch", test_add_and_subtract_reject_shape_mismatch},
    {2, "scalar multiplication", test_scalar_multiplication},
    {2, "transpose", test_transpose},
    {2, "trace", test_trace},
    {2, "trace rejects non-square", test_trace_rejects_non_square},

    {3, "multiply", test_multiply},
    {3, "identity is neutral and order matters", test_multiply_identity_and_order},
    {3, "multiply rejects mismatched shapes", test_multiply_rejects_mismatched_shapes},
    {3, "power of small exponents", test_power_of_small_exponents},
    {3, "power rejects non-square", test_power_rejects_non_square},
    {3, "power of large exponents is fast", test_power_of_large_exponents_is_fast},

    {4, "small matrices", test_determinant_of_small_matrices},
    {4, "zero on the diagonal", test_determinant_with_zero_on_the_diagonal},
    {4, "singular matrices", test_determinant_of_singular_matrices},
    {4, "row operations", test_determinant_under_row_operations},
    {4, "rejects non-square", test_determinant_rejects_non_square},
    {4, "10 x 10 is fast", test_determinant_of_10x10_is_fast},

    {5, "rref of invertible matrices", test_rref_of_invertible_matrices},
    {5, "rref of singular and rectangular matrices", test_rref_of_singular_and_rectangular_matrices},
    {5, "rref treats tiny values as zero", test_rref_treats_tiny_values_as_zero},
    {5, "rank", test_rank},
    {5, "rank treats tiny values as zero", test_rank_treats_tiny_values_as_zero},

    {6, "inverse of small matrices", test_inverse_of_small_matrices},
    {6, "inverse of 20 x 20", test_inverse_of_20x20},
    {6, "inverse rejects singular and non-square", test_inverse_rejects_singular_and_non_square},
    {6, "solve small systems", test_solve_small_systems},
    {6, "solve 20 x 20 with several right-hand sides", test_solve_20x20_with_several_right_hand_sides},
    {6, "solve rejects bad input", test_solve_rejects_bad_input},

    {7, "small matrices", test_lu_of_small_matrices},
    {7, "singular matrices", test_lu_of_singular_matrices},
    {7, "30 x 30", test_lu_of_30x30},
    {7, "rejects non-square", test_lu_rejects_non_square},

    {8, "qr of small matrices", test_qr_of_small_matrices},
    {8, "qr of 40 x 10", test_qr_of_40x10},
    {8, "qr rejects bad input", test_qr_rejects_bad_input},
    {8, "least squares with an exact fit", test_least_squares_with_an_exact_fit},
    {8, "least squares without an exact fit", test_least_squares_without_an_exact_fit},
    {8, "least squares rejects bad input", test_least_squares_rejects_bad_input},

    {9, "small matrices", test_eigenvalues_of_small_matrices},
    {9, "repeated eigenvalues", test_repeated_eigenvalues},
    {9, "rotated diagonal matrix", test_eigenvalues_of_a_rotated_diagonal_matrix},
    {9, "20 x 20 second-difference matrix", test_eigenvalues_of_20x20_second_difference},
    {9, "checks symmetry", test_eigenvalues_check_symmetry},
};

}  // namespace

int main(int argc, char** argv) {
    // 0 runs every level.
    int selected_level = 0;
    if (argc == 2) {
        selected_level = std::atoi(argv[1]);
    }
    if (argc > 2 || (argc == 2 && (selected_level < 1 || selected_level > kLevelCount))) {
        std::fprintf(stderr, "usage: %s [level 1-%d]\n", argv[0], kLevelCount);
        return EXIT_FAILURE;
    }

    int passed[kLevelCount + 1] = {};
    int total[kLevelCount + 1] = {};
    int current_level = 0;

    for (const Test& test : kTests) {
        if (selected_level != 0 && test.level != selected_level) {
            continue;
        }

        if (test.level != current_level) {
            current_level = test.level;
            std::printf("\nLevel %d: %s\n", current_level, kLevelNames[current_level]);
        }

        std::printf("[ RUN  ] %s\n", test.name);
        std::fflush(stdout);
        test_failed = false;

        try {
            test.run();
        } catch (const std::exception& error) {
            std::printf("    threw: %s\n", error.what());
            test_failed = true;
        } catch (...) {
            std::printf("    threw something that is not a std::exception\n");
            test_failed = true;
        }

        std::printf("[ %s ] %s\n", test_failed ? "FAIL" : " OK ", test.name);
        total[test.level]++;
        passed[test.level] += test_failed ? 0 : 1;
    }

    int all_passed = 0;
    int all_total = 0;
    std::printf("\nSummary\n");
    for (int level = 1; level <= kLevelCount; level++) {
        if (total[level] == 0) {
            continue;
        }
        std::printf("  Level %d  %-36s %d/%d\n", level, kLevelNames[level], passed[level], total[level]);
        all_passed += passed[level];
        all_total += total[level];
    }
    std::printf("\n%d/%d tests passed\n", all_passed, all_total);

    return all_passed == all_total ? EXIT_SUCCESS : EXIT_FAILURE;
}
