#ifndef HDC2080_H_
#define HDC2080_H_


#include "driver/i2c_esp32_fun.h"

#ifdef __cplusplus
extern "C" {
#endif

//DEFAULT DEVICE ADDRESS
#ifndef HDC2080_ADDR
#define HDC2080_ADDR 0x40   //ADDR PIN = LOW
#endif 

//REGISTER MAP
#define TEMP_REG 0x00
#define HUM_REG 0x02
#define INTERRUPT_DRDY 0x04
#define TEMP_MAX 0x05
#define HUM_MAX 0x06
#define INTERRUPT_ENABLE 0x07
#define TEMP_OFFSET_ADJUST 0x08
#define HUM_OFFSET_ADJUST 0x09
#define TEMP_THR_L 0x0A
#define TEMP_THR_H 0x0B
#define RH_THR_L 0x0C
#define RH_THR_H 0x0D
#define RST_DRDY_INTCONF 0x0E
#define MEAS_CONFIG 0x0F
#define MANUFACTURERID_REG 0xFC		//always return 0x5449
#define DEVICEID_REG 0xFE			//always return 0x1050

typedef enum {
	RES14BIT =0,
	RES11BIT =1,
	RES8BIT=2
} hdc2080_bitres_t;

typedef enum  {
	DISABLED=0,
	S1_EVERY2MIN=1,
	S1_EVERY1MIN=2,
	S1_EVERY10SEC=3,
	S1_EVERY5SEC=4,
	S1_EVERY1SEC=5,
	S2_EVERY1SEC=6,
	S5_EVERY1SEC=7
} hdc2080_autoreadmode_t;

typedef enum  {
	ACTIVE_LOW=0,
	ACTIVE_HIGH=1
} hdc2080_int_pol_t;

typedef enum  {
	LEVEL_SENS =0,
	COMPARATOR =1
} hdc2080_int_mode_t;

typedef enum  {
	HUM_TEMP=0,
	TEMP_ONLY=1,
	HUM_ONLY=2
} hdc2080_read_conf_t;


uint8_t hdc_2080_echo();
bool hdc2080_isDataReady();
bool hdc2080_softReset();
bool hdc2080_configAutoMode(hdc2080_autoreadmode_t readMode);
bool hdc2080_configMeas(hdc2080_bitres_t temp_res, hdc2080_bitres_t hum_res, hdc2080_read_conf_t read_conf);
bool hdc2080_read(uint16_t *temp, uint16_t *hum);

 
//FUNCTIONS TO POSSIBLY IMPLEMENT
/*
bool hdc2080_configIntSource(bool DRDY_ENABLE, bool TH_ENABLE, bool TL_ENABLE, bool HH_ENABLE, bool HL_ENABLE);
bool hdc2080_setTempOffet(uint8_t tempOffset);
bool hdc2080_setHumOffset(uint8_t humOffset);
bool hdc2080_setTempThrH(uint8_t tempThrH);
bool hdc2080_setTempThrL(uint8_t tempThrL);
bool hdc2080_set HumThrH(uint8_t humThrH);
bool hdc2080_set HumThrL(uint8_t humThrL);
*/

#ifdef __cplusplus
}
#endif

#endif
