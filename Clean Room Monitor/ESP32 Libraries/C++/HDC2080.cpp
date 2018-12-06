#include "HDC2080.h"

HDC2080::HDC2080(){
_address=HDC2080_ADDR; //default address if ADDR=0
}

HDC2080::HDC2080(const int address){
_address=address;
}

bool HDC2080::isDataReady(){
	uint8_t rawData= I2Cread1byte(I2C_MASTER_NUM, _address, INTERRUPT_DRDY);
	if (rawData & 0b10000000) {
		return true;
		}
	else {
		return false;
		}
}

bool HDC2080::softReset(){
	uint8_t registerData= I2Cread1byte(I2C_MASTER_NUM, _address, RST_DRDY_INTCONF);
	int ret=I2Cwrite1byte(I2C_MASTER_NUM, _address, RST_DRDY_INTCONF, registerData|0b10000000);
	return !!ret;  // !!=convert int to boolean via double negation
}


bool HDC2080::configMode(hdc2080_autoreadmode_t readMode){
	uint8_t registerData= I2Cread1byte(I2C_MASTER_NUM, _address, RST_DRDY_INTCONF);
	registerData=registerData & 0b10001111; //set 5th-6th-7th bit to 0, let others untouched
	uint8_t configData;
	switch (readMode){
		case DISABLED:
		configData=0b00000000|registerData;
		break;
		case S1_EVERY2MIN:
		configData=0b00010000|registerData;
		break;
		case S1_EVERY1MIN:
		configData=0b00100000|registerData;
		break;
		case S1_EVERY10SEC:
		configData=0b00110000|registerData;
		break;
		case S1_EVERY5SEC:
		configData=0b01000000|registerData;
		break;
		case S1_EVERY1SEC:
		configData=0b01010000|registerData;
		break;
		case S2_EVERY1SEC:
		configData=0b01100000|registerData;
		break;
		case S5_EVERY1SEC:
		configData=0b01110000|registerData;
		break;
		default:
		configData=0b00000000|registerData;
		break;
	}
	int ret=I2Cwrite1byte(I2C_MASTER_NUM, _address, RST_DRDY_INTCONF, configData);
	return !!ret;
}

bool HDC2080::configMeas(hdc2080_bitres_t temp_res, hdc2080_bitres_t hum_res, hdc2080_read_conf_t read_conf) {
	uint8_t configData= temp_res<<6 |
                    hum_res<<4 |
                    read_conf<<1;
	int ret=I2Cwrite1byte(I2C_MASTER_NUM, _address, MEAS_CONFIG, configData);
	return !!ret;
}


bool HDC2080::read(uint16_t &temp, uint16_t &hum){
	//uint8_t registerData= I2Cread1byte(I2C_MASTER_NUM, _address, MEAS_CONFIG); DEBUG: NOT NEEDED?
	//trigger the measure
	//registerData=registerData|0b00000001;
	int ret=I2Cwrite1byte(I2C_MASTER_NUM, _address, MEAS_CONFIG, 1); //lsb of the register is the measurement trigger
	//read the data
	uint8_t Data[4];
	ret = I2CreadNbytes(I2C_MASTER_NUM, _address, TEMP_REG, 4, Data);
	// set the data in the memory pointed
	temp=Data[1]<<8|Data[0];
	hum =Data[3]<<8|Data[2];
	return !!ret;
}

