/*
 * switch_lib.c
 *
 *  Created on: 25 lug 2017
 *      Author: arcib
 */

#include "switch_lib.h"
#include "sdkconfig.h"


bool setSwitchChan(uint8_t Address, int shift)
{
	uint8_t writeNbyte[1];
	int len = 1;

	writeNbyte[0] = 0b00000001;

	for(int i = 1; i < shift; i++)
		writeNbyte[0] <<= 1;

	int ret = I2CwriteNbytesSW(I2C_MASTER_NUM, Address, len, writeNbyte);

	if (ret == ESP_OK)
	{
		return 1;
	}
	else
		return 0;
}


bool setSwitchOff(uint8_t Address)
{
	uint8_t writeNbyte[1];
	int len = 1;

	writeNbyte[0] = 0b00000000;

	int ret = I2CwriteNbytesSW(I2C_MASTER_NUM, Address, len, writeNbyte);

	if (ret == ESP_OK)
		{
			return 1;
		}
		else
			return 0;
}
