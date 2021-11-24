/*
 * SPS30.c
 *
 *  Created on: Nov 24, 2021
 *      Author: KSP
 */
#include "stm32l4xx_hal.h"
#include "sps30.h"

I2C_HandleTypeDef hi2c1;

/********************************************************************************************
;	Function:		SPS30_startMeasurements
;	Description:	Start SPS30 Measurements
;	Inputs: 	 	Nothing
;	Returns:	 	Nothing
**********************************************************************************************/
void SPS30_startMeasurements(void){

	uint8_t I2C_COMMAND[5];
	I2C_COMMAND[0] = 0x00;
	I2C_COMMAND[1] = 0x10;
	I2C_COMMAND[2] = 0x03;
	I2C_COMMAND[3] = 0x00;
	I2C_COMMAND[4] = SPS30_MEASUREMENT_CHECKSUM;
	HAL_I2C_Master_Transmit( &hi2c1, SPS30_I2C_ADDRESS, I2C_COMMAND, sizeof( I2C_COMMAND ), HAL_MAX_DELAY );

}

/********************************************************************************************
;	Function:		SPS30_stopMeasurements
;	Description:	Stop SPS30 Measurements
;	Inputs: 	 	Nothing
;	Returns:	 	Nothing
**********************************************************************************************/
void SPS30_stopMeasurements(void){

	uint16_t I2C_COMMAND[1];
	I2C_COMMAND[0] = SPS30_CMD_STOP_MEASUREMENT;

	HAL_I2C_Master_Transmit( &hi2c1, SPS30_I2C_ADDRESS, ( uint8_t* ) &I2C_COMMAND, sizeof( I2C_COMMAND ), HAL_MAX_DELAY );

}

/********************************************************************************************
;	Function:		SPS30_sleep
;	Description:	Set SPS30 in Sleep Mode
;	Inputs: 	 	Nothing
;	Returns:	 	Nothing
**********************************************************************************************/
void SPS30_sleep(void){

	uint16_t I2C_COMMAND[1];
	I2C_COMMAND[0] = SPS30_CMD_SLEEP;

	HAL_I2C_Master_Transmit( &hi2c1, SPS30_I2C_ADDRESS, ( uint8_t* ) &I2C_COMMAND, sizeof( I2C_COMMAND ), HAL_MAX_DELAY );

}

/********************************************************************************************
;	Function:		SPS30_wakeUp
;	Description:	Awake SPS30 from Sleep Mode
;	Inputs: 	 	Nothing
;	Returns:	 	Nothing
**********************************************************************************************/
void SPS30_wakeUp(void){

	uint16_t I2C_COMMAND[1];
	I2C_COMMAND[0] = SPS30_CMD_WAKE_UP;

	HAL_I2C_Master_Transmit( &hi2c1, SPS30_I2C_ADDRESS, ( uint8_t* ) &I2C_COMMAND, sizeof( I2C_COMMAND ), HAL_MAX_DELAY );
	HAL_I2C_Master_Transmit( &hi2c1, SPS30_I2C_ADDRESS, ( uint8_t* ) &I2C_COMMAND, sizeof( I2C_COMMAND ), HAL_MAX_DELAY );

}

/********************************************************************************************
;	Function:		SPS30_writeByte
;	Description:	Send SPS30 Command
;	Inputs: 	 	Register, Value
;	Returns:	 	Nothing
**********************************************************************************************/
void SPS30_writeByte(uint16_t reg, uint16_t val){

	uint8_t I2C_COMMAND[2];
	I2C_COMMAND[0] = reg;
	I2C_COMMAND[1] = val;

	HAL_I2C_Master_Transmit( &hi2c1, SPS30_I2C_ADDRESS, ( uint8_t* ) &I2C_COMMAND, sizeof( I2C_COMMAND ), HAL_MAX_DELAY );


}

/********************************************************************************************
;	Function:		SPS30_readMeasurements
;	Description:	Read Measurement Parameters from SPS30
;	Inputs: 	 	Nothing
;	Returns:	 	Readings ( as struct)
**********************************************************************************************/
struct measurements SPS30_readMeasurements(){

	uint8_t rx_Buffer[30] 	= {0};

	uint8_t I2C_COMMAND[2];
	I2C_COMMAND[0] = 0x03;
	I2C_COMMAND[1] = 0x00;
	HAL_I2C_Master_Transmit( &hi2c1, SPS30_I2C_ADDRESS, I2C_COMMAND, sizeof( I2C_COMMAND ), HAL_MAX_DELAY );
	HAL_I2C_Master_Receive( &hi2c1, SPS30_I2C_ADDRESS, rx_Buffer, sizeof(rx_Buffer) , HAL_MAX_DELAY);


	//uint16_t sps30_1p0 = (rx_Buffer[0] << 16) | (rx_Buffer[1] << 8) | rx_Buffer[2];

	struct measurements SPS30 = { .particle1p0 		= ((rx_Buffer[0] << 16) | (rx_Buffer[1] << 8) | rx_Buffer[2]),
								  .particle2p5 		= ((rx_Buffer[3] << 16) | (rx_Buffer[4] << 8) | rx_Buffer[5]),
								  .particle4p0 		= ((rx_Buffer[6] << 16) | (rx_Buffer[7] << 8) | rx_Buffer[8]),
								  .particle10p 		= ((rx_Buffer[9] << 16) | (rx_Buffer[10] << 8) | rx_Buffer[11]),
								  .concantration0p5 = ((rx_Buffer[12] << 16) | (rx_Buffer[13] << 8) | rx_Buffer[14]),
								  .concantration1p0 = ((rx_Buffer[15] << 16) | (rx_Buffer[16] << 8) | rx_Buffer[17]),
								  .concantration2p5 = ((rx_Buffer[18] << 16) | (rx_Buffer[19] << 8) | rx_Buffer[20]),
								  .concantration4p0 = ((rx_Buffer[21] << 16) | (rx_Buffer[22] << 8) | rx_Buffer[23]),
								  .concantration10p = ((rx_Buffer[24] << 16) | (rx_Buffer[25] << 8) | rx_Buffer[26]),
								  .particleSize		= ((rx_Buffer[27] << 16) | (rx_Buffer[28] << 8) | rx_Buffer[29])
	};

	return SPS30;
}
