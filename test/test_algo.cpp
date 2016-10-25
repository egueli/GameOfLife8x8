/*
 * test_field.cpp
 *
 *  Created on: 24 Oct 2016
 *      Author: enrico
 */

#include "gtest/gtest.h"
#include "Algo.h"

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

GoLAlgorithm<8, 8> algo;

TEST(GoLAlgo, advance_blinker_changes) {
	EXPECT_NE(algo.advance(blinker_v()), blinker_v());
}

TEST(GoLAlgo, blinker_v_to_blinker_h) {
	EXPECT_EQ(algo.advance(blinker_v()), blinker_h());
}

TEST(GoLAlgo, blinker_h_to_blinker_v) {
	EXPECT_EQ(algo.advance(blinker_h()), blinker_v());
}



