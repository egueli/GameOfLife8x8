/*
 * Field.h
 *
 *  Created on: 23 Oct 2016
 *      Author: enrico
 */

#ifndef FIELD_H_
#define FIELD_H_

#include <array>

using namespace std;


template<size_t Cols, size_t Rows>
class Field {
public:
	Field() : cells() {}

	void set(int x, int y) {
		set(x, y, true);
	}

	void set(int x, int y, bool alive) {
		cells[x][y] = alive;
	}

	bool get(int x, int y) const {
		return cells[x][y];
	}

	bool operator==(const Field<Cols, Rows> & rhs) const {
		for (int x=0; x<Cols; x++) {
			for (int y=0; y<Rows; y++) {
				if (get(x, y) != rhs.get(x, y))
					return false;
			}
		}
		return true;
	}

	bool operator!=(const Field<Cols, Rows> & rhs) const {
		return !operator==(rhs);
	}

	Field<Cols, Rows> operator^(const Field<Cols, Rows> & rhs) const {
		Field<Cols, Rows> out;
		for (int x=0; x<Cols; x++) {
			for (int y=0; y<Rows; y++) {
				out.set(x, y, get(x, y) ^ rhs.get(x, y));
			}
		}
		return out;
	}

	Field<Cols, Rows> operator&(const Field<Cols, Rows> & rhs) const {
		Field<Cols, Rows> out;
		for (int x=0; x<Cols; x++) {
			for (int y=0; y<Rows; y++) {
				out.set(x, y, get(x, y) & rhs.get(x, y));
			}
		}
		return out;
	}

private:
	array<array<bool, Rows>, Cols> cells;
};



#endif /* FIELD_H_ */
