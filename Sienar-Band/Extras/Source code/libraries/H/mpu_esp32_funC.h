/*
 * mpu_esp32_funC.h
 *
 *  Created on: 19 jun 2017
 *      Author: FRAX
 */

#ifndef MAIN_MPU_ESP32_FUNC_H_
#define MAIN_MPU_ESP32_FUNC_H_

#include "i2c_esp32_fun.h"

//REGISTER MAP
#define SELF_TEST_X_GYRO 0x00
#define SELF_TEST_Y_GYRO 0x01
#define SELF_TEST_Z_GYRO 0x02
#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E
#define SELF_TEST_Z_ACCEL 0x0F
#define XG_OFFSET_H      0x13  // User-defined trim values for gyroscope
#define XG_OFFSET_L      0x14
#define YG_OFFSET_H      0x15
#define YG_OFFSET_L      0x16
#define ZG_OFFSET_H      0x17
#define ZG_OFFSET_L      0x18
#define SMPLRT_DIV       0x19
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define ACCEL_CONFIG2    0x1D
#define LP_ACCEL_ODR     0x1E
#define WOM_THR          0x1F
#define MOT_DUR          0x20  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
#define ZMOT_THR         0x21  // Zero-motion detection threshold bits [7:0]
#define ZRMOT_DUR        0x22  // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms
#define FIFO_EN          0x23
#define I2C_MST_CTRL     0x24
#define I2C_SLV0_ADDR    0x25
#define I2C_SLV0_REG     0x26
#define I2C_SLV0_CTRL    0x27
#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_CTRL    0x2A
#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_CTRL    0x2D
#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_CTRL    0x30
#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_DI      0x35
#define I2C_MST_STATUS   0x36
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define DMP_INT_STATUS   0x39  // Check DMP interrupt
#define INT_STATUS       0x3A
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define MOT_DETECT_STATUS 0x61
#define I2C_SLV0_DO      0x63
#define I2C_SLV1_DO      0x64
#define I2C_SLV2_DO      0x65
#define I2C_SLV3_DO      0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET  0x68
#define MOT_DETECT_CTRL  0x69
#define USER_CTRL        0x6A  // Bit 7 enable DMP, bit 3 reset DMP
#define PWR_MGMT_1       0x6B // Device defaults to the SLEEP mode
#define PWR_MGMT_2       0x6C
#define DMP_BANK         0x6D  // Activates a specific bank in the DMP
#define DMP_RW_PNT       0x6E  // Set read/write pointer to a specific start address in specified DMP bank
#define DMP_REG          0x6F  // Register in DMP from which to read or to which to write
#define DMP_REG_1        0x70
#define DMP_REG_2        0x71
#define FIFO_COUNTH      0x72
#define FIFO_COUNTL      0x73
#define FIFO_R_W         0x74
#define WHO_AM_I_MPU9250 0x75 // Should return 0x71
#define XA_OFFSET_H      0x77
#define XA_OFFSET_L      0x78
#define YA_OFFSET_H      0x7A
#define YA_OFFSET_L      0x7B
#define ZA_OFFSET_H      0x7D
#define ZA_OFFSET_L      0x7E


#ifndef MPU9250_ADDRESS
#define MPU9250_ADDRESS 0x68  // Default device address when ADO = 0
#endif


#define AK8963_ADDRESS   0x0C
#define WHO_AM_I_AK8963  0x00 // should return 0x48

#define AK8963_ST1       0x02  // data ready status bit 0
#define AK8963_XOUT_L    0x03  // data
#define AK8963_ST2       0x09  // status2
#define AK8963_CNTL      0x0A
#define AK8963_ASAX      0x10
#define AK8963_ASAY      0x11
#define AK8963_ASAZ      0x12

#define HIGH      1
#define LOW       0

typedef enum AccelScale {
  AFS_2G = 0,
  AFS_4G,
  AFS_8G,
  AFS_16G
} AccelScale;

typedef enum GyroScale {
  GFS_250DPS = 0,
  GFS_500DPS,
  GFS_1000DPS,
  GFS_2000DPS
}GyroScale;

typedef enum FIFO_MODE {
  REPLACE = 0,
  KEEP,
}FIFO_MODE;

typedef enum EXT_SYNC_SET {
  DISABLED = 0,
  SET_TEMP_OUT_L,
  SET_GYRO_XOUT_L,
  SET_GYRO_YOUT_L,
  SET_GYRO_ZOUT_L,
  SET_ACCEL_XOUT_L,
  SET_ACCEL_YOUT_L,
  SET_ACCEL_ZOUT_L
}EXT_SYNC_SET;

typedef enum G_DLPF_CFG {
  GYRO_LP250HZ = 0,
  GYRO_LP184HZ,
  GYRO_LP92HZ,
  GYRO_LP41HZ,
  GYRO_LP20HZ,
  GYRO_LP10HZ,
  GYRO_LP5HZ,
  GYRO_LP3600HZ
}G_DLPF_CFG;

typedef enum A_DLPF_CFG {
  ACCEL_LP460HZ = 0,
  ACCEL_LP184HZ,
  ACCEL_LP92HZ,
  ACCEL_LP41HZ,
  ACCEL_LP20HZ,
  ACCEL_LP10HZ,
  ACCEL_LP5HZ
}A_DLPF_CFG;

typedef enum MAG_OPMODE {
  POWER_DOWN = 0,
  SINGLE_MEAS,
  CONT_MEAS_1,
  EXT_TRIG = 4,
  CONT_MEAS_2 = 6,
  SELF_TEST = 8,
  FUSE_ROM = 15
}MAG_OPMODE;

typedef enum MAG_BITDEPTH {
  MAG14BIT = 0,
  MAG16BIT
}MAG_BITDEPTH;


int MPUconfig();
//void config();
//void MPUconfig(FIFO_MODE mode, EXT_SYNC_SET sync_set);
int MPUsampleDivider(uint8_t divider);
int MPUbypassEnable();
int MAGconfig(MAG_OPMODE opmode, MAG_BITDEPTH depth);
//bool IMUecho();
//void setAccelOffset(int16_t accelX, int16_t accelY, int16_t accelZ);
//void getAccelOffset(int16_t *AccelOffset);
//void setGyroOffset(int16_t gyroX, int16_t gyroY, int16_t gyroZ);
//void getGyroOffset(int16_t *GyroOffset);
int MPUsetAccelScale(AccelScale ascale);
int MPUsetAccelFilter(bool enable, A_DLPF_CFG filter);
//void setGyroScale(GyroScale gscale);
int MPUsetGyroFilter(bool enable, G_DLPF_CFG filter);  //BUG!!! CHECK CPP FILE
int MPUgetAccelData(int16_t *AccelData);
int MPUgetGyroData(int16_t *GyroData);
//bool MAGecho();
int MPUgetMagData(int16_t *MagData);
//bool isMagDataReady();
//bool isMagOverflow();
//void calibrateIMU(int16_t *AccelOffset, int16_t *GyroOffset);
//void calibrateIMU(int16_t *AccelOffset, float *AccelSensCorrection, int16_t *GyroOffset);
//void calibrateMAG(int16_t *MagOffset, float *MagSensCorrection);


#endif /* MAIN_MPU_ESP32_FUNC_H_ */