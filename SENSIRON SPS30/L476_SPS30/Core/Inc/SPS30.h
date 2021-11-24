/**********************************************************************
 *	SPS30.h
 *
 *  Created on: Nov 24, 2021
 *  Author: Ş. Emre KASAP
 *********************************************************************/

#ifndef _SPS30_H_
#define _SPS30_H_

#define SPS30_I2C_ADDRESS ( 0x69 << 1 )

#define SPS30_CMD_START_MEASUREMENT 0x00
#define SPS30_CMD_STOP_MEASUREMENT 0x0401
#define SPS30_CMD_READ_MEASUREMENT 0x03

#define SPS30_CMD_DEVICE_INFO 0xD0
#define SPS30_CMD_DEVICE_STATUS 0xD2
#define SPS30_START_MANUAL_FAN_CLEANING 0x0756

#define SPS30_CMD_RESET 0xD3
#define SPS30_CMD_SLEEP 0x0110
#define SPS30_CMD_WAKE_UP 0x0311

#define SPS30_ENABLE_MEASUREMENT 0x01
#define SPS30_MEASUREMENT_INTEGER 0x03
#define SPS30_MEASUREMENT_IEEE754 0x05

#define SPS30_MEASUREMENT_CHECKSUM 0xAC


struct measurements {

	uint32_t particle1p0;
	uint32_t particle2p5;
	uint32_t particle4p0;
	uint32_t particle10p;
	uint32_t concantration0p5;
	uint32_t concantration1p0;
	uint32_t concantration2p5;
	uint32_t concantration4p0;
	uint32_t concantration10p;
	uint32_t particleSize;


};

/* Function Prototypes */
void SPS30_startMeasurements(void);
void SPS30_stopMeasurements(void);
void SPS30_sleep(void);
void SPS30_wakeUp(void);
struct measurements SPS30_readMeasurements();
void SPS30_writeByte(uint16_t reg, uint16_t val);


#endif /* INC_SPS30_H_ */
