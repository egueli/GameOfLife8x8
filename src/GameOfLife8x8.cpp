#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include "field.h"


template<size_t Cols, size_t Rows>
void print_field(const Field<Cols, Rows> & field) {
	for (int x = 0; x < Cols; x++) {
		for (int y = 0; y < Rows; y++) {
			printf("%d ", field.get(x, y));
		}
		printf("\n");
	}
}

