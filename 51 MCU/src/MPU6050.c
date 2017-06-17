#include <Var.h>

#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	MPU6050_SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取

unsigned char Ax_Offset = 0;
unsigned char Ay_Offset = 0;
unsigned char Az_Offset = 14;
unsigned char Wx_Offset = 0;
unsigned char Wy_Offset = 0;
unsigned char Wz_Offset = 0;
float xdata exInt=0,eyInt=0,ezInt=0;
float xdata q0=1,q1=0,q2=0,q3=0;

void InitMPU6050()						//初始化MPU6050
{
	Single_WriteI2C(MPU6050_SlaveAddress,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(MPU6050_SlaveAddress,SMPLRT_DIV, 0x07);
	Single_WriteI2C(MPU6050_SlaveAddress,CONFIG, 0x06);
	Single_WriteI2C(MPU6050_SlaveAddress,GYRO_CONFIG, 0x18);
	Single_WriteI2C(MPU6050_SlaveAddress,ACCEL_CONFIG, 0x18);

	Single_WriteI2C(MPU6050_SlaveAddress,0x6A, 0x44);
	Single_WriteI2C(MPU6050_SlaveAddress,0x23, 0xff);
}

float GetData(unsigned char REG_Address)			//合成数据
{
	char H,L;
	float dat;

	H=Single_ReadI2C(MPU6050_SlaveAddress,REG_Address);
	L=Single_ReadI2C(MPU6050_SlaveAddress,REG_Address+1);
	dat = H;
	dat = dat*256+L;

	return dat;//(H<<8)+L;   //合成数据
}

float GetData_A(unsigned char REG_Address)			//合成数据
{
	char H,L;
	float dat;

	H=Single_ReadI2C(MPU6050_SlaveAddress,REG_Address);
	L=Single_ReadI2C(MPU6050_SlaveAddress,REG_Address+1);
	dat = H;
	dat = dat*256+L;
	dat = dat/2048.0;

	return dat;//(H<<8)+L;   //合成数据
}

float GetData_W(unsigned char REG_Address)			//合成数据
{
	char H,L;
	float dat;

	H=Single_ReadI2C(MPU6050_SlaveAddress,REG_Address);
	L=Single_ReadI2C(MPU6050_SlaveAddress,REG_Address+1);
	dat = H;
	dat = dat*256+L;
	dat = dat/16.4;

	return dat;//(H<<8)+L;   //合成数据
}

float MPU6050_Temp()
{ 
	float Temperature;
//	char Temp_h,Temp_l;

//	Temp_h=Single_ReadI2C(MPU6050_SlaveAddress,TEMP_OUT_H); //读取温度
//	Temp_l=Single_ReadI2C(MPU6050_SlaveAddress,TEMP_OUT_L); //读取温度
//	Temperature = Temp_h;
//	Temperature = Temperature*256+Temp_l;     //合成温度
//	Temperature = 35+ ((double) (Temperature + 13200)) / 280; // 计算出温度
	Temperature=(GetData(TEMP_OUT_H)/340.0)+36.53;

	return	Temperature; 
}

void DisplayData(int value,unsigned char x,unsigned char y)   //在1602上显示10位数据
{					
	if(value<0)
	{
	 	value=abs(value*1.0);
		Lcd_display(x,y,String2[9]);
		Lcd_display(x,y+1,number[(int)value/1000]);				// 十位
		Lcd_display(x,y+2,number[(int)value/100%10]);			// 个位
		Lcd_display(x,y+3,String2[10]);
		Lcd_display(x,y+4,number[(int)value/10%10]);			// 小数点后一位
		Lcd_display(x,y+5,number[(int)value%10]);				// 小数点后两位
	}
	else
	{
		Lcd_display(x,y,number[(int)value/1000]);
		Lcd_display(x,y+1,number[(int)value/100%10]);
		Lcd_display(x,y+2,String2[10]);
		Lcd_display(x,y+3,number[(int)value/10%10]);
		Lcd_display(x,y+4,number[(int)value%10]);
		Lcd_display(x,y+5,' ');	
	}				
}

//void MPU6050(unsigned char select,unsigned char x,unsigned char y)
//{	
//   	switch(select)
//	{
//		case Ax:	DisplayData(GetData_A(ACCEL_XOUT_H)+Ax_Offset,x,y);	//显示X轴加速度
//					break;
//		case Ay:	DisplayData(GetData_A(ACCEL_YOUT_H)+Ay_Offset,x,y);	//显示Y轴加速度
//					break;
//		case Az:	DisplayData(GetData_A(ACCEL_ZOUT_H)+Az_Offset,x,y);	//显示Z轴加速度
//					break;
//		case Wx:	DisplayData(GetData_W(GYRO_XOUT_H)+Wx_Offset,x,y);	//显示X轴角速度
//					break;
//		case Wy:	DisplayData(GetData_W(GYRO_YOUT_H)+Wy_Offset,x,y);	//显示Y轴角速度
//					break;
//		case Wz:	DisplayData(GetData_W(GYRO_ZOUT_H)+Wz_Offset,x,y);	//显示Z轴角速度
//					break;
//		case Temp:	DisplayData(MPU6050_Temp(),x,y);
//					break;
//	}	
//}

void MPU6050()
{	
	unsigned char xdata Ax_dat,Ay_dat,Az_dat,Wx_dat,Wy_dat,Wz_dat,temp_dat;
	float xdata norm;
	float xdata vx, vy, vz;
	float xdata ex, ey, ez;
 
	double xdata Angle = 0.0;
	double xdata Angley = 0.0;
	float xdata gx,gy,gz,ax,ay,az;

//	for(i = 1;i<=10;i++)
//	{
		Ax_dat = GetData_A(ACCEL_XOUT_H)+Ax_Offset;
		Ay_dat = GetData_A(ACCEL_YOUT_H)+Ay_Offset;
		Az_dat = GetData_A(ACCEL_ZOUT_H)+Az_Offset;
		Wx_dat = GetData_W(GYRO_XOUT_H)+Wx_Offset;
		Wy_dat = GetData_W(GYRO_YOUT_H)+Wy_Offset;
		Wz_dat = GetData_W(GYRO_ZOUT_H)+Wz_Offset;
		temp_dat = MPU6050_Temp();

		gx = Wx_dat*0.0174533;
		gy = Wy_dat*0.0174533;
		gz = Wz_dat*0.0174533;
		ax = Ax_dat;
		ay = Ay_dat;
		az = Az_dat;

		norm = sqrt(ax*ax + ay*ay + az*az);      
  		ax = ax/norm;
  		ay = ay/norm;
  		az = az/norm;
           
  		vx = 2*(q1*q3 - q0*q2);												
  		vy = 2*(q0*q1 + q2*q3);
  		vz = q0*q0 - q1*q1 - q2*q2 + q3*q3 ;

  		ex = (ay*vz - az*vy) ;                           					
  		ey = (az*vx - ax*vz) ;
  		ez = (ax*vy - ay*vx) ;

  		exInt = exInt + ex * Ki;								 
  		eyInt = eyInt + ey * Ki;
  		ezInt = ezInt + ez * Ki;

  		gx = gx + Kp*ex + exInt;					   							
  		gy = gy + Kp*ey + eyInt;
  		gz = gz + Kp*ez + ezInt;				   							
					   
  		q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
  		q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
  		q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
  		q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

  		norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  		q0 = q0 / norm;
  		q1 = q1 / norm;
  		q2 = q2 / norm;
  		q3 = q3 / norm;

  		Angle=asin(2*(q0*q2-q1*q3 ))* 57.3; // 俯仰
  		Angley=atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // 横滚
//	}

  ////////////////////////////////////////////////////////
  		Lcd_display(1,0,number[((long)(Angle*100))/10000]);
		Lcd_display(1,1,number[((long)(Angle*100))/1000%10]);
		Lcd_display(1,2,number[((long)(Angle*100))/100%10]);
		Lcd_display(1,3,String2[10]);
		Lcd_display(1,4,number[((long)(Angle*100))/10%10]);
		Lcd_display(1,5,number[((long)(Angle*100))%10]);

		Lcd_display(2,0,number[((long)(Angley*100))/10000]);
		Lcd_display(2,1,number[((long)(Angley*100))/1000%10]);
		Lcd_display(2,2,number[((long)(Angley*100))/100%10]);
		Lcd_display(2,3,String2[10]);
		Lcd_display(2,4,number[((long)(Angley*100))/10%10]);
		Lcd_display(2,5,number[((long)(Angley*100))%10]);	
 ////////////////////////////////////////////////////////
}