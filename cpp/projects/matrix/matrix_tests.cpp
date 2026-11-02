#include "matrix.h"

#include <concepts>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <initializer_list>
#include <stdexcept>

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

using linalg::Matrix;

namespace {

bool test_failed;

template <typename M>
concept readable_through_const = requires(const M& m) {
    { m.rows() } -> std::convertible_to<std::size_t>;
    { m.cols() } -> std::convertible_to<std::size_t>;
    { m[0][0] } -> std::convertible_to<double>;
};

template <typename M>
concept writable_through_index = requires(M& m) { m[0][0] = 1.0; };

static_assert(readable_through_const<Matrix>, "rows(), cols() and [r][c] should work on a const Matrix");
static_assert(writable_through_index<Matrix>, "[r][c] on a Matrix should return a reference you can write through");
static_assert(!writable_through_index<const Matrix>, "[r][c] on a const Matrix must not allow writing");

void test_reports_its_shape() {
    Matrix m(2, 3);
    CHECK(m.rows() == 2 && m.cols() == 3, "Matrix(2, 3) is %zu x %zu", m.rows(), m.cols());

    Matrix tall(3, 2);
    CHECK(tall.rows() == 3 && tall.cols() == 2, "Matrix(3, 2) is %zu x %zu", tall.rows(), tall.cols());
}

void test_single_entry() {
    Matrix m(1, 1);
    CHECK(m.rows() == 1 && m.cols() == 1, "Matrix(1, 1) is %zu x %zu", m.rows(), m.cols());
}

void test_row_and_column_vectors() {
    Matrix row(1, 5);
    CHECK(row.rows() == 1 && row.cols() == 5, "Matrix(1, 5) is %zu x %zu", row.rows(), row.cols());

    Matrix column(5, 1);
    CHECK(column.rows() == 5 && column.cols() == 1, "Matrix(5, 1) is %zu x %zu",
          column.rows(), column.cols());
}

void test_large_shape() {
    Matrix m(1000, 2000);
    CHECK(m.rows() == 1000 && m.cols() == 2000, "Matrix(1000, 2000) is %zu x %zu", m.rows(), m.cols());
}

void test_rejects_zero_rows_or_columns() {
    CHECK_THROWS(std::invalid_argument, Matrix(0, 3));
    CHECK_THROWS(std::invalid_argument, Matrix(3, 0));
    CHECK_THROWS(std::invalid_argument, Matrix(0, 0));
}

void test_new_entries_are_zero() {
    Matrix m(2, 3);
    for (std::size_t row = 0; row < 2; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            CHECK(m[row][col] == 0, "Matrix(2, 3)[%zu][%zu] is %g, expected 0",
                  row, col, m[row][col]);
        }
    }
}

void test_index_writes_and_reads_entries() {
    Matrix m(2, 2);
    m[1][0] = 7;
    m[0][1] = -2.5;

    CHECK(m[1][0] == 7, "after writing 7 to (1, 0), it reads %g", m[1][0]);
    CHECK(m[0][1] == -2.5, "after writing -2.5 to (0, 1), it reads %g", m[0][1]);
    CHECK(m[0][0] == 0 && m[1][1] == 0, "writing two entries changed another one");
}

void test_index_returns_a_reference() {
    Matrix m(2, 2);

    double& entry = m[1][1];
    entry = 4;
    CHECK(m[1][1] == 4, "writing 4 through a saved reference to (1, 1) left it at %g", m[1][1]);

    m[1][1] += 1.5;
    CHECK(m[1][1] == 5.5, "after += 1.5, (1, 1) is %g, expected 5.5", m[1][1]);
}

void test_every_entry_is_separate() {
    Matrix m(3, 4);
    for (std::size_t row = 0; row < 3; row++) {
        for (std::size_t col = 0; col < 4; col++) {
            m[row][col] = row * 10.0 + col;
        }
    }

    for (std::size_t row = 0; row < 3; row++) {
        for (std::size_t col = 0; col < 4; col++) {
            double expected = row * 10.0 + col;
            CHECK(m[row][col] == expected, "Matrix(3, 4)[%zu][%zu] is %g, expected %g",
                  row, col, m[row][col], expected);
        }
    }
}

void test_row_and_column_vector_entries() {
    Matrix row(1, 5);
    row[0][4] = 3;
    CHECK(row[0][4] == 3, "Matrix(1, 5)[0][4] is %g, expected 3", row[0][4]);

    Matrix column(5, 1);
    column[4][0] = 3;
    CHECK(column[4][0] == 3, "Matrix(5, 1)[4][0] is %g, expected 3", column[4][0]);
}

void test_entries_keep_fractions_and_extremes() {
    Matrix m(1, 4);
    m[0][0] = 0.1;
    m[0][1] = -1e300;
    m[0][2] = 1e-300;
    m[0][3] = -0.5;

    CHECK(m[0][0] == 0.1, "stored 0.1, read %g", m[0][0]);
    CHECK(m[0][1] == -1e300, "stored -1e300, read %g", m[0][1]);
    CHECK(m[0][2] == 1e-300, "stored 1e-300, read %g", m[0][2]);
    CHECK(m[0][3] == -0.5, "stored -0.5, read %g", m[0][3]);
}

void test_list_constructor_sets_shape() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    CHECK(m.rows() == 2 && m.cols() == 3, "{{1, 2, 3}, {4, 5, 6}} is %zu x %zu", m.rows(), m.cols());

    Matrix tall{{1, 2}, {3, 4}, {5, 6}};
    CHECK(tall.rows() == 3 && tall.cols() == 2, "{{1, 2}, {3, 4}, {5, 6}} is %zu x %zu",
          tall.rows(), tall.cols());
}

