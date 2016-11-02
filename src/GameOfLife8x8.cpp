#include <iostream>
#include <sstream>
#include <iomanip>
#include <climits>

#include "field.h"
#include "algo.h"

template<size_t Cols, size_t Rows>
void print_field(const Field<Cols, Rows> & field);

void print_8x8_array(array< array<int, 8>, 8> &arr);
pair<int, int> max_2d(array< array<int, 8>, 8> &arr);



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

	for (int i = 0; i < argc - 2; i++) {
		std::istringstream iss(argv[i + 2]);
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

	Field<8, 8> field = seed;
	Field<8, 8> last_field;
	for (int i=0; i<start_time; i++) {
		field = algo.advance(field);
		cout << "STEP " << i << endl;
		print_field(field);
		if (i > 0) {
			cout << "Difference with previous:" << endl;
			print_field(field ^ last_field);
		}
		cout << endl;

		last_field = field;
	}

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
	auto b_start = max_2d(mut_start);
	cout << "biggest variation: " << b_start.first << " at " << b_start.second << endl;

	cout << "period variations:" << endl;
	print_8x8_array(mut_period);
	auto b_period = max_2d(mut_period);
	cout << "biggest variation: " << b_period.first << " at " << b_period.second << endl;
}

pair<int, int> max_2d(array< array<int, 8>, 8> &arr) {
	int m = INT_MIN;
	int mn = 0;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int v = arr[x][y];
			if (m < v) {
				m = v;
				mn = y * 8 + x;
			}
		}
	}
	return pair<int, int>(m, mn);
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
			printf(field.get(x, y) ? "⬜️ " : "⬛ ");
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
