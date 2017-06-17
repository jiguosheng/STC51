#include <Var.h>

void I2C_Start()				//I2C��ʼ�ź�
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    delay_us(5,T0);                 //��ʱ
    SDA = 0;                    //�����½���
    delay_us(5,T0);                 //��ʱ
    SCL = 0;                    //����ʱ����
}

void I2C_Stop()					//I2Cֹͣ�ź�
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    delay_us(5,T0);                 //��ʱ
    SDA = 1;                    //����������
    delay_us(5,T0);                 //��ʱ
}


void I2C_SendACK(bit ack)		//I2C����Ӧ���ź� ��ڲ���:ack (0:ACK 1:NAK)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    delay_us(5,T0);                 //��ʱ
    SCL = 0;                    //����ʱ����
    delay_us(5,T0);                 //��ʱ
}

bit I2C_RecvACK()				//I2C����Ӧ���ź�
{
	SDA = 1;
    SCL = 1;                    //����ʱ����
    delay_us(5,T0);                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    delay_us(5,T0);                 //��ʱ

    return CY;
}

void I2C_SendByte(unsigned char dat)	//��I2C���߷���һ���ֽ�����
{
    unsigned char i;
    for (i=0; i<8; i++)         //8λ������
    {
        if((dat <<i)&0x80)              
		{
        	SDA = 1;               //�����ݿ�
		}
		else
		{
			SDA = 0;
		}
        SCL = 1;                //����ʱ����
        delay_us(5,T0);             //��ʱ
        SCL = 0;                //����ʱ����
        delay_us(5,T0);             //��ʱ
    }
    I2C_RecvACK();
}

unsigned char I2C_RecvByte()			//��I2C���߽���һ���ֽ�����
{
    unsigned char i;
    unsigned char dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
		SCL = 0;
		delay_us(5,T0);             //��ʱ
        SCL = 1;                //����ʱ����
        delay_us(5,T0);             //��ʱ
		dat <<= 1;
        dat |= SDA;             //������               
    }
	SCL = 0;

    return dat;
}

void Single_WriteI2C(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)	   //��I2C�豸д��һ���ֽ�����
{
    I2C_Start();                  //��ʼ�ź�
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
    I2C_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                   //����ֹͣ�ź�
}

unsigned char Single_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)	   //��I2C�豸��ȡһ���ֽ�����
{
	unsigned char REG_data;

	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress+1);  //�����豸��ַ+���ź�
	REG_data=I2C_RecvByte();       //�����Ĵ�������
	I2C_SendACK(1);                //����Ӧ���ź�
	I2C_Stop();                    //ֹͣ�ź�

	return REG_data;
}

//	Single_WriteI2C(0xae,4,5);
//	delay_ms(50,T0);
//	displayshumaguan(3,Single_ReadI2C(0xae,4));