void test_list_constructor_fills_rows_in_order() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    const double expected[2][3] = {{1, 2, 3}, {4, 5, 6}};

    for (std::size_t row = 0; row < 2; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            CHECK(m[row][col] == expected[row][col], "{{1, 2, 3}, {4, 5, 6}}[%zu][%zu] is %g, expected %g",
                  row, col, m[row][col], expected[row][col]);
        }
    }
}

void test_list_constructor_row_and_column_vectors() {
    Matrix row{{1, 2, 3, 4}};
    CHECK(row.rows() == 1 && row.cols() == 4, "{{1, 2, 3, 4}} is %zu x %zu", row.rows(), row.cols());
    CHECK(row[0][3] == 4, "{{1, 2, 3, 4}}[0][3] is %g, expected 4", row[0][3]);

    Matrix column{{1}, {2}, {3}};
    CHECK(column.rows() == 3 && column.cols() == 1, "{{1}, {2}, {3}} is %zu x %zu",
          column.rows(), column.cols());
    CHECK(column[2][0] == 3, "{{1}, {2}, {3}}[2][0] is %g, expected 3", column[2][0]);
}

void test_list_constructor_single_entry() {
    Matrix m{{-7.5}};
    CHECK(m.rows() == 1 && m.cols() == 1, "{{-7.5}} is %zu x %zu", m.rows(), m.cols());
    CHECK(m[0][0] == -7.5, "{{-7.5}}[0][0] is %g, expected -7.5", m[0][0]);
}

void test_list_constructor_keeps_fractions() {
    Matrix m{{0.1, -0.25}, {1e-300, -1e300}};
    CHECK(m[0][0] == 0.1, "stored 0.1, read %g", m[0][0]);
    CHECK(m[0][1] == -0.25, "stored -0.25, read %g", m[0][1]);
    CHECK(m[1][0] == 1e-300, "stored 1e-300, read %g", m[1][0]);
    CHECK(m[1][1] == -1e300, "stored -1e300, read %g", m[1][1]);
}

void test_list_built_matrix_can_change() {
    Matrix m{{1, 2}, {3, 4}};
    m[0][1] = 9;

    CHECK(m[0][1] == 9, "after writing 9 to (0, 1), it reads %g", m[0][1]);
    CHECK(m[0][0] == 1 && m[1][0] == 3 && m[1][1] == 4, "writing (0, 1) changed another entry");
}

void test_list_constructor_rejects_empty_input() {
    std::initializer_list<std::initializer_list<double>> no_rows = {};
    CHECK_THROWS(std::invalid_argument, Matrix(no_rows));
    CHECK_THROWS(std::invalid_argument, Matrix{{}});
    CHECK_THROWS(std::invalid_argument, Matrix{{}, {}});
}

void test_list_constructor_rejects_ragged_rows() {
    CHECK_THROWS(std::invalid_argument, Matrix{{1, 2}, {}});
    CHECK_THROWS(std::invalid_argument, Matrix{{}, {1, 2}});
    CHECK_THROWS(std::invalid_argument, Matrix{{1, 2}, {3}});
    CHECK_THROWS(std::invalid_argument, Matrix{{1}, {2, 3}});
    CHECK_THROWS(std::invalid_argument, Matrix{{1, 2}, {3, 4}, {5, 6, 7}});
}

void test_equal_matrices_compare_equal() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{1, 2, 3}, {4, 5, 6}};
    CHECK(a == b, "two copies of {{1, 2, 3}, {4, 5, 6}} should be equal");
    CHECK(b == a, "equality should not depend on the order of the operands");
    CHECK(a == a, "a matrix should equal itself");

    Matrix single{{-7.5}};
    Matrix also_single{{-7.5}};
    CHECK(single == also_single, "{{-7.5}} should equal {{-7.5}}");
}

void test_equal_matrices_built_differently() {
    Matrix built{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix written_diagonal(3, 3);
    for (std::size_t i = 0; i < 3; i++) {
        written_diagonal[i][i] = 1;
    }
    CHECK(built == written_diagonal, "{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} should equal a 3 x 3 zero matrix with 1s written on the diagonal");

    Matrix zeros(2, 2);
    Matrix listed{{0, 0}, {0, 0}};
    CHECK(zeros == listed, "Matrix(2, 2) should equal {{0, 0}, {0, 0}}");

    Matrix written(2, 2);
    written[0][1] = 3;
    written[1][0] = -1;
    Matrix expected{{0, 3}, {-1, 0}};
    CHECK(written == expected, "a matrix filled with [r][c] should equal the same entries written as a list");
}

void test_one_different_entry_makes_unequal() {
    Matrix base{{1, 2, 3}, {4, 5, 6}};

    for (std::size_t row = 0; row < 2; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            Matrix changed{{1, 2, 3}, {4, 5, 6}};
            changed[row][col] += 0.5;
            CHECK(!(base == changed), "matrices that differ only at (%zu, %zu) compared equal", row, col);
            CHECK(!(changed == base), "matrices that differ only at (%zu, %zu) compared equal", row, col);
        }
    }
}

