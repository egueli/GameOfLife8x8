#include <iostream>
#include <sstream>
#include <iomanip>

#include "field.h"
#include "algo.h"

template<size_t Cols, size_t Rows>
void print_field(const Field<Cols, Rows> & field);

void print_8x8_array(array< array<int, 8>, 8> &arr);



Field<8, 8> random_field();

int main(int argc, char *argv[]) {
	unsigned int r_seed;
	if (argc < 2) {
		r_seed = time(NULL);
	}
	else {
		std::istringstream iss(argv[1]);
		iss >> r_seed;
		if (iss.fail()) {
			cout << "Invalid random seed " << iss << endl;
			r_seed = time(NULL);
		}
	}
	srand(r_seed);
	Field<8, 8> seed = random_field();

	if (argc >= 3) {
		std::istringstream iss(argv[2]);
		int n;
		iss >> n;
		if (!iss.fail()) {
			int x = n % 8;
			int y = n / 8;
			cout << "Mutating cell at row " << y << " column " << x << endl;
			seed.set(x, y, !seed.get(x, y));
		}
	}


	print_field(seed);

	GoLAlgorithm<8, 8> algo;
	int start_time;
	int period;
	algo.run(seed, start_time, period);

	cout << "period start: " << start_time << endl;
	cout << "period length: " << period << endl;
	cout << endl;

	array< array<int, 8>, 8> mut_start = {};
	array< array<int, 8>, 8> mut_period = {};
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			Field<8, 8> mutated = seed;
			mutated.set(x, y, !mutated.get(x, y));
			int m_start;
			int m_period;
			algo.run(mutated, m_start, m_period);
			mut_start[x][y] = m_start - start_time;
			mut_period[x][y] = m_period - period;
		}
	}


	cout << "start time variations:" << endl;
	print_8x8_array(mut_start);
	cout << "period variations:" << endl;
	print_8x8_array(mut_period);
}

void print_8x8_array(array< array<int, 8>, 8> &arr) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			cout << setw(4) << arr[x][y] << " ";
		}
		cout << endl;
	}
}


template<size_t Cols, size_t Rows>
void print_field(const Field<Cols, Rows> & field) {
	for (int y = 0; y < Cols; y++) {
		for (int x = 0; x < Rows; x++) {
			printf("%c ", field.get(x, y) ? 'O' : '.');
		}
		printf("\n");
	}
}


Field<8, 8> random_field() {
	Field<8, 8> out;
	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			out.set(i, j, rand() % 2 == 0);
		}
	}
	return out;
}
