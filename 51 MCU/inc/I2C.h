#ifndef I2C_H_
#define I2C_H_

	void I2C_Start();
	void I2C_Stop();
	void I2C_SendACK(bit ack);
	bit I2C_RecvACK();
	void I2C_SendByte(unsigned char dat);
	unsigned char I2C_RecvByte();
	void Single_WriteI2C(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
	unsigned char Single_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address);

#endif