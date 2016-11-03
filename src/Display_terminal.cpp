/*
 * Display_terminal.cpp
 *
 *  Created on: 2 Nov 2016
 *      Author: enrico
 */

#include "Display.h"
#include <array>
#include <iostream>

using namespace std;

array< array<uint8_t, 8>, 8> buffer;
const uint8_t RED = 1;
const uint8_t GREEN = 2;



void Display::init() {
	clear();
}
void Display::clear() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			buffer[x][y] = 0;
		}
	}
}

void Display::set_red(uint8_t x, uint8_t y) {
	buffer[x][y] |= RED;
}

void Display::set_green(uint8_t x, uint8_t y) {
	buffer[x][y] |= GREEN;
}

void Display::commit() {
	cout << "\033[2J";
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			string to_print;
			switch (buffer[x][y]) {
			case RED:
				to_print = "❤ ";
				break;
			case GREEN:
				to_print = "💚 ";
				break;
			case RED | GREEN:
				to_print = "️💛 ";
				break;
			default:
				to_print = ". ";
			}
			cout << to_print;
		}
		cout << endl;
	}
}


