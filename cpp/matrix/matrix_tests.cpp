#include "matrix.h"

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
            CHECK(m.at(row, col) == 0, "Matrix(2, 3).at(%zu, %zu) is %g, expected 0",
                  row, col, m.at(row, col));
        }
    }
}

void test_at_writes_and_reads_entries() {
    Matrix m(2, 2);
    m.at(1, 0) = 7;
    m.at(0, 1) = -2.5;

    CHECK(m.at(1, 0) == 7, "after writing 7 to (1, 0), it reads %g", m.at(1, 0));
    CHECK(m.at(0, 1) == -2.5, "after writing -2.5 to (0, 1), it reads %g", m.at(0, 1));
    CHECK(m.at(0, 0) == 0 && m.at(1, 1) == 0, "writing two entries changed another one");
}

void test_at_returns_a_reference() {
    Matrix m(2, 2);

    double& entry = m.at(1, 1);
    entry = 4;
    CHECK(m.at(1, 1) == 4, "writing 4 through a saved reference to (1, 1) left it at %g", m.at(1, 1));

    m.at(1, 1) += 1.5;
    CHECK(m.at(1, 1) == 5.5, "after += 1.5, (1, 1) is %g, expected 5.5", m.at(1, 1));
}

void test_every_entry_is_separate() {
    Matrix m(3, 4);
    for (std::size_t row = 0; row < 3; row++) {
        for (std::size_t col = 0; col < 4; col++) {
            m.at(row, col) = row * 10.0 + col;
        }
    }

    for (std::size_t row = 0; row < 3; row++) {
        for (std::size_t col = 0; col < 4; col++) {
            double expected = row * 10.0 + col;
            CHECK(m.at(row, col) == expected, "Matrix(3, 4).at(%zu, %zu) is %g, expected %g",
                  row, col, m.at(row, col), expected);
        }
    }
}

void test_row_and_column_vector_entries() {
    Matrix row(1, 5);
    row.at(0, 4) = 3;
    CHECK(row.at(0, 4) == 3, "Matrix(1, 5).at(0, 4) is %g, expected 3", row.at(0, 4));

    Matrix column(5, 1);
    column.at(4, 0) = 3;
    CHECK(column.at(4, 0) == 3, "Matrix(5, 1).at(4, 0) is %g, expected 3", column.at(4, 0));
}

void test_entries_keep_fractions_and_extremes() {
    Matrix m(1, 4);
    m.at(0, 0) = 0.1;
    m.at(0, 1) = -1e300;
    m.at(0, 2) = 1e-300;
    m.at(0, 3) = -0.5;

    CHECK(m.at(0, 0) == 0.1, "stored 0.1, read %g", m.at(0, 0));
    CHECK(m.at(0, 1) == -1e300, "stored -1e300, read %g", m.at(0, 1));
    CHECK(m.at(0, 2) == 1e-300, "stored 1e-300, read %g", m.at(0, 2));
    CHECK(m.at(0, 3) == -0.5, "stored -0.5, read %g", m.at(0, 3));
}

void test_at_rejects_out_of_range_indexes() {
    Matrix m(2, 3);
    CHECK_THROWS(std::out_of_range, m.at(2, 0));
    CHECK_THROWS(std::out_of_range, m.at(0, 3));
    CHECK_THROWS(std::out_of_range, m.at(2, 3));
    CHECK_THROWS(std::out_of_range, m.at(100, 0));
    CHECK_THROWS(std::out_of_range, m.at(0, 100));
    CHECK_THROWS(std::out_of_range, m.at(-1, 0));
    CHECK_THROWS(std::out_of_range, m.at(0, -1));

    Matrix single(1, 1);
    CHECK_THROWS(std::out_of_range, single.at(1, 0));
    CHECK_THROWS(std::out_of_range, single.at(0, 1));
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
            CHECK(m.at(row, col) == expected[row][col], "{{1, 2, 3}, {4, 5, 6}}.at(%zu, %zu) is %g, expected %g",
                  row, col, m.at(row, col), expected[row][col]);
        }
    }
}

