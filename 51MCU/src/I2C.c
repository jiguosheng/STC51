#include <Var.h>

void I2C_Start()				//I2C起始信号
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    delay_us(5,T0);                 //延时
    SDA = 0;                    //产生下降沿
    delay_us(5,T0);                 //延时
    SCL = 0;                    //拉低时钟线
}

void I2C_Stop()					//I2C停止信号
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    delay_us(5,T0);                 //延时
    SDA = 1;                    //产生上升沿
    delay_us(5,T0);                 //延时
}


void I2C_SendACK(bit ack)		//I2C发送应答信号 入口参数:ack (0:ACK 1:NAK)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    delay_us(5,T0);                 //延时
    SCL = 0;                    //拉低时钟线
    delay_us(5,T0);                 //延时
}

bit I2C_RecvACK()				//I2C接收应答信号
{
	SDA = 1;
    SCL = 1;                    //拉高时钟线
    delay_us(5,T0);                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    delay_us(5,T0);                 //延时

    return CY;
}

void I2C_SendByte(unsigned char dat)	//向I2C总线发送一个字节数据
{
    unsigned char i;
    for (i=0; i<8; i++)         //8位计数器
    {
        if((dat <<i)&0x80)              
		{
        	SDA = 1;               //送数据口
		}
		else
		{
			SDA = 0;
		}
        SCL = 1;                //拉高时钟线
        delay_us(5,T0);             //延时
        SCL = 0;                //拉低时钟线
        delay_us(5,T0);             //延时
    }
    I2C_RecvACK();
}

unsigned char I2C_RecvByte()			//从I2C总线接收一个字节数据
{
    unsigned char i;
    unsigned char dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
		SCL = 0;
		delay_us(5,T0);             //延时
        SCL = 1;                //拉高时钟线
        delay_us(5,T0);             //延时
		dat <<= 1;
        dat |= SDA;             //读数据               
    }
	SCL = 0;

    return dat;
}

void Single_WriteI2C(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)	   //向I2C设备写入一个字节数据
{
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
}

unsigned char Single_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)	   //从I2C设备读取一个字节数据
{
	unsigned char REG_data;

	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress);    //发送设备地址+写信号
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始	
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK(1);                //接收应答信号
	I2C_Stop();                    //停止信号

	return REG_data;
}

//	Single_WriteI2C(0xae,4,5);
//	delay_ms(50,T0);
//	displayshumaguan(3,Single_ReadI2C(0xae,4));