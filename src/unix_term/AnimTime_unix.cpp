/*
 * AnimTime_unix.cpp
 *
 *  Created on: 3 Nov 2016
 *      Author: enrico
 */


#include "../AnimTime.h"
#include <unistd.h>

void my_sleep(unsigned int millis) {
	sleep(millis/1000);
}