void test_list_constructor_row_and_column_vectors() {
    Matrix row{{1, 2, 3, 4}};
    CHECK(row.rows() == 1 && row.cols() == 4, "{{1, 2, 3, 4}} is %zu x %zu", row.rows(), row.cols());
    CHECK(row.at(0, 3) == 4, "{{1, 2, 3, 4}}.at(0, 3) is %g, expected 4", row.at(0, 3));

    Matrix column{{1}, {2}, {3}};
    CHECK(column.rows() == 3 && column.cols() == 1, "{{1}, {2}, {3}} is %zu x %zu",
          column.rows(), column.cols());
    CHECK(column.at(2, 0) == 3, "{{1}, {2}, {3}}.at(2, 0) is %g, expected 3", column.at(2, 0));
}

void test_list_constructor_single_entry() {
    Matrix m{{-7.5}};
    CHECK(m.rows() == 1 && m.cols() == 1, "{{-7.5}} is %zu x %zu", m.rows(), m.cols());
    CHECK(m.at(0, 0) == -7.5, "{{-7.5}}.at(0, 0) is %g, expected -7.5", m.at(0, 0));
}

void test_list_constructor_keeps_fractions() {
    Matrix m{{0.1, -0.25}, {1e-300, -1e300}};
    CHECK(m.at(0, 0) == 0.1, "stored 0.1, read %g", m.at(0, 0));
    CHECK(m.at(0, 1) == -0.25, "stored -0.25, read %g", m.at(0, 1));
    CHECK(m.at(1, 0) == 1e-300, "stored 1e-300, read %g", m.at(1, 0));
    CHECK(m.at(1, 1) == -1e300, "stored -1e300, read %g", m.at(1, 1));
}

void test_list_built_matrix_can_change() {
    Matrix m{{1, 2}, {3, 4}};
    m.at(0, 1) = 9;

    CHECK(m.at(0, 1) == 9, "after writing 9 to (0, 1), it reads %g", m.at(0, 1));
    CHECK(m.at(0, 0) == 1 && m.at(1, 0) == 3 && m.at(1, 1) == 4, "writing (0, 1) changed another entry");
    CHECK_THROWS(std::out_of_range, m.at(2, 0));
    CHECK_THROWS(std::out_of_range, m.at(0, 2));
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

void test_identity_shape() {
    Matrix i3 = Matrix::identity(3);
    CHECK(i3.rows() == 3 && i3.cols() == 3, "identity(3) is %zu x %zu", i3.rows(), i3.cols());

    Matrix i1 = Matrix::identity(1);
    CHECK(i1.rows() == 1 && i1.cols() == 1, "identity(1) is %zu x %zu", i1.rows(), i1.cols());
}

void test_identity_entries() {
    Matrix i3 = Matrix::identity(3);
    for (std::size_t row = 0; row < 3; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            double expected = row == col ? 1 : 0;
            CHECK(i3.at(row, col) == expected, "identity(3).at(%zu, %zu) is %g, expected %g",
                  row, col, i3.at(row, col), expected);
        }
    }

    Matrix i1 = Matrix::identity(1);
    CHECK(i1.at(0, 0) == 1, "identity(1).at(0, 0) is %g, expected 1", i1.at(0, 0));
}

void test_large_identity() {
    const std::size_t n = 200;
    Matrix m = Matrix::identity(n);
    CHECK(m.rows() == n && m.cols() == n, "identity(200) is %zu x %zu", m.rows(), m.cols());

    for (std::size_t row = 0; row < n; row++) {
        for (std::size_t col = 0; col < n; col++) {
            double expected = row == col ? 1 : 0;
            CHECK(m.at(row, col) == expected, "identity(200).at(%zu, %zu) is %g, expected %g",
                  row, col, m.at(row, col), expected);
        }
    }
}

