/*
 * mpu_esp32_funC.cpp
 *
 *  Created on: 18 jun 2017
 *      Author: FRAX
 */
 
 #include "mpu_esp32_funC.h"
 
 int MPUconfig() {
  uint8_t configData =   REPLACE << 6 |	//set FIFO MODE
                         DISABLED << 3 |	//DISABLE EXT_SYNC
                         GYRO_LP250HZ;	//set LP filter to 250HZ
  int ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, CONFIG, configData);
  return ret;
}

int MPUsampleDivider(uint8_t divider){
  int ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, SMPLRT_DIV, divider);
  return ret;
}

int MPUbypassEnable() {
  int ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, USER_CTRL, 0x0);  //disable I2C Master interface
  if (ret == ESP_OK)
	  ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, INT_PIN_CFG, 0x02); //enable bypass mode
  return ret;
}

int MAGconfig(MAG_OPMODE opmode, MAG_BITDEPTH depth) {
  uint8_t configData = depth << 4 |
                       opmode;
  int ret = I2Cwrite1byte(I2C_MASTER_NUM, AK8963_ADDRESS, AK8963_CNTL, configData);
  return ret;
}

int MPUsetAccelScale(AccelScale ascale) {
  uint8_t configData = ascale << 3;
  int ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, ACCEL_CONFIG, configData);
  return ret;
}

int MPUsetAccelFilter(bool enable, A_DLPF_CFG filter) {
  uint8_t configData = !enable << 3
                       | filter;
  int ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, ACCEL_CONFIG2, configData);
  return ret;
}

/*int MPUsetGyroScale(GyroScale gscale) {
  uint8_t configData = gscale;
  int ret = I2Cread1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, GYRO_CONFIG);
  
}*/

//SET GYROSCALE E CORREGGERE IL BUG!!!!

int MPUsetGyroFilter(bool enable, G_DLPF_CFG filter) {
  int ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, GYRO_CONFIG, !enable); //BUG!!!!! STO SETTANDO ANCHE FULLSCALERANGE a 250DPS!!!!
  ret = I2Cwrite1byte(I2C_MASTER_NUM, MPU9250_ADDRESS, CONFIG, filter);
  return ret;
}

int MPUgetAccelData(int16_t *AccelData) {
  uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
  int ret = I2CreadNbytes(I2C_MASTER_NUM, MPU9250_ADDRESS, ACCEL_XOUT_H, 6, rawData);
  if(ret == ESP_OK)
  {
	  AccelData[0] = ((int16_t)rawData[0] << 8) | rawData[1];
	  AccelData[1] = ((int16_t)rawData[2] << 8) | rawData[3];
	  AccelData[2] = ((int16_t)rawData[4] << 8) | rawData[5];
	  return ret;
  }
  else
	  return ret;
}

int MPUgetGyroData(int16_t *GyroData) {
  uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
  int ret = I2CreadNbytes(I2C_MASTER_NUM, MPU9250_ADDRESS, GYRO_XOUT_H, 6, rawData);
  if(ret == ESP_OK)
  {
	  GyroData[0] = ((int16_t)rawData[0] << 8) | rawData[1];
	  GyroData[1] = ((int16_t)rawData[2] << 8) | rawData[3];
	  GyroData[2] = ((int16_t)rawData[4] << 8) | rawData[5];
	  return ret;
  }
  else
  	  return ret;
}

int MPUgetMagData(int16_t *MagData) {
  uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
  int ret = I2CreadNbytes(I2C_MASTER_NUM, AK8963_ADDRESS, AK8963_XOUT_L, 6, rawData);
  if(ret == ESP_OK)
  {
	  MagData[0] = ((int16_t)rawData[1] << 8) | rawData[0]; //Lower and Higher bytes are inverted respect of MPU9255 accel and gyro
	  MagData[1] = ((int16_t)rawData[3] << 8) | rawData[2];
	  MagData[2] = ((int16_t)rawData[5] << 8) | rawData[4];
  }
  if(ret == ESP_OK)
	  ret = I2Cread1byte(I2C_MASTER_NUM, AK8963_ADDRESS, AK8963_ST2); //needed to enable new measurement
  return ret;
}