void test_different_shapes_are_unequal() {
    CHECK(!(Matrix(2, 3) == Matrix(3, 2)), "a 2 x 3 and a 3 x 2 matrix of zeros compared equal");
    CHECK(!(Matrix(1, 4) == Matrix(4, 1)), "a 1 x 4 and a 4 x 1 matrix of zeros compared equal");
    CHECK(!(Matrix(2, 2) == Matrix(2, 3)), "a 2 x 2 and a 2 x 3 matrix of zeros compared equal");
    CHECK(!(Matrix(2, 3) == Matrix(2, 2)), "a 2 x 3 and a 2 x 2 matrix of zeros compared equal");
    CHECK(!(Matrix(2, 2) == Matrix(3, 2)), "a 2 x 2 and a 3 x 2 matrix of zeros compared equal");
    CHECK(!(Matrix(3, 2) == Matrix(2, 2)), "a 3 x 2 and a 2 x 2 matrix of zeros compared equal");

    Matrix small{{1, 2}, {3, 4}};
    Matrix bigger{{1, 2, 0}, {3, 4, 0}};
    CHECK(!(small == bigger), "{{1, 2}, {3, 4}} compared equal to {{1, 2, 0}, {3, 4, 0}}");
    CHECK(!(bigger == small), "{{1, 2, 0}, {3, 4, 0}} compared equal to {{1, 2}, {3, 4}}");
}

void test_entries_must_match_exactly() {
    Matrix sum{{0.1 + 0.2}};
    Matrix exact{{0.3}};
    CHECK(!(sum == exact), "{{0.1 + 0.2}} compared equal to {{0.3}}, but the doubles differ");

    Matrix a{{1}};
    Matrix b{{1 + 1e-12}};
    CHECK(!(a == b), "{{1}} compared equal to {{1 + 1e-12}}");
}

void test_not_equal() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix same{{1, 2}, {3, 4}};
    Matrix different{{1, 2}, {3, 5}};

    CHECK(!(a != same), "a != same should be false for equal matrices");
    CHECK(a != different, "a != different should be true when an entry differs");
    CHECK(Matrix(2, 3) != Matrix(3, 2), "Matrix(2, 3) != Matrix(3, 2) should be true");
}

void test_comparison_leaves_matrices_unchanged() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{1, 2}, {3, 5}};
    (void)(a == b);

    CHECK(a.rows() == 2 && a.cols() == 2 && a[1][1] == 4, "comparing changed the left matrix");
    CHECK(b.rows() == 2 && b.cols() == 2 && b[1][1] == 5, "comparing changed the right matrix");
}

void test_add() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};
    Matrix expected{{11, 22}, {33, 44}};
    CHECK(a + b == expected, "{{1, 2}, {3, 4}} + {{10, 20}, {30, 40}} should be {{11, 22}, {33, 44}}");
}

void test_subtract() {
    Matrix a{{10, 20}, {30, 40}};
    Matrix b{{1, 2}, {3, 4}};
    Matrix expected{{9, 18}, {27, 36}};
    CHECK(a - b == expected, "{{10, 20}, {30, 40}} - {{1, 2}, {3, 4}} should be {{9, 18}, {27, 36}}");

    Matrix reversed{{-9, -18}, {-27, -36}};
    CHECK(b - a == reversed, "{{1, 2}, {3, 4}} - {{10, 20}, {30, 40}} should be {{-9, -18}, {-27, -36}}");
}

void test_add_and_subtract_non_square() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{6, 5, 4}, {3, 2, 1}};
    Matrix sum{{7, 7, 7}, {7, 7, 7}};
    Matrix difference{{-5, -3, -1}, {1, 3, 5}};

    Matrix result = a + b;
    CHECK(result.rows() == 2 && result.cols() == 3, "a 2 x 3 sum is %zu x %zu", result.rows(), result.cols());
    CHECK(result == sum, "{{1, 2, 3}, {4, 5, 6}} + {{6, 5, 4}, {3, 2, 1}} should be all 7s");
    CHECK(a - b == difference, "{{1, 2, 3}, {4, 5, 6}} - {{6, 5, 4}, {3, 2, 1}} should be {{-5, -3, -1}, {1, 3, 5}}");

    Matrix column{{1}, {2}, {3}};
    Matrix doubled{{2}, {4}, {6}};
    CHECK(column + column == doubled, "{{1}, {2}, {3}} + itself should be {{2}, {4}, {6}}");
}

void test_add_and_subtract_single_entry() {
    CHECK(Matrix{{2.5}} + Matrix{{-4}} == Matrix{{-1.5}}, "{{2.5}} + {{-4}} should be {{-1.5}}");
    CHECK(Matrix{{2.5}} - Matrix{{-4}} == Matrix{{6.5}}, "{{2.5}} - {{-4}} should be {{6.5}}");
}

void test_zero_matrix_changes_nothing() {
    Matrix a{{1, -2}, {3.5, 0}};
    CHECK(a + Matrix(2, 2) == a, "adding a zero matrix changed the matrix");
    CHECK(Matrix(2, 2) + a == a, "adding to a zero matrix should give the other matrix");
    CHECK(a - Matrix(2, 2) == a, "subtracting a zero matrix changed the matrix");
    CHECK(a - a == Matrix(2, 2), "a matrix minus itself should be all zeros");
}

void test_add_is_commutative() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{-1, 0.5, 8}, {2, -7, 0.25}};
    CHECK(a + b == b + a, "a + b should equal b + a");
}

void test_add_and_subtract_chain() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{5, 6}, {7, 8}};
    Matrix c{{-1, -1}, {-1, -1}};

    Matrix expected{{5, 7}, {9, 11}};
    CHECK(a + b + c == expected, "{{1, 2}, {3, 4}} + {{5, 6}, {7, 8}} + {{-1, -1}, {-1, -1}} should be {{5, 7}, {9, 11}}");
    CHECK(a + b - b == a, "a + b - b should equal a");
    CHECK((a - b) + b == a, "(a - b) + b should equal a");
}

void test_add_and_subtract_leave_operands_unchanged() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};
    Matrix a_before{{1, 2}, {3, 4}};
    Matrix b_before{{10, 20}, {30, 40}};

    (void)(a + b);
    (void)(a - b);
    CHECK(a == a_before, "a + b or a - b changed a");
    CHECK(b == b_before, "a + b or a - b changed b");
}

