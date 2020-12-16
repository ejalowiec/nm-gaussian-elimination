//https://github.com/ejalowiec/nm-gaussian-elimination

#include <iostream>
#include <fstream>
#include<iomanip>

using namespace std;

int main() {

	// ---------------------- reading file ----------------------

	fstream file;
	file.open("test.txt", ios::in);

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

	double* tempArr = new double[size];

	// displaying initial equations
	cout << "Equations: " << endl;
	cout << "No of equations: " << size << endl;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j <= size; ++j)
			cout << arr[i][j] << setw(12);
		cout << "\n";
	}

	// pivotisation
	for (int i = 0; i < size; ++i) {
		for (int k = i + 1; k < size; ++k) {
			if (abs(arr[i][i]) < abs(arr[k][i])) {
				for (int j = 0; j <= size; ++j) {
					double temp = arr[i][j];
					arr[i][j] = arr[k][j];
					arr[k][j] = temp;
				}
			}
		}
	}
	cout << "\nMatrix after pivotisation:\n";

	// matrix after pivotisation
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j <= size; ++j)
			cout << arr[i][j] << setw(12);
		cout << "\n";
	}

	// gauss elimination
	for (int i = 0; i < size - 1; i++) {
		for (int k = i + 1; k < size; ++k) {
			double ratio = arr[k][i] / arr[i][i];
			cout << ratio << endl;
			//make the elements below the pivot elements equal to zero or eliminate the variables
			for (int j = 0; j <= size; ++j)
				arr[k][j] -= (ratio * arr[i][j]);
		}
	}

	cout << "\nMatrix after Gaussian elimination:\n";
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j <= size; j++)
			cout << arr[i][j] << setw(12);
		cout << "\n";
	}

	//back-substitution

	//x is an array whose values correspond to the values of x,y,z..
	for (int i = size - 1; i >= 0; i--)	{
		//make the variable to be calculated equal to the rhs of the last equation
		tempArr[i] = arr[i][size];
		for (int j = i + 1; j < size; ++j)
			//then subtract all the lhs values except the coefficient of the variable whose value is being calculated
			if (j != i)
				tempArr[i] = tempArr[i] - arr[i][j] * tempArr[j];
		//now finally divide the rhs by the coefficient of the variable to be calculated
		tempArr[i] = tempArr[i] / arr[i][i];
	}
	cout << "\nThe values of the variables are as follows:\n";
	for (int i = 0; i < size; ++i)
		cout << tempArr[i] << endl;            // Print the values of x, y,z,....    
	


	cout << "\nMatrix: " << endl;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size + 1; ++j)
			cout << arr[i][j] << setw(12);
		cout << "\n";
	}

	for (int i = 0; i < size; ++i) {
		delete[] arr[i];
	}

	delete[] arr;

	return 0;
}