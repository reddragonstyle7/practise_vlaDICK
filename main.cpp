#include <iostream>

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    
    if (n <= 0 || m <= 0) {
        return 1;
    }
    
    int **matrix = new int*[n];
    
    if (matrix == nullptr) {
        return 2;
    }
    
    for (int i = 0; i < n; i++) {
        matrix[i] = new (std::nothrow) int[m];
        
        if (matrix[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                delete[] matrix[j];
            }
            delete[] matrix[i];
            return 2;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = 0;
            std::cin >> x;
            matrix[i][j] = x;
        }
    }
    
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    
    delete[] matrix;
    return 0;
}