void test_sum_is_a_separate_matrix() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};
    Matrix sum = a + b;

    sum[0][0] = 100;
    CHECK(a[0][0] == 1 && b[0][0] == 10, "changing the sum changed one of the operands");
}

void test_large_add_and_subtract() {
    const std::size_t n = 100;
    Matrix a(n, n);
    Matrix b(n, n);
    Matrix sum(n, n);
    Matrix difference(n, n);

    for (std::size_t row = 0; row < n; row++) {
        for (std::size_t col = 0; col < n; col++) {
            a[row][col] = row * 3.0 + col;
            b[row][col] = col * 2.0 - row;
            sum[row][col] = row * 2.0 + col * 3.0;
            difference[row][col] = row * 4.0 - col;
        }
    }

    CHECK(a + b == sum, "a 100 x 100 sum is wrong");
    CHECK(a - b == difference, "a 100 x 100 difference is wrong");
}

void test_add_and_subtract_reject_shape_mismatch() {
    CHECK_THROWS(std::invalid_argument, Matrix(2, 3) + Matrix(3, 2));
    CHECK_THROWS(std::invalid_argument, Matrix(2, 2) + Matrix(2, 3));
    CHECK_THROWS(std::invalid_argument, Matrix(2, 3) + Matrix(2, 2));
    CHECK_THROWS(std::invalid_argument, Matrix(3, 2) + Matrix(2, 2));
    CHECK_THROWS(std::invalid_argument, Matrix(1, 1) + Matrix(2, 2));

    CHECK_THROWS(std::invalid_argument, Matrix(2, 3) - Matrix(3, 2));
    CHECK_THROWS(std::invalid_argument, Matrix(2, 2) - Matrix(2, 3));
    CHECK_THROWS(std::invalid_argument, Matrix(2, 3) - Matrix(2, 2));
    CHECK_THROWS(std::invalid_argument, Matrix(3, 2) - Matrix(2, 2));
    CHECK_THROWS(std::invalid_argument, Matrix(2, 2) - Matrix(1, 1));
}

void test_scalar_times_matrix() {
    Matrix m{{1, 2}, {3, 4}};
    Matrix expected{{3, 6}, {9, 12}};
    CHECK(3 * m == expected, "3 * {{1, 2}, {3, 4}} should be {{3, 6}, {9, 12}}");
}

void test_matrix_times_scalar() {
    Matrix m{{1, 2}, {3, 4}};
    Matrix expected{{3, 6}, {9, 12}};
    CHECK(m * 3 == expected, "{{1, 2}, {3, 4}} * 3 should be {{3, 6}, {9, 12}}");
}

void test_scalar_order_does_not_matter() {
    Matrix m{{1.5, -2, 0}, {4, 0.25, -8}};
    CHECK(2.5 * m == m * 2.5, "2.5 * m should equal m * 2.5");
    CHECK(-4 * m == m * -4, "-4 * m should equal m * -4");
}

void test_scalar_multiplication_non_square() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    Matrix expected{{-2, -4, -6}, {-8, -10, -12}};

    Matrix left = -2 * m;
    CHECK(left.rows() == 2 && left.cols() == 3, "-2 * (a 2 x 3 matrix) is %zu x %zu", left.rows(), left.cols());
    CHECK(left == expected, "-2 * {{1, 2, 3}, {4, 5, 6}} is wrong");

    Matrix right = m * -2;
    CHECK(right.rows() == 2 && right.cols() == 3, "(a 2 x 3 matrix) * -2 is %zu x %zu", right.rows(), right.cols());
    CHECK(right == expected, "{{1, 2, 3}, {4, 5, 6}} * -2 is wrong");

    Matrix column{{1}, {2}, {3}};
    Matrix halved{{0.5}, {1}, {1.5}};
    CHECK(0.5 * column == halved, "0.5 * {{1}, {2}, {3}} should be {{0.5}, {1}, {1.5}}");
    CHECK(column * 0.5 == halved, "{{1}, {2}, {3}} * 0.5 should be {{0.5}, {1}, {1.5}}");
}

void test_multiply_by_zero_one_and_minus_one() {
    Matrix m{{1, -2, 3.5}, {0, 7, -0.5}};

    CHECK(0 * m == Matrix(2, 3), "0 * m should be a 2 x 3 matrix of zeros");
    CHECK(m * 0 == Matrix(2, 3), "m * 0 should be a 2 x 3 matrix of zeros");
    CHECK(1 * m == m, "1 * m should equal m");
    CHECK(m * 1 == m, "m * 1 should equal m");

    Matrix negated{{-1, 2, -3.5}, {0, -7, 0.5}};
    CHECK(-1 * m == negated, "-1 * m should negate every entry");
    CHECK(m + m * -1 == Matrix(2, 3), "m + m * -1 should be all zeros");
}

void test_scalar_multiplication_single_entry() {
    CHECK(4 * Matrix{{-2.5}} == Matrix{{-10}}, "4 * {{-2.5}} should be {{-10}}");
    CHECK(Matrix{{-2.5}} * 4 == Matrix{{-10}}, "{{-2.5}} * 4 should be {{-10}}");
}

void test_scalar_multiplication_chain() {
    Matrix m{{1, 2}, {3, 4}};
    CHECK(m * 2 * 3 == m * 6, "m * 2 * 3 should equal m * 6");
    CHECK(2 * (3 * m) == 6 * m, "2 * (3 * m) should equal 6 * m");
    CHECK(2 * m * 3 == 6 * m, "2 * m * 3 should equal 6 * m");
}

