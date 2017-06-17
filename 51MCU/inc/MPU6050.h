#ifndef MPU6050_H_
#define MPU6050_H_

	void InitMPU6050();
	float GetData(unsigned char REG_Address);
	float GetData_A(unsigned char REG_Address);
	float GetData_W(unsigned char REG_Address);
	void DisplayData(int value,unsigned char x,unsigned char y);
	float MPU6050_Temp();
//	void MPU6050(unsigned char select,unsigned char x,unsigned char y);
	void MPU6050();

	#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
	#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
	#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
	#define	ACCEL_XOUT_H	0x3B
	#define	ACCEL_XOUT_L	0x3C
	#define	ACCEL_YOUT_H	0x3D
	#define	ACCEL_YOUT_L	0x3E
	#define	ACCEL_ZOUT_H	0x3F
	#define	ACCEL_ZOUT_L	0x40
	#define	TEMP_OUT_H		0x41
	#define	TEMP_OUT_L		0x42
	#define	GYRO_XOUT_H		0x43
	#define	GYRO_XOUT_L		0x44	
	#define	GYRO_YOUT_H		0x45
	#define	GYRO_YOUT_L		0x46
	#define	GYRO_ZOUT_H		0x47
	#define	GYRO_ZOUT_L		0x48
	#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
	
	#define Ax 1
	#define Ay 2
	#define Az 3
	#define Wx 4
	#define Wy 5
	#define Wz 6
	#define Temp 7

	#define pi 3.14159265f 
	#define Kp 0.8f                        
	#define Ki 0.001f                                                   
	#define halfT 0.004f 

#endif