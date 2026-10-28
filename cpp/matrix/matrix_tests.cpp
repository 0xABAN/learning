#include "matrix.h"

#include <cstddef>
#include <cstdio>
#include <exception>
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
