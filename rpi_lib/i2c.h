/*
*
*/

#ifndef __I2C_H__
#define __I2C_H__

#define S_CLKT	((volatile unsigned int)0x01 << 9)
#define S_ERR	((volatile unsigned int)0x01 << 8)
#define S_RXD	((volatile unsigned int)0x01 << 5)
#define S_DONE	((volatile unsigned int)0x01 << 1)
#define S_TA	((volatile unsigned int)0x01 << 0)

#define C_I2CEN	((volatile unsigned int)0x01 << 15)
#define C_ST	((volatile unsigned int)0x01 << 7)
#define C_CLEAR_ALL	((volatile unsigned int)0x03 << 4)
#define C_READ	((volatile unsigned int)0x01 << 0)

#define X_AXIS 0
#define Y_AXIS 1

extern void i2c_init();
extern void i2c_write();
extern void i2c_read(volatile int* value, char dir);

#endif
