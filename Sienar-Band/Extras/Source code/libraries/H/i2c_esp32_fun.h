/*
 * i2c_esp32_fun.h
 *
 *  Created on: 06 apr 2017
 *      Author: SIMO
 */

#ifndef MAIN_I2C_ESP32_FUN_H_
#define MAIN_I2C_ESP32_FUN_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "driver/adc.h"
#include "driver/i2c.h"

#define DATA_LENGTH          512  /*!<Data buffer length for test buffer*/
#define RW_TEST_LENGTH       129  /*!<Data length for r/w test, any value from 0-DATA_LENGTH*/
#define DELAY_TIME_BETWEEN_ITEMS_MS   1234 /*!< delay time between different test items */

#define I2C_MASTER_SCL_IO    19    /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO    18    /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUM_1   /*!< I2C port number for master dev */
#define I2C_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_FREQ_HZ    100000     /*!< I2C master clock frequency */

#define WRITE_BIT  I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT   I2C_MASTER_READ  /*!< I2C master read */
#define ACK_CHECK_EN   0x1     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS  0x0     /*!< I2C master will not check ack from slave */
#define ACK_VAL    0x0         /*!< I2C ack value */
#define NACK_VAL   0x1         /*!< I2C nack value */


void i2c_master_init();
esp_err_t I2Cwrite1byte(i2c_port_t i2c_num, uint8_t Address, uint8_t Register, uint8_t Data);
esp_err_t I2CwriteNbytes(i2c_port_t i2c_num, uint8_t Address, uint8_t Register, int Nbytes, uint8_t* Data);
esp_err_t I2CwriteNbytesSW(i2c_port_t i2c_num, uint8_t Address, int Nbytes, uint8_t* Data);
esp_err_t I2Cread1byte(i2c_port_t i2c_num, uint8_t Address, uint8_t Register);
esp_err_t I2CreadNbytes(i2c_port_t i2c_num, uint8_t Address, uint8_t Register, int Nbytes, uint8_t* Data);
void I2CInitialization(uint8_t Address, uint8_t Register);

#ifdef __cplusplus
}
#endif



#endif /* MAIN_I2C_ESP32_FUN_H_ */
