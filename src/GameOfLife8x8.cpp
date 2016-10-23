#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include "field.h"


int wrap(int n, int max) {
	while (n < 0) n += max;
	while (n >= max) n -= max;
	return n;
}

template<size_t Cols, size_t Rows>
void find_neighbors(
		array<array<int, Rows>, Cols> &neighbors,
		const Field<Cols, Rows> &current) {
	for (int x = 0; x < Cols; x++) {
		for (int y = 0; y < Rows; y++) {
			for (int nx = -1; nx <= 1; nx++) {
				for (int ny = -1; ny <= 1; ny++) {
					if (nx == 0 && ny == 0)
						continue;

					int xx = wrap(x + nx, Rows);
					int yy = wrap(y + ny, Cols);
					if (current.get(xx, yy)) {
						neighbors[x][y]++;
					}
				}
			}
		}
	}
}

template<size_t Cols, size_t Rows>
void print_field(const Field<Cols, Rows> & field) {
	for (int x = 0; x < Cols; x++) {
		for (int y = 0; y < Rows; y++) {
			printf("%d ", field.get(x, y));
		}
		printf("\n");
	}
}

template<size_t Cols, size_t Rows>
void print_neighbors(array<array<int, Rows>, Cols> &neighbors) {
	for (int x = 0; x < Cols; x++) {
		for (int y = 0; y < Rows; y++) {
			printf("%d ", neighbors[x][y]);
		}
		printf("\n");
	}
}


template<size_t Cols, size_t Rows>
Field<Cols, Rows> advance(const Field<Cols, Rows> & current) {
	array<array<int, Rows>, Cols> neighbors = {};
	find_neighbors(neighbors, current);
	print_neighbors(neighbors);

	Field<Cols, Rows> next;
	for (int x = 0; x < Cols; x++) {
		for (int y = 0; y < Rows; y++) {
			if (!current.get(x, y)) {
				next.set(x, y, neighbors[x][y] == 3);
			}
			else {
				int n = neighbors[x][y];
				next.set(x, y, (n == 2 || n == 3));
			}
		}
	}
	return next;
}

Field<8, 8> blinker_v() {
	Field<8, 8> out;
	out.set(0, 1);
	out.set(1, 1);
	out.set(2, 1);
	return out;
}

Field<8, 8> blinker_h() {
	Field<8, 8> out;
	out.set(1, 0);
	out.set(1, 1);
	out.set(1, 2);
	return out;
}

bool test_advance_blinker_changes() {
	return advance(blinker_v()) != blinker_v();
}

bool test_blinker_h() {
	return advance(blinker_v()) == blinker_h();
}

bool test_blinker_v() {
	return advance(blinker_h()) == blinker_v();
}

void run_test(const char* testName, const bool result) {
	printf("%s %s\n", (result ? "PASS" : "FAIL"), testName);
}

#define TEST(f) run_test(#f, f())

int main()
{
	TEST(test_advance_blinker_changes);
	TEST(test_blinker_h);
	TEST(test_blinker_v);
}
