/*
 * Algo.h
 *
 *  Created on: 24 Oct 2016
 *      Author: enrico
 */

#ifndef ALGO_H_
#define ALGO_H_

#include <cstddef>
#include "Field.h"

template<size_t Cols, size_t Rows>
class GoLAlgorithm {
public:
	Field<Cols, Rows> advance(const Field<Cols, Rows> & current);

private:
	void find_neighbors(
		array<array<int, Rows>, Cols> &neighbors,
		const Field<Cols, Rows> &current);
	int wrap(int n, int max);
};

template<size_t Cols, size_t Rows>
Field<Cols, Rows> GoLAlgorithm<Cols, Rows>::advance(const Field<Cols, Rows> & current) {
	array<array<int, Rows>, Cols> neighbors = {};
	find_neighbors(neighbors, current);

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

template<size_t Cols, size_t Rows>
void GoLAlgorithm<Cols, Rows>::find_neighbors(
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
int GoLAlgorithm<Cols, Rows>::wrap(int n, int max) {
	while (n < 0) n += max;
	while (n >= max) n -= max;
	return n;
}

#endif /* ALGO_H_ */
