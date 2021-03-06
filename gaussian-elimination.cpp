﻿//https://github.com/ejalowiec/nm-gaussian-elimination

#include <iostream>
#include <fstream>
#include<iomanip>

using namespace std;

void showMatrix(double**, int );
void pivotizeMatrix(double**, int);

int main() {

	// ---------------------- reading file ----------------------

	fstream file;
	file.open("test2.txt", ios::in);

	if (!file.good()) {
		cerr << "File does not exist";
		exit(0);
	}

	int size;
	file >> size;

	if (size <= 1) {
		cerr << "Number of equations is too low";
		exit(0);
	}

	double** arr = new double*[size];
	for (int i = 0; i < size; ++i)
		arr[i] = new double[size + 1];

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size + 1; ++j)
			file >> arr[i][j];
	}

	file.close();

	double* resultArr = new double[size];

	// displaying initial equations
	cout << "No of equations: " << size << endl;
	cout << "Equations: " << endl;
	showMatrix(arr, size);

	// pivotization
	for (int i = 0; i < size - 1; i++) {
		for (int k = i + 1; k < size; ++k) {
			if (abs(arr[i][i]) < abs(arr[k][i])) {
				for (int j = 0; j <= size; ++j) {
					double temp = arr[i][j];
					arr[i][j] = arr[k][j];
					arr[k][j] = temp;
				}
			}
		}

		cout << "\nMatrix after " << i + 1 << " pivotisation:\n";
		showMatrix(arr, size);

		// gaussian elimination

		for (int k = i + 1; k < size; ++k) {
			double ratio = arr[k][i] / arr[i][i];
			for (int j = 0; j <= size; ++j)
				arr[k][j] -= (ratio * arr[i][j]);
		}
		cout << "\nMatrix after " << i + 1 << " gaussian iteration:\n";
		showMatrix(arr, size);
	}

	cout << "\nMatrix after gaussian elimination:\n";
	showMatrix(arr, size);

	// back substitution
	for (int i = size - 1; i >= 0; --i)	{
		resultArr[i] = arr[i][size];
		for (int j = i + 1; j < size; ++j) {
			if (j != i)
				resultArr[i] -= (arr[i][j] * resultArr[j]);
		}
		resultArr[i] /= arr[i][i];
	}

	// print result
	cout << "\nResult:\n";
	for (int i = 0; i < size; ++i)
		cout << "x" << i + 1 << ":\t" << resultArr[i] << endl;

	// delete dynamic arrays
	for (int i = 0; i < size; ++i) {
		delete[] arr[i];
	}

	delete[] arr;

	return 0;
}

void showMatrix(double** arr, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j <= size; ++j) {
			cout << arr[i][j] << setw(12);
		}
		cout << "\n";
	}
}