void test_identity_can_change() {
    Matrix m = Matrix::identity(2);
    m.at(0, 1) = 5;
    m.at(1, 1) = -3;

    CHECK(m.at(0, 1) == 5 && m.at(1, 1) == -3, "writing to an identity matrix didn't stick");
    CHECK(m.at(0, 0) == 1 && m.at(1, 0) == 0, "writing two entries changed another one");

    Matrix fresh = Matrix::identity(2);
    CHECK(fresh.at(0, 1) == 0 && fresh.at(1, 1) == 1, "changing one identity matrix changed a later one");
}

void test_identity_rejects_bad_indexes() {
    Matrix m = Matrix::identity(2);
    CHECK_THROWS(std::out_of_range, m.at(2, 0));
    CHECK_THROWS(std::out_of_range, m.at(0, 2));
}

void test_identity_rejects_zero_size() {
    CHECK_THROWS(std::invalid_argument, Matrix::identity(0));
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
    Matrix identity = Matrix::identity(3);
    CHECK(built == identity, "{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} should equal identity(3)");

    Matrix zeros(2, 2);
    Matrix listed{{0, 0}, {0, 0}};
    CHECK(zeros == listed, "Matrix(2, 2) should equal {{0, 0}, {0, 0}}");

    Matrix written(2, 2);
    written.at(0, 1) = 3;
    written.at(1, 0) = -1;
    Matrix expected{{0, 3}, {-1, 0}};
    CHECK(written == expected, "a matrix filled with at() should equal the same entries written as a list");
}

void test_one_different_entry_makes_unequal() {
    Matrix base{{1, 2, 3}, {4, 5, 6}};

    for (std::size_t row = 0; row < 2; row++) {
        for (std::size_t col = 0; col < 3; col++) {
            Matrix changed{{1, 2, 3}, {4, 5, 6}};
            changed.at(row, col) += 0.5;
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

    CHECK(a.rows() == 2 && a.cols() == 2 && a.at(1, 1) == 4, "comparing changed the left matrix");
    CHECK(b.rows() == 2 && b.cols() == 2 && b.at(1, 1) == 5, "comparing changed the right matrix");
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

    sum.at(0, 0) = 100;
    CHECK(a.at(0, 0) == 1 && b.at(0, 0) == 10, "changing the sum changed one of the operands");
}

void test_large_add_and_subtract() {
    const std::size_t n = 100;
    Matrix a(n, n);
    Matrix b(n, n);
    Matrix sum(n, n);
    Matrix difference(n, n);

    for (std::size_t row = 0; row < n; row++) {
        for (std::size_t col = 0; col < n; col++) {
            a.at(row, col) = row * 3.0 + col;
            b.at(row, col) = col * 2.0 - row;
            sum.at(row, col) = row * 2.0 + col * 3.0;
            difference.at(row, col) = row * 4.0 - col;
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
    {"at writes and reads entries", test_at_writes_and_reads_entries},
    {"at returns a reference", test_at_returns_a_reference},
    {"every entry is separate", test_every_entry_is_separate},
    {"row and column vector entries", test_row_and_column_vector_entries},
    {"entries keep fractions and extremes", test_entries_keep_fractions_and_extremes},
    {"at rejects out-of-range indexes", test_at_rejects_out_of_range_indexes},
    {"list constructor sets shape", test_list_constructor_sets_shape},
    {"list constructor fills rows in order", test_list_constructor_fills_rows_in_order},
    {"list constructor row and column vectors", test_list_constructor_row_and_column_vectors},
    {"list constructor single entry", test_list_constructor_single_entry},
    {"list constructor keeps fractions", test_list_constructor_keeps_fractions},
    {"list-built matrix can change", test_list_built_matrix_can_change},
    {"list constructor rejects empty input", test_list_constructor_rejects_empty_input},
    {"list constructor rejects ragged rows", test_list_constructor_rejects_ragged_rows},
    {"identity shape", test_identity_shape},
    {"identity entries", test_identity_entries},
    {"large identity", test_large_identity},
    {"identity can change", test_identity_can_change},
    {"identity rejects bad indexes", test_identity_rejects_bad_indexes},
    {"identity rejects zero size", test_identity_rejects_zero_size},
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
