// Copyright 2025 Viktoria Buzlaeva

#include "../lib_algorithms/algorithms.h"

int find_local_min_matrix(Matrix<int> matrix) {
	srand(time(0));
	int size = matrix.rows();
	int x = rand() % (size);
	int y = rand() % (size);

	int min_value = matrix[x][y];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((i == x - 1 || i == x + 1) && j == y || (j == y - 1 || j == y + 1) && i == x) {
				if (min_value > matrix[i][j]) {
					min_value = matrix[i][j];
					x = i;
					y = j;
				}
			}
		}
	}
	return min_value;
}