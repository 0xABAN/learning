#include "matrix.h"

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
