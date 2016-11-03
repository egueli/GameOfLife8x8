/*
 * Display.h
 *
 *  Created on: 2 Nov 2016
 *      Author: enrico
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

struct Display {
	void init();
	void clear();
	void set_red(uint8_t x, uint8_t y);
	void set_green(uint8_t x, uint8_t y);
	void commit();
};


#endif /* DISPLAY_H_ */
