/*
 * switch_lib.h
 *
 *  Created on: 25 lug 2017
 *      Author: arcib
 */

#ifndef MAIN_SWITCH_LIB_H_
#define MAIN_SWITCH_LIB_H_

#include "driver/i2c_esp32_fun.h"
#include "driver/adc.h"

bool setSwitchChan(uint8_t Address, int shift);
bool setSwitchOff(uint8_t Address);


#endif /* MAIN_SWITCH_LIB_H_ */
