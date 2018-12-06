/*
 * i2c_esp32_fun.c
 *
 *  Created on: 06 apr 2017
 *      Author: SIMO
 */

#include "i2c_esp32_fun.h"
#include "sdkconfig.h"


void i2c_master_init()
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t I2Cwrite1byte(i2c_port_t i2c_num, uint8_t Address, uint8_t Register, uint8_t Data)
{
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, Address << 1 | WRITE_BIT, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, Register, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, Data, ACK_CHECK_EN);
	i2c_master_stop(cmd);
	int ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_FAIL)
		return ESP_FAIL;
	else
		return ESP_OK;
}


esp_err_t I2CwriteNbytes(i2c_port_t i2c_num, uint8_t Address, uint8_t Register, int Nbytes, uint8_t* Data)
{
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, Address << 1 | WRITE_BIT, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, Register, ACK_CHECK_EN);
	for (int i = 0; i < Nbytes; i++)
	{
		i2c_master_write_byte(cmd, Data[i], ACK_VAL);
		//printf("data = %d\n", Data[0]);
	}
	i2c_master_stop(cmd);
	int ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_FAIL)
		return ESP_FAIL;
	else
		return ESP_OK;
}


esp_err_t I2CwriteNbytesSW(i2c_port_t i2c_num, uint8_t Address, int Nbytes, uint8_t* Data)
{
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, Address << 1 | WRITE_BIT, ACK_CHECK_EN);
	//i2c_master_write_byte(cmd, Register, ACK_CHECK_EN);
	for (int i = 0; i < Nbytes; i++)
	{
		i2c_master_write_byte(cmd, Data[i], ACK_VAL);
		//printf("data = %d\n", Data[0]);
	}
	i2c_master_stop(cmd);
	int ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_FAIL)
		return ESP_FAIL;
	else
		return ESP_OK;
}


esp_err_t I2Cread1byte(i2c_port_t i2c_num, uint8_t Address, uint8_t Register)
{
	uint8_t data;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, Address << 1 | WRITE_BIT, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, Register, ACK_CHECK_EN);
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, Address << 1 | READ_BIT, ACK_CHECK_EN);
	i2c_master_read_byte(cmd, &data, NACK_VAL);
	i2c_master_stop(cmd);
	int ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	//printf("data = %d\n", data);
	if (ret == ESP_FAIL)
		return ESP_FAIL;
	else
		return ESP_OK;
}


esp_err_t I2CreadNbytes(i2c_port_t i2c_num, uint8_t Address, uint8_t Register, int Nbytes, uint8_t* Data)
{
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, Address << 1 | WRITE_BIT, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, Register, ACK_CHECK_EN);
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, Address << 1 | READ_BIT, ACK_CHECK_EN);
	for (int i = 0; i < Nbytes - 1; i++)
	{
		i2c_master_read_byte(cmd, &Data[i], ACK_VAL);
	}
	i2c_master_read_byte(cmd, &Data[Nbytes - 1], NACK_VAL);
	i2c_master_stop(cmd);
	int ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_FAIL)
		return ESP_FAIL;
	else
		return ESP_OK;
}

void I2CInitialization(uint8_t Address, uint8_t Register)
{
	int ret = I2Cread1byte(I2C_MASTER_NUM, Address, Register);
	while (ret != ESP_OK)
	{
		ret = I2Cread1byte(I2C_MASTER_NUM, Address, Register);
	}
}