void test_scalar_distributes_over_add() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{5, -6}, {0, 8}};
    CHECK(3 * (a + b) == 3 * a + 3 * b, "3 * (a + b) should equal 3 * a + 3 * b");
    CHECK((a - b) * 2 == a * 2 - b * 2, "(a - b) * 2 should equal a * 2 - b * 2");
    CHECK(a + a == 2 * a, "a + a should equal 2 * a");
}

void test_scalar_multiplication_leaves_matrix_unchanged() {
    Matrix m{{1, 2}, {3, 4}};
    Matrix before{{1, 2}, {3, 4}};

    (void)(5 * m);
    CHECK(m == before, "5 * m changed m");

    (void)(m * 5);
    CHECK(m == before, "m * 5 changed m");
}

void test_scaled_matrix_is_separate() {
    Matrix m{{1, 2}, {3, 4}};

    Matrix left = 2 * m;
    left[0][0] = 100;
    CHECK(m[0][0] == 1, "changing 2 * m changed m");

    Matrix right = m * 2;
    right[1][1] = 100;
    CHECK(m[1][1] == 4, "changing m * 2 changed m");
}

void test_large_scalar_multiplication() {
    const std::size_t n = 100;
    Matrix m(n, n);
    Matrix expected(n, n);

    for (std::size_t row = 0; row < n; row++) {
        for (std::size_t col = 0; col < n; col++) {
            m[row][col] = row * 3.0 - col;
            expected[row][col] = row * -1.5 + col * 0.5;
        }
    }

    CHECK(-0.5 * m == expected, "-0.5 times a 100 x 100 matrix is wrong");
    CHECK(m * -0.5 == expected, "a 100 x 100 matrix times -0.5 is wrong");
}

void test_transpose_non_square() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    Matrix t = transpose(m);
    Matrix expected{{1, 4}, {2, 5}, {3, 6}};

    CHECK(t.rows() == 3 && t.cols() == 2, "the transpose of a 2 x 3 matrix is %zu x %zu", t.rows(), t.cols());
    CHECK(t == expected, "transpose({{1, 2, 3}, {4, 5, 6}}) should be {{1, 4}, {2, 5}, {3, 6}}");

    Matrix tall{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Matrix wide{{1, 3, 5, 7}, {2, 4, 6, 8}};
    CHECK(transpose(tall) == wide, "transpose of a 4 x 2 matrix is wrong");
}

void test_transpose_square() {
    Matrix m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix expected{{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    CHECK(transpose(m) == expected, "transpose of {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} is wrong");
}

void test_transpose_row_and_column_vectors() {
    Matrix row{{1, 2, 3, 4}};
    Matrix column{{1}, {2}, {3}, {4}};
    CHECK(transpose(row) == column, "transpose of {{1, 2, 3, 4}} should be {{1}, {2}, {3}, {4}}");
    CHECK(transpose(column) == row, "transpose of {{1}, {2}, {3}, {4}} should be {{1, 2, 3, 4}}");
}

void test_transpose_single_entry() {
    CHECK(transpose(Matrix{{-7.5}}) == Matrix{{-7.5}}, "transpose of {{-7.5}} should be {{-7.5}}");
}

void test_transpose_twice_gives_original() {
    Matrix m{{1, -2, 3.5}, {0, 7, -0.25}};
    CHECK(transpose(transpose(m)) == m, "transposing twice should give back the original matrix");
}

void test_symmetric_matrices_are_their_own_transpose() {
    Matrix diagonal{{3, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, 0.5, 0}, {0, 0, 0, 2}};
    CHECK(transpose(diagonal) == diagonal, "a diagonal matrix should equal its transpose");

    Matrix symmetric{{1, 2, 3}, {2, 5, 6}, {3, 6, 9}};
    CHECK(transpose(symmetric) == symmetric, "a symmetric matrix should equal its transpose");
}

void test_transpose_with_add_and_scale() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{-1, 0, 2}, {8, -3, 0.5}};
    CHECK(transpose(a + b) == transpose(a) + transpose(b), "transpose(a + b) should equal transpose(a) + transpose(b)");
    CHECK(transpose(a - b) == transpose(a) - transpose(b), "transpose(a - b) should equal transpose(a) - transpose(b)");
    CHECK(transpose(3 * a) == 3 * transpose(a), "transpose(3 * a) should equal 3 * transpose(a)");
}

void test_transpose_leaves_matrix_unchanged() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    Matrix before{{1, 2, 3}, {4, 5, 6}};

    (void)transpose(m);
    CHECK(m == before, "transpose(m) changed m");
}

void test_transpose_is_separate() {
    Matrix m{{1, 2}, {3, 4}};
    Matrix t = transpose(m);

    t[0][1] = 100;
    CHECK(m[0][1] == 2 && m[1][0] == 3, "changing the transpose changed the original");
}

void test_large_transpose() {
    const std::size_t rows = 60;
    const std::size_t cols = 150;
    Matrix m(rows, cols);
    for (std::size_t row = 0; row < rows; row++) {
        for (std::size_t col = 0; col < cols; col++) {
            m[row][col] = row * 1000.0 + col;
        }
    }

    Matrix t = transpose(m);
    CHECK(t.rows() == cols && t.cols() == rows, "the transpose of a 60 x 150 matrix is %zu x %zu", t.rows(), t.cols());

    for (std::size_t row = 0; row < cols; row++) {
        for (std::size_t col = 0; col < rows; col++) {
            double expected = col * 1000.0 + row;
            CHECK(t[row][col] == expected, "transpose[%zu][%zu] is %g, expected %g",
                  row, col, t[row][col], expected);
        }
    }
}

Matrix product_by_definition(const Matrix& a, const Matrix& b) {
    Matrix product(a.rows(), b.cols());
    for (std::size_t row = 0; row < a.rows(); row++) {
        for (std::size_t col = 0; col < b.cols(); col++) {
            for (std::size_t k = 0; k < a.cols(); k++) {
                product[row][col] += a[row][k] * b[k][col];
            }
        }
    }
    return product;
}

