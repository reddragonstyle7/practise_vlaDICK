#include <iostream>
#include <stdexcept>

void memory_release(int n, int **matrix) {
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    
    delete[] matrix;
}

int **memory_alloc(int n, int m) {
    int **matrix = nullptr;
    int count = 0;
    try {
        matrix = new int *[n];

        for (int i = 0; i < n; i++) {
            matrix[i] = new int [m];
            count += 1;
        }

        return matrix;
    } catch (std::bad_alloc) {
        memory_release(count, matrix);
        throw;
    }
}

void matrix_input(int n, int m, int **matrix) {
    int x;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            std::cin >> x;
            matrix[i][j] = x;
        }
}

void matrix_output(int n, int m, int **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void transposition_matrix(int n, int m, int **matrix) {
    int **transposed_matrix = memory_alloc(m, n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            transposed_matrix[i][j] = matrix[j][i];
    
    matrix_output(m, n, transposed_matrix);

    memory_release(m, transposed_matrix);

}

void protect_against_fool(int n, int m) {
    if (std::cin.fail()) {
        throw std::invalid_argument("Bro, we were waiting for a whole and non-negative integer!");
    }
    if (m == 0 || n == 0 || n < 2 || m < 2) {
        throw std::out_of_range("Bro, the numbers n and m must belong to the interval [2, +∞]");
    }
}

int main(void) {

    try {
        int n, m;
        std::cin >> n >> m;

        protect_against_fool(n, m);

        int **matrix = memory_alloc(n, m);
        
        matrix_input(n, m, matrix);

        std::cout << "Введённая матрица" << std::endl;
        matrix_output(n, m, matrix);

        std::cout << "Транспонированная матрица"<< std::endl;

        transposition_matrix(n, m, matrix);

        memory_release(n, matrix);

        return 0;
    } catch (std::invalid_argument &e) {
        std::cerr << "invalid_argument: " << e.what() << std::endl;
        return 1;
    } catch (std::out_of_range &e) {
        std::cerr << "out_of_range: " << e.what() << std::endl;
        return 1;
    } catch (std::bad_alloc) {
        std::cerr << "Bro, sorry, the computer did not allocate memory :(" << std::endl;
        return 2;
    }
     
}
