#include <Var.h>

#define	HMC5883_SlaveAddress   0x3C	  //定义器件在IIC总线中的从地址

unsigned char BUF[8];                         //接收数据缓存区      	

void Multiple_read_HMC5883()			  //连续读出HMC5883内部角度数据，地址范围0x3~0x5
{   
	unsigned char i;
    I2C_Start();                          //起始信号
    I2C_SendByte(HMC5883_SlaveAddress);           //发送设备地址+写信号
    I2C_SendByte(0x03);                   //发送存储单元地址，从0x3开始	
    I2C_Start();                          //起始信号
    I2C_SendByte(HMC5883_SlaveAddress+1);         //发送设备地址+读信号
	for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = I2C_RecvByte();          //BUF[0]存储数据
        if (i == 5)
		{
           I2C_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          I2C_SendACK(0);                //回应ACK
		}
	}
    I2C_Stop();                          //停止信号
    delay_ms(5,2);
}


void Init_HMC5883()						 //初始化HMC5883，根据需要请参考pdf进行修改
{
	Single_WriteI2C(HMC5883_SlaveAddress,0x02,0x00);  
}
								
int HMC5883()
{ 
	int x,y,z,angle;
			
   	Init_HMC5883();
	Multiple_read_HMC5883();      //连续读出数据，存储在BUF中
    x=BUF[0] << 8 | BUF[1]; //Combine MSB and LSB of X Data output register
    z=BUF[2] << 8 | BUF[3]; //Combine MSB and LSB of Z Data output register
    y=BUF[4] << 8 | BUF[5]; //Combine MSB and LSB of Y Data output register

    angle=(atan2((double)y,(double)x) * (180 / 3.14159265) + 180)*10; // angle in degrees
	Lcd_display(1,0,number[angle%10000/1000]);  
    Lcd_display(1,1,number[angle%1000/100]); 
    Lcd_display(1,2,number[angle%100/10]); 
    Lcd_display(1,3,String2[10]); 
	Lcd_display(1,4,number[angle%10]);   
	
	return angle;               
} 