void test_multiply_square() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{5, 6}, {7, 8}};
    Matrix expected{{19, 22}, {43, 50}};
    CHECK(a * b == expected, "{{1, 2}, {3, 4}} * {{5, 6}, {7, 8}} should be {{19, 22}, {43, 50}}");
}

void test_multiply_non_square() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{7, 8}, {9, 10}, {11, 12}};

    Matrix ab = a * b;
    Matrix ab_expected{{58, 64}, {139, 154}};
    CHECK(ab.rows() == 2 && ab.cols() == 2, "(2 x 3) * (3 x 2) is %zu x %zu, expected 2 x 2", ab.rows(), ab.cols());
    CHECK(ab == ab_expected, "{{1, 2, 3}, {4, 5, 6}} * {{7, 8}, {9, 10}, {11, 12}} should be {{58, 64}, {139, 154}}");

    Matrix ba = b * a;
    Matrix ba_expected{{39, 54, 69}, {49, 68, 87}, {59, 82, 105}};
    CHECK(ba.rows() == 3 && ba.cols() == 3, "(3 x 2) * (2 x 3) is %zu x %zu, expected 3 x 3", ba.rows(), ba.cols());
    CHECK(ba == ba_expected, "{{7, 8}, {9, 10}, {11, 12}} * {{1, 2, 3}, {4, 5, 6}} is wrong");

    Matrix c{{1, 0, 2}, {0, 1, -1}};
    Matrix d{{3, 1, 0, 2}, {1, 1, 1, 1}, {0, 2, 1, -1}};
    Matrix cd_expected{{3, 5, 2, 0}, {1, -1, 0, 2}};
    Matrix cd = c * d;
    CHECK(cd.rows() == 2 && cd.cols() == 4, "(2 x 3) * (3 x 4) is %zu x %zu, expected 2 x 4", cd.rows(), cd.cols());
    CHECK(cd == cd_expected, "a (2 x 3) * (3 x 4) product is wrong");
}

void test_multiply_row_and_column_vectors() {
    Matrix row{{1, 2, 3}};
    Matrix column{{4}, {5}, {6}};

    Matrix dot = row * column;
    CHECK(dot.rows() == 1 && dot.cols() == 1, "(1 x 3) * (3 x 1) is %zu x %zu, expected 1 x 1", dot.rows(), dot.cols());
    CHECK(dot == Matrix{{32}}, "{{1, 2, 3}} * {{4}, {5}, {6}} should be {{32}}");

    Matrix outer = column * row;
    Matrix outer_expected{{4, 8, 12}, {5, 10, 15}, {6, 12, 18}};
    CHECK(outer.rows() == 3 && outer.cols() == 3, "(3 x 1) * (1 x 3) is %zu x %zu, expected 3 x 3",
          outer.rows(), outer.cols());
    CHECK(outer == outer_expected, "{{4}, {5}, {6}} * {{1, 2, 3}} is wrong");
}

void test_multiply_single_entries() {
    CHECK(Matrix{{-2.5}} * Matrix{{4}} == Matrix{{-10}}, "{{-2.5}} * {{4}} should be {{-10}}");

    Matrix three{{3}};
    Matrix row{{1, 2}};
    Matrix scaled_row{{3, 6}};
    CHECK(three * row == scaled_row, "{{3}} * {{1, 2}} should be {{3, 6}}");

    Matrix square{{1, 2}, {3, 4}};
    CHECK_THROWS(std::invalid_argument, three * square);
}

void test_multiply_by_identity() {
    Matrix i2{{1, 0}, {0, 1}};
    Matrix i3{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    Matrix a{{1, 2, 3}, {4, 5, 6}};
    CHECK(i2 * a == a, "identity(2) * a should equal a for a 2 x 3 matrix a");
    CHECK(a * i3 == a, "a * identity(3) should equal a for a 2 x 3 matrix a");

    Matrix square{{2, -1}, {0.5, 3}};
    CHECK(square * i2 == square && i2 * square == square,
          "multiplying by identity(2) on either side should leave a 2 x 2 matrix unchanged");
}

void test_multiply_by_zero_matrix() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    CHECK(a * Matrix(3, 4) == Matrix(2, 4), "a 2 x 3 matrix times a 3 x 4 zero matrix should be a 2 x 4 zero matrix");
    CHECK(Matrix(5, 2) * a == Matrix(5, 3), "a 5 x 2 zero matrix times a 2 x 3 matrix should be a 5 x 3 zero matrix");
}

void test_multiply_order_matters() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{0, 1}, {1, 0}};
    Matrix ab{{2, 1}, {4, 3}};
    Matrix ba{{3, 4}, {1, 2}};

    CHECK(a * b == ab, "{{1, 2}, {3, 4}} * {{0, 1}, {1, 0}} should swap the columns: {{2, 1}, {4, 3}}");
    CHECK(b * a == ba, "{{0, 1}, {1, 0}} * {{1, 2}, {3, 4}} should swap the rows: {{3, 4}, {1, 2}}");
}

void test_multiply_is_associative() {
    Matrix a{{1, 2}, {3, 4}, {5, 6}};
    Matrix b{{1, -1, 2}, {0, 3, 1}};
    Matrix c{{2, 0}, {1, 1}, {-1, 4}};
    CHECK((a * b) * c == a * (b * c), "(a * b) * c should equal a * (b * c)");
}

