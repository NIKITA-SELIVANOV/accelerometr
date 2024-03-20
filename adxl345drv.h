/*
 * adxl345drv.h
 *
 *  Created on: Nov 29, 2023
 *      Author: a.zavyalov
 */

#ifndef SRC_ADXL345DRV_H_
#define SRC_ADXL345DRV_H_

#include <main.h>

#define ADXL345_REG_DEVID                  0x00 //Device ID
#define ADXL345_REG_THRESH_TAP             0x1D //Tap threshold
#define ADXL345_REG_OFSX                   0x1E //X-axis offset
#define ADXL345_REG_OFSY                   0x1F //Y-axis offset
#define ADXL345_REG_OFSZ                   0x20 //Z-axis offset
#define ADXL345_REG_DUR                    0x21 //Tap duration
#define ADXL345_REG_LATENT                 0x22 //Tap latency
#define ADXL345_REG_WINDOW                 0x23 //Tap window
#define ADXL345_REG_THRESH_ACT             0x24 //Activity threshold
#define ADXL345_REG_THRESH_INACT           0x25 //Inactivity threshold
#define ADXL345_REG_TIME_INACT             0x26 //Inactivity time
#define ADXL345_REG_ACT_INACT_CTL          0x27 //Axis enable control for activity and inactivity detection
#define ADXL345_REG_THRESH_FF              0x28 //Free-fall threshold
#define ADXL345_REG_TIME_FF                0x29 //Free-fall time
#define ADXL345_REG_TAP_AXES               0x2A //Axis control for single tap/double tap
#define ADXL345_REG_ACT_TAP_STATUS         0x2B //Source of single tap/double tap
#define ADXL345_REG_BW_RATE                0x2C //Data rate and power mode control
#define ADXL345_REG_POWER_CTL              0x2D //Power-saving features control
#define ADXL345_REG_INT_ENABLE             0x2E //Interrupt enable control
#define ADXL345_REG_INT_MAP                0x2F //Interrupt mapping control
#define ADXL345_REG_INT_SOURCE             0x30 //Source of interrupts
#define ADXL345_REG_DATA_FORMAT            0x31 //Data format control
#define ADXL345_REG_DATAX0                 0x32 //X-Axis Data 0
#define ADXL345_REG_DATAX1                 0x33 //X-Axis Data 1
#define ADXL345_REG_DATAY0                 0x34 //Y-Axis Data 0
#define ADXL345_REG_DATAY1                 0x35 //Y-Axis Data 1
#define ADXL345_REG_DATAZ0                 0x36 //Z-Axis Data 0
#define ADXL345_REG_DATAZ1                 0x37 //Z-Axis Data 1
#define ADXL345_REG_FIFO_CTL               0x38 //FIFO control
#define ADXL345_REG_FIFO_STATUS            0x39 //FIFO status

typedef enum {ADXL_OK,ADXL_ERR} adxlStatus;

extern I2C_HandleTypeDef hi2c1;

typedef struct {
   int16_t x;
   int16_t y;
} ADXL345_data;

class TADXL345 {
private:
	uint8_t address;
	uint8_t chipid;
	void writereg(uint8_t reg, uint8_t value);
	uint8_t readreg(uint8_t reg);
	uint8_t *buffer;
	bool busy;
public:
	TADXL345();
	uint8_t GetDeviceAddress();
	uint8_t GetChipID();
	adxlStatus Init();
	void StartReadXY_DMA();
	ADXL345_data Read_values_cplt();
	void SetBuffer(uint8_t *buf);
	bool IsBusy();
	virtual ~TADXL345();
};

#endif /* SRC_ADXL345DRV_H_ */
