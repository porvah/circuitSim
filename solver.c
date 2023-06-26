#include <stdio.h>
#include <stdlib.h>


void swapRows(double** eqs, int row1, int row2) {
	if (row1 != row2) {
		double* temp = eqs[row1];
		eqs[row1] = eqs[row2];
		eqs[row2] = temp;
	}
}

void eleminator(double** eqs, int index, int size) {
	//selecting the correct row for elemination
	if (eqs[index][index] == 0.0) {
		int rowNo = index;
		for (int i = index; i < size; i++) {
			if (eqs[i][index] != 0.0) {
				break;
			}
			rowNo++;
		}
		swapRows(eqs, index, rowNo);
	}
	//divide row by its index
	double val = eqs[index][index];
	for (int i = 0; i <= size; i++) {
		eqs[index][i] /= val;
	}
	//forward elemination
	for (int i = index + 1; i < size; i++) {
		double multFactor = -1.0 * eqs[i][index];
		for (int j = 0; j <= size; j++) {
			eqs[i][j] += (multFactor * eqs[index][j]);
		}

	}
	//backward elemination
	for (int i = index - 1; i >= 0; i--) {
		double multFactor = -1.0 * eqs[i][index];
		for (int j = 0; j <= size; j++) {
			eqs[i][j] += (multFactor * eqs[index][j]);
		}
	}

}

double* solver(int n, double** eqs) {
	double* solution = (double*)malloc(n * sizeof(double));
	//getting row echlon form
	for (int i = 0; i < n; i++) {
		eleminator(eqs, i, n);
	}
	for (int i = 0; i < n; i++) {
		solution[i] = eqs[i][n];
	}
	return solution;
}