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
