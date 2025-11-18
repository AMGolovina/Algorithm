#include <iostream>
#include <vector>

void multiply(
    const std::vector<std::vector<int64_t>>& A,
    const std::vector<std::vector<int64_t>>& B,
    std::vector<std::vector<int64_t>>& C,
    int size
) {
    if (size <= 64) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int64_t sum = 0;
                for (int k = 0; k < size; ++k) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }
        return;
    }

    int half = size / 2;
    
    std::vector<std::vector<int64_t>> M1(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> M2(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> M3(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> M4(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> M5(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> M6(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> M7(half, std::vector<int64_t>(half));
    
    std::vector<std::vector<int64_t>> A11(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> A12(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> A21(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> A22(half, std::vector<int64_t>(half));
    
    std::vector<std::vector<int64_t>> B11(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> B12(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> B21(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> B22(half, std::vector<int64_t>(half));
    
    std::vector<std::vector<int64_t>> tempA(half, std::vector<int64_t>(half));
    std::vector<std::vector<int64_t>> tempB(half, std::vector<int64_t>(half));

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            tempA[i][j] = A11[i][j] + A22[i][j];
            tempB[i][j] = B11[i][j] + B22[i][j];
        }
    }
    multiply(tempA, tempB, M1, half);

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            tempA[i][j] = A21[i][j] + A22[i][j];
        }
    }
    multiply(tempA, B11, M2, half);

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            tempB[i][j] = B12[i][j] - B22[i][j];
        }
    }
    multiply(A11, tempB, M3, half);

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            tempB[i][j] = B21[i][j] - B11[i][j];
        }
    }
    multiply(A22, tempB, M4, half);

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            tempA[i][j] = A11[i][j] + A12[i][j];
        }
    }
    multiply(tempA, B22, M5, half);

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            tempA[i][j] = A21[i][j] - A11[i][j];
            tempB[i][j] = B11[i][j] + B12[i][j];
        }
    }
    multiply(tempA, tempB, M6, half);

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            tempA[i][j] = A12[i][j] - A22[i][j];
            tempB[i][j] = B21[i][j] + B22[i][j];
        }
    }
    multiply(tempA, tempB, M7, half);

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + half] = M3[i][j] + M5[i][j];
            C[i + half][j] = M2[i][j] + M4[i][j];
            C[i + half][j + half] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }
}

std::vector<std::vector<int64_t>> matrixProduct(const std::vector<std::vector<int64_t>>& A, const std::vector<std::vector<int64_t>>& B) {
    int n = A.size();
    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(n, 0));
    multiply(A, B, C, n);
    return C;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int64_t>> A(n, std::vector<int64_t>(n));
    std::vector<std::vector<int64_t>> B(n, std::vector<int64_t>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> A[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> B[i][j];
        }
    }

    auto C = matrixProduct(A, B);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << C[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