void test_multiply_with_add_scale_and_transpose() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{1, 0}, {2, -1}, {0, 3}};
    Matrix c{{-2, 1}, {0, 4}, {5, 5}};

    CHECK(a * (b + c) == a * b + a * c, "a * (b + c) should equal a * b + a * c");
    CHECK((b - c) * a == b * a - c * a, "(b - c) * a should equal b * a - c * a");
    CHECK((2 * a) * b == 2 * (a * b), "(2 * a) * b should equal 2 * (a * b)");
    CHECK(a * (b * 3) == (a * b) * 3, "a * (b * 3) should equal (a * b) * 3");
    CHECK(transpose(a * b) == transpose(b) * transpose(a),
          "transpose(a * b) should equal transpose(b) * transpose(a)");
}

void test_multiply_leaves_operands_unchanged() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{5, 6}, {7, 8}};
    Matrix a_before{{1, 2}, {3, 4}};
    Matrix b_before{{5, 6}, {7, 8}};

    (void)(a * b);
    CHECK(a == a_before, "a * b changed a");
    CHECK(b == b_before, "a * b changed b");
}

void test_product_is_separate() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix i{{1, 0}, {0, 1}};
    Matrix product = a * i;

    product[0][0] = 100;
    CHECK(a[0][0] == 1, "changing a * identity changed a");
    CHECK(i[0][0] == 1, "changing a * identity changed the identity matrix");
}

void test_large_multiply() {
    const std::size_t rows = 40;
    const std::size_t inner = 70;
    const std::size_t cols = 30;

    Matrix a(rows, inner);
    Matrix b(inner, cols);
    for (std::size_t row = 0; row < rows; row++) {
        for (std::size_t k = 0; k < inner; k++) {
            a[row][k] = static_cast<double>((row * 7 + k * 3) % 11) - 5;
        }
    }
    for (std::size_t k = 0; k < inner; k++) {
        for (std::size_t col = 0; col < cols; col++) {
            b[k][col] = static_cast<double>((k * 5 + col * 2) % 13) - 6;
        }
    }

    Matrix product = a * b;
    CHECK(product.rows() == rows && product.cols() == cols, "(40 x 70) * (70 x 30) is %zu x %zu, expected 40 x 30",
          product.rows(), product.cols());
    CHECK(product == product_by_definition(a, b), "a (40 x 70) * (70 x 30) product is wrong");
}

void test_multiply_rejects_mismatched_shapes() {
    CHECK_THROWS(std::invalid_argument, Matrix(2, 3) * Matrix(2, 3));
    CHECK_THROWS(std::invalid_argument, Matrix(3, 2) * Matrix(3, 2));
    CHECK_THROWS(std::invalid_argument, Matrix(2, 2) * Matrix(3, 3));
    CHECK_THROWS(std::invalid_argument, Matrix(1, 4) * Matrix(1, 4));
    CHECK_THROWS(std::invalid_argument, Matrix(4, 1) * Matrix(4, 1));
    CHECK_THROWS(std::invalid_argument, Matrix(2, 3) * Matrix(4, 2));
}

void test_const_matrix_can_be_read() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    const Matrix& view = m;

    CHECK(view.rows() == 2 && view.cols() == 3, "a const view of a 2 x 3 matrix is %zu x %zu", view.rows(), view.cols());
    CHECK(view[0][0] == 1 && view[1][2] == 6, "reading through a const view gave the wrong entries");

    m[1][2] = 9;
    CHECK(view[1][2] == 9, "a const view should see changes made through the matrix itself; read %g", view[1][2]);
}

void test_operations_take_const_references() {
    bool (*equal)(const Matrix&, const Matrix&) = linalg::operator==;
    Matrix (*add)(const Matrix&, const Matrix&) = linalg::operator+;
    Matrix (*subtract)(const Matrix&, const Matrix&) = linalg::operator-;
    Matrix (*scale_right)(const Matrix&, double) = linalg::operator*;
    Matrix (*scale_left)(double, const Matrix&) = linalg::operator*;
    Matrix (*multiply)(const Matrix&, const Matrix&) = linalg::operator*;
    Matrix (*transposed)(const Matrix&) = linalg::transpose;

    const Matrix a{{1, 2}, {3, 4}};
    const Matrix b{{5, 6}, {7, 8}};

    Matrix sum{{6, 8}, {10, 12}};
    Matrix difference{{-4, -4}, {-4, -4}};
    Matrix doubled{{2, 4}, {6, 8}};
    Matrix product{{19, 22}, {43, 50}};
    Matrix flipped{{1, 3}, {2, 4}};

    CHECK(equal(a, a) && !equal(a, b), "== through const references gave the wrong answer");
    CHECK(add(a, b) == sum, "+ through const references gave the wrong sum");
    CHECK(subtract(a, b) == difference, "- through const references gave the wrong difference");
    CHECK(scale_right(a, 2) == doubled && scale_left(2, a) == doubled, "scaling through const references is wrong");
    CHECK(multiply(a, b) == product, "* through const references gave the wrong product");
    CHECK(transposed(a) == flipped, "transpose through a const reference is wrong");
}

void test_operations_on_const_matrices() {
    const Matrix a{{1, 2, 3}, {4, 5, 6}};
    const Matrix b{{6, 5, 4}, {3, 2, 1}};

    Matrix sum{{7, 7, 7}, {7, 7, 7}};
    Matrix product{{28, 10}, {73, 28}};
    Matrix flipped{{1, 4}, {2, 5}, {3, 6}};

    CHECK(a + b == sum, "adding two const matrices is wrong");
    CHECK(a - a == Matrix(2, 3), "a const matrix minus itself should be all zeros");
    CHECK(a * transpose(b) == product, "multiplying const matrices is wrong");
    CHECK(transpose(a) == flipped, "transposing a const matrix is wrong");
    CHECK(a * 2 == 2 * a, "scaling a const matrix should not depend on the side");
}

