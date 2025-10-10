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