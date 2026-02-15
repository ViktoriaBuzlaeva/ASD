// Copyright 2025 Viktoria Buzlaeva

#include "../lib_algorithms/algorithms.h"

int find_local_min_matrix(Matrix<int> matrix, unsigned int seed) {
	srand(seed);
	int size = matrix.rows();
	int x = rand() % (size);
	int y = rand() % (size);

    while (true) {
        int value = matrix[x][y];
        int i = x, j = y;
        int min_value = value;

        if (x + 1 < size && min_value > matrix[x + 1][y]) {
            min_value = matrix[x + 1][y];
            i = x + 1;
            j = y;
        }
        if (x - 1 >= 0 && min_value > matrix[x - 1][y]) {
            min_value = matrix[x - 1][y];
            i = x - 1;
            j = y;
        }
        if (y + 1 < size && min_value > matrix[x][y + 1]) {
            min_value = matrix[x][y + 1];
            i = x;
            j = y + 1;
        }
        if (y - 1 >= 0 && min_value > matrix[x][y - 1]) {
            min_value = matrix[x][y - 1];
            i = x;
            j = y - 1;
        }

        if (min_value >= value) {
            return value;
        }
        else {
            x = i;
            y = j;
        }
    }
}

int find_number_of_islands(Matrix<int> matrix) {
    DSU dsu(matrix.rows() * matrix.cols());

    for (int i = 0; i < matrix.rows(); i++) {
        for (int j = 0; j < matrix.cols(); j++) {
            if (matrix[i][j] == 1) {
                int current_index = i * matrix.cols() + j;

                if (j > 0 && matrix[i][j - 1] == 1) {
                    int left_index = i * matrix.cols() + (j - 1);
                    dsu.unite(current_index, left_index);
                }

                if (i > 0 && matrix[i - 1][j] == 1) {
                    int top_index = (i - 1) * matrix.cols() + j;
                    dsu.unite(current_index, top_index);
                }
            }
        }
    }

    int islands_count = 0;
    for (int i = 0; i < matrix.rows(); i++) {
        for (int j = 0; j < matrix.cols(); j++) {
            if (matrix[i][j] == 1) {
                int index = i * matrix.cols() + j;
                if (dsu.find(index) == index) {
                    islands_count++;
                }
            }
        }
    }

    return islands_count;
}

Matrix<bool> generate_labyrinth(int S, int F, int N, int M) {
    if (N < 5 || M < 5) {
        throw std::logic_error("Labyrinth size must be at least 5x5");
    }

    int size = N * M;
    S--; F--;
    if (S < 0 || S >= size || F < 0 || F >= size || S == F) {
        throw std::logic_error("Invalid input");
    }

    Matrix<bool> walls = create_wall_matrix(S, F, N, M);
    DSU labyrinth(size);
    srand(time(0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int cell = i * M + j;
            int random = rand() % 61;

            if (j + 1 < M && random <= 25) {
                int rcell = i * M + (j + 1); // ѕрава€ €чейка (вертикальна€ стена)
                if (labyrinth.find(cell) != labyrinth.find(rcell)) {
                    labyrinth.unite(cell, rcell);
                    walls[2 * i + 1][j + 1] = false;
                }
            }

            if (i + 1 < N && random > 25 && random <= 50) {
                int dcell = (i + 1) * M + j; // Ќижн€€ €чейка (горизонтальна€ стена)
                if (labyrinth.find(cell) != labyrinth.find(dcell)) {
                    labyrinth.unite(cell, dcell);
                    walls[2 * i + 2][j] = false;
                }
            }
        }
    }

    while (labyrinth.find(S) != labyrinth.find(F)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int cell = i * M + j;
                int random = rand() % 101;
                int rcell = -1, dcell = -1;

                if (j + 1 < M) {
                    rcell = i * M + (j + 1);
                    if (labyrinth.find(cell) == labyrinth.find(rcell) ||
                        labyrinth.find(cell) != labyrinth.find(S) &&
                        labyrinth.find(rcell) != labyrinth.find(S)) {
                        rcell = -1;
                    }
                    else if (labyrinth.find(F) == labyrinth.find(rcell)) {
                        random = rand() % 51;
                    }
                }

                if (i + 1 < N) {
                    dcell = (i + 1) * M + j;
                    if (labyrinth.find(cell) == labyrinth.find(dcell) ||
                        labyrinth.find(cell) != labyrinth.find(S) &&
                        labyrinth.find(dcell) != labyrinth.find(S)) {
                        dcell = -1;
                    }
                    else if (labyrinth.find(F) == labyrinth.find(dcell)) {
                        random = 51 + rand() % 51;
                    }
                }

                if (rcell != -1 || dcell != -1) {
                    if (random <= 50 && rcell != -1 || dcell == -1) {
                        labyrinth.unite(cell, rcell);
                        walls[2 * i + 1][j + 1] = false;
                    }
                    else {
                        labyrinth.unite(cell, dcell);
                        walls[2 * i + 2][j] = false;
                    }
                }

            }
        }
    }

    return walls;
}

Matrix<bool> create_wall_matrix(int S, int F, int N, int M) {
    int rowS = S / M;
    int colS = S % M;
    int rowF = F / M;
    int colF = F % M;

    if (rowS != 0 && rowS != N - 1 && colS != 0 && colS != M - 1
        || rowF != 0 && rowF != N - 1 && colF != 0 && colF != M - 1) {
        throw std::logic_error("Start and finish must be on the border");
    }

    Matrix<bool> walls(2 * N + 1, M + 1);
    for (int i = 0; i < walls.rows(); i++) {
        for (int j = 0; j < walls.cols(); j++) {
            if (i % 2 == 0 && j != 0 && j % M == 0) {
                walls[i][j] = false;
            }
            else {
                walls[i][j] = true;
            }
        }
    }

    if (rowS == 0) walls[0][colS] = false;
    else if (rowS == N - 1) walls[2 * N][colS] = false;
    else if (colS == 0) walls[2 * rowS + 1][0] = false;
    else if (colS == M - 1) walls[2 * rowS + 1][M] = false;

    if (rowF == 0) walls[0][colF] = false;
    else if (rowF == N - 1) walls[2 * N][colF] = false;
    else if (colF == 0) walls[2 * rowF + 1][0] = false;
    else if (colF == M - 1) walls[2 * rowF + 1][M] = false;

    return walls;
}

void print_lab(Matrix<bool> labyrinth, int N, int M) {
    int num = 1;
    for (int i = 0; i < N * 2 + 1; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < M; j++) {
                std::cout << '+';
                if (labyrinth[i][j]) {
                    std::cout << "---";
                }
                else {
                    std::cout << "   ";
                }
            }
            std::cout << "+" << std::endl;
        }
        else {
            for (int j = 0; j < M; j++) {
                if (labyrinth[i][j]) {
                    std::cout << "|";
                }
                else {
                    std::cout << " ";
                }
                std::cout << std::setw(3) << num;
                num++;
            }
            if (labyrinth[i][M]) {
                std::cout << "|";
            }
            std::cout << std::endl;
        }
    }
}