struct Test {
    const char* name;
    void (*run)();
};

const Test kTests[] = {
    {"reports its shape", test_reports_its_shape},
    {"single entry", test_single_entry},
    {"row and column vectors", test_row_and_column_vectors},
    {"large shape", test_large_shape},
    {"rejects zero rows or columns", test_rejects_zero_rows_or_columns},
    {"new entries are zero", test_new_entries_are_zero},
    {"index writes and reads entries", test_index_writes_and_reads_entries},
    {"index returns a reference", test_index_returns_a_reference},
    {"every entry is separate", test_every_entry_is_separate},
    {"row and column vector entries", test_row_and_column_vector_entries},
    {"entries keep fractions and extremes", test_entries_keep_fractions_and_extremes},
    {"list constructor sets shape", test_list_constructor_sets_shape},
    {"list constructor fills rows in order", test_list_constructor_fills_rows_in_order},
    {"list constructor row and column vectors", test_list_constructor_row_and_column_vectors},
    {"list constructor single entry", test_list_constructor_single_entry},
    {"list constructor keeps fractions", test_list_constructor_keeps_fractions},
    {"list-built matrix can change", test_list_built_matrix_can_change},
    {"list constructor rejects empty input", test_list_constructor_rejects_empty_input},
    {"list constructor rejects ragged rows", test_list_constructor_rejects_ragged_rows},
    {"equal matrices compare equal", test_equal_matrices_compare_equal},
    {"equal matrices built differently", test_equal_matrices_built_differently},
    {"one different entry makes unequal", test_one_different_entry_makes_unequal},
    {"different shapes are unequal", test_different_shapes_are_unequal},
    {"entries must match exactly", test_entries_must_match_exactly},
    {"not equal", test_not_equal},
    {"comparison leaves matrices unchanged", test_comparison_leaves_matrices_unchanged},
    {"add", test_add},
    {"subtract", test_subtract},
    {"add and subtract non-square", test_add_and_subtract_non_square},
    {"add and subtract single entry", test_add_and_subtract_single_entry},
    {"zero matrix changes nothing", test_zero_matrix_changes_nothing},
    {"add is commutative", test_add_is_commutative},
    {"add and subtract chain", test_add_and_subtract_chain},
    {"add and subtract leave operands unchanged", test_add_and_subtract_leave_operands_unchanged},
    {"sum is a separate matrix", test_sum_is_a_separate_matrix},
    {"large add and subtract", test_large_add_and_subtract},
    {"add and subtract reject shape mismatch", test_add_and_subtract_reject_shape_mismatch},
    {"scalar times matrix", test_scalar_times_matrix},
    {"matrix times scalar", test_matrix_times_scalar},
    {"scalar order does not matter", test_scalar_order_does_not_matter},
    {"scalar multiplication non-square", test_scalar_multiplication_non_square},
    {"multiply by zero, one and minus one", test_multiply_by_zero_one_and_minus_one},
    {"scalar multiplication single entry", test_scalar_multiplication_single_entry},
    {"scalar multiplication chain", test_scalar_multiplication_chain},
    {"scalar distributes over add", test_scalar_distributes_over_add},
    {"scalar multiplication leaves matrix unchanged", test_scalar_multiplication_leaves_matrix_unchanged},
    {"scaled matrix is separate", test_scaled_matrix_is_separate},
    {"large scalar multiplication", test_large_scalar_multiplication},
    {"transpose non-square", test_transpose_non_square},
    {"transpose square", test_transpose_square},
    {"transpose row and column vectors", test_transpose_row_and_column_vectors},
    {"transpose single entry", test_transpose_single_entry},
    {"transpose twice gives original", test_transpose_twice_gives_original},
    {"symmetric matrices are their own transpose", test_symmetric_matrices_are_their_own_transpose},
    {"transpose with add and scale", test_transpose_with_add_and_scale},
    {"transpose leaves matrix unchanged", test_transpose_leaves_matrix_unchanged},
    {"transpose is separate", test_transpose_is_separate},
    {"large transpose", test_large_transpose},
    {"multiply square", test_multiply_square},
    {"multiply non-square", test_multiply_non_square},
    {"multiply row and column vectors", test_multiply_row_and_column_vectors},
    {"multiply single entries", test_multiply_single_entries},
    {"multiply by identity", test_multiply_by_identity},
    {"multiply by zero matrix", test_multiply_by_zero_matrix},
    {"multiply order matters", test_multiply_order_matters},
    {"multiply is associative", test_multiply_is_associative},
    {"multiply with add, scale and transpose", test_multiply_with_add_scale_and_transpose},
    {"multiply leaves operands unchanged", test_multiply_leaves_operands_unchanged},
    {"product is separate", test_product_is_separate},
    {"large multiply", test_large_multiply},
    {"multiply rejects mismatched shapes", test_multiply_rejects_mismatched_shapes},
    {"const matrix can be read", test_const_matrix_can_be_read},
    {"operations take const references", test_operations_take_const_references},
    {"operations on const matrices", test_operations_on_const_matrices},
};

}

int main() {
    int passed = 0;
    int total = 0;

    for (const Test& test : kTests) {
        test_failed = false;
        std::printf("[ RUN  ] %s\n", test.name);

        try {
            test.run();
        } catch (const std::exception& error) {
            std::printf("    threw: %s\n", error.what());
            test_failed = true;
        }

        std::printf("%s %s\n", test_failed ? "[ FAIL ]" : "[  OK  ]", test.name);
        total++;
        if (!test_failed) {
            passed++;
        }
    }

    std::printf("\n%d/%d tests passed\n", passed, total);
    return passed == total ? 0 : 1;
}
