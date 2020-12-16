//https://github.com/ejalowiec/nm-gaussian-elimination

#include <iostream>
#include <fstream>

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



	// ---------------------- displaying results ----------------------
	// 1.
	cout << "Equations: " << endl;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size + 1; ++j)
			cout << arr[i][j] << "\t";
		cout << "\n";
	}
}