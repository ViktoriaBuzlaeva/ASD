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
            int random = rand() % 65;

            if (j + 1 < M && random < 25) {
                int rcell = i * M + (j + 1); // ѕрава€ €чейка (вертикальна€ стена)
                if (labyrinth.find(cell) != labyrinth.find(rcell)) {
                    labyrinth.unite(cell, rcell);
                    walls[2 * i + 1][j + 1] = false;
                }
            }

            if (i + 1 < N && random >= 25 && random < 50) {
                int dcell = (i + 1) * M + j; // Ќижн€€ €чейка (горизонтальна€ стена)
                if (labyrinth.find(cell) != labyrinth.find(dcell)) {
                    labyrinth.unite(cell, dcell);
                    walls[2 * i + 2][j] = false;
                }
            }
        }
    }

    int rootS = labyrinth.find(S);
    int rootF = labyrinth.find(F);

    while (rootS != rootF) {
        for (int i = 0; i < N && rootS != rootF; i++) {
            for (int j = 0; j < M && rootS != rootF; j++) {
                int cell = i * M + j;
                bool cell_in_S = (labyrinth.find(cell) == rootS);
                bool cell_in_F = (labyrinth.find(cell) == rootF);
                int rcell = -1, dcell = -1;

                if (j + 1 < M) {
                    rcell = i * M + (j + 1);
                    bool rcell_in_S = (labyrinth.find(rcell) == rootS);
                    bool rcell_in_F = (labyrinth.find(rcell) == rootF);
                    if (labyrinth.find(cell) == labyrinth.find(rcell) ||
                        !cell_in_S && !cell_in_F && !rcell_in_S && !rcell_in_F) {
                        rcell = -1;
                    }
                }

                if (i + 1 < N) {
                    dcell = (i + 1) * M + j;
                    bool dcell_in_S = (labyrinth.find(dcell) == rootS);
                    bool dcell_in_F = (labyrinth.find(dcell) == rootF);
                    if (labyrinth.find(cell) == labyrinth.find(dcell) ||
                        !cell_in_S && !cell_in_F && !dcell_in_S && !dcell_in_F) {
                        dcell = -1;
                    }
                }

                if (rcell != -1 || dcell != -1) {
                    int random = rand() % 100;
                    if (random < 50 && rcell != -1 || dcell == -1) {
                        labyrinth.unite(cell, rcell);
                        walls[2 * i + 1][j + 1] = false;
                    }
                    else {
                        labyrinth.unite(cell, dcell);
                        walls[2 * i + 2][j] = false;
                    }
                }

                rootS = labyrinth.find(S);
                rootF = labyrinth.find(F);
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

    create_passage(walls, rowS, colS, N, M);
    create_passage(walls, rowF, colF, N, M);

    return walls;
}

void create_passage(Matrix<bool>& walls, int row, int col, int N, int M) {
    if (row == 0) walls[0][col] = false;
    else if (row == N - 1) walls[2 * N][col] = false;
    else if (col == 0) walls[2 * row + 1][0] = false;
    else if (col == M - 1) walls[2 * row + 1][M] = false;
}

void print_lab(Matrix<bool> labyrinth, int N, int M) {
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
                std::cout << std::setw(3) << "";
            }
            if (labyrinth[i][M]) {
                std::cout << "|";
            }
            std::cout << std::endl;
        }
    }
}
