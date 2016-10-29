#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

#include "field.h"
#include "algo.h"

template<size_t Cols, size_t Rows>
void print_field(const Field<Cols, Rows> & field);

Field<8, 8> random_field();


int main(int argc, char ** argv) {
	srand(time(NULL));
	Field<8, 8> seed = random_field();
	print_field(seed);

	GoLAlgorithm<8, 8> algo;
	int start_time;
	int period;
	algo.run(seed, start_time, period);

	cout << "period start: " << start_time << endl;
	cout << "period length: " << period << endl;
}


template<size_t Cols, size_t Rows>
void print_field(const Field<Cols, Rows> & field) {
	for (int x = 0; x < Cols; x++) {
		for (int y = 0; y < Rows; y++) {
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
