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

Field<8, 8> block() {
	Field<8, 8> out;
	out.set(1, 0);
	out.set(1, 1);
	out.set(2, 0);
	out.set(2, 1);
	return out;
}

Field<8, 8> complex_oscillator() {
	Field<8, 8> out;
	out.set(4, 0);
	out.set(4, 1);
	out.set(4, 6);
	out.set(4, 7);
	out.set(3, 2);
	out.set(3, 5);
	out.set(5, 2);
	out.set(5, 5);
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

TEST(GoLAlgo, blinker_h_has_start_time_of_0) {
	int start_time;
	int period;
	algo.run(blinker_h(), start_time, period);
	EXPECT_EQ(start_time, 0);
}

TEST(GoLAlgo, blinker_h_has_period_of_2) {
	int start_time;
	int period;
	algo.run(blinker_h(), start_time, period);
	EXPECT_EQ(period, 2);
}

TEST(GoLAlgo, block_is_stable) {
	int start_time;
	int period;
	algo.run(block(), start_time, period);
	EXPECT_EQ(period, 1);
}

TEST(GoLAlgo, more_complex_oscillator) {
	int start_time;
	int period;
	algo.run(complex_oscillator(), start_time, period);
	EXPECT_EQ(period, 6);
}
