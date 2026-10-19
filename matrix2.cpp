#include <stdexcept>
#include <limits>

int ** concat_rows(
    const int * const * lhs, size_t n1, size_t m1,
    const int * const * rhs, size_t n2, size_t m2
) {
    if ((n1 > 0 && lhs == nullptr) || (n2 > 0 && rhs == nullptr))
        throw std::invalid_argument("nullptr");

    for (size_t i = 0; i < n1; i++) {
        if (m1 > 0 && lhs[i] == nullptr)
            throw std::invalid_argument("nullptr in lhs");
    }

    for (size_t i = 0; i < n2; i++) {
        if (m2 > 0 && rhs[i] == nullptr)
            throw std::invalid_argument("nullptr in rhs");
    }

    if (m1 > std::numeric_limits<size_t>::max() - m2) {
        throw std::overflow_error("overflow");
    }
    size_t cols = m1 + m2;

    size_t rows = (n1 > n2) ? n1 : n2;

    int **matrix = new int*[rows];
    size_t count = 0;

    try {
        for (size_t i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
            count++;
            
            if (i < n1) {
                for (size_t j = 0; j < m1; j++)
                    matrix[i][j] = lhs[i][j];
            } else {
                for (size_t j = 0; j < m1; j++)
                    matrix[i][j] = 0;
            }
            
            if (i < n2) {
                for (size_t k = 0; k < m2; k++)
                    matrix[i][k + m1] = rhs[i][k];
            } else {
                for (size_t k = 0; k < m2; k++)
                    matrix[i][k + m1] = 0;
            }
        }
    }
    catch (const std::bad_alloc &e) {
        for (size_t k = 0; k < count; k++)
            delete[] matrix[k];

        delete[] matrix;
        throw;
    }

    return matrix;
}
