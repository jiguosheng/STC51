#include <Var.h>

#define	HMC5883_SlaveAddress   0x3C	  //����������IIC�����еĴӵ�ַ

unsigned char BUF[8];                         //�������ݻ�����      	

void Multiple_read_HMC5883()			  //��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
{   
	unsigned char i;
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(HMC5883_SlaveAddress);           //�����豸��ַ+д�ź�
    I2C_SendByte(0x03);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(HMC5883_SlaveAddress+1);         //�����豸��ַ+���ź�
	for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = I2C_RecvByte();          //BUF[0]�洢����
        if (i == 5)
		{
           I2C_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          I2C_SendACK(0);                //��ӦACK
		}
	}
    I2C_Stop();                          //ֹͣ�ź�
    delay_ms(5,2);
}


void Init_HMC5883()						 //��ʼ��HMC5883��������Ҫ��ο�pdf�����޸�
{
	Single_WriteI2C(HMC5883_SlaveAddress,0x02,0x00);  
}
								
int HMC5883()
{ 
	int x,y,z,angle;
			
   	Init_HMC5883();
	Multiple_read_HMC5883();      //�����������ݣ��洢��BUF��
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
