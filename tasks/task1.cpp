#include <array>
#include <iostream>

//Гаусс честно взят отсюда: https://www.geeksforgeeks.org/cpp-program-for-determinant-of-a-matrix/
template <int N>
constexpr int Det(const std::array<std::array<int, N>, N>& matrix) {
    int mat[N][N] = {0};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[i][j] = matrix[i][j];
        }
    }

    int det = 1, total = 1, temp[N + 1] = {0};
    for (int i = 0; i < N; i++)
    {
        int leading = i;
        while (leading < N && mat[leading][i] == 0) ++leading;
        if (leading == N) return 0;
        if (leading != i)
        {
            for (int j = 0; j < N; ++j)
            {
                int t = mat[leading][j];
                mat[leading][j] = mat[i][j];
                mat[i][j] = t;
            }
            for (int k = 0; k < leading - i; ++k) det *= -1;
        }
        for (int j = 0; j < N; ++j) temp[j] = mat[i][j];
        for (int j = i + 1; j < N; ++j)
        {
            int a = temp[i], b = mat[j][i];
            for (int k = 0; k < N; ++k)
            {
                mat[j][k] = (a * mat[j][k]) - (b * temp[k]);
            }
            total *= a;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        det *= mat[i][i];
    }

    return det / total;
}

int main() {
    constexpr std::array<std::array<int, 2>, 2> matrix = {{
                                                                  {0, 1, 2},
                                                                  {1, 2, 3},
                                                                  {2, 3, 7}
                                                          }};
    constexpr int result = Det<3>(matrix);
    std::cout << result << std::endl;
    return 0;
}
