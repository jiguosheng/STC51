#include <Var.h>

void DS1302_Write_Adress(unsigned char adr)
{
	unsigned char i,j;

 	CE = 0;
	SCLK = 0;
	IO = 0;
	CE = 1;	
	delay_us(3,T0);
	for(i = 1,j = 0x01;i <= 8;i++)
	{
		SCLK = 0;
//		delay_us(3,T0);
	 	if(adr&j)
		{
		 	IO = 1;
		}
		else
		{
		 	IO = 0;
		}
		SCLK = 1;
		j = j*2;
//		delay_us(3,T0);
	}
}

unsigned char DS1302_Read_Data()
{
	unsigned char i = 0;
	unsigned char j = 0x01;
	unsigned char dat = 0x00;

	for(i = 1;i <= 8;i++)
	{
 		SCLK = 0;
//		delay_us(3,T0);
		if(IO)
		{
			dat = dat|j;			
		}
		j = j*2;
//		if(i < 8)
		{
			SCLK = 1;
//			delay_us(3,T0);
		}
	}
	CE = 0;

	return dat;
}

void DS1302_Write_Command(unsigned char com)
{
	unsigned char i,j;

	for(i = 1,j = 0x01;i <= 8;i++)
	{
		SCLK = 0;
//		delay_us(3,T0);
	 	if(com&j)
		{
		 	IO = 1;
		}
		else
		{
		 	IO = 0;
		}
		SCLK = 1;
		j = j*2;
//		delay_us(3,T0);
	}
	SCLK = 0;
	CE = 0;	 	
}

void DS1302_Init(	unsigned char year,
					unsigned char month,
					unsigned char ndate,
					unsigned char day,
					unsigned char hour,
					unsigned char mintues,
					unsigned char second
				)
{
	DS1302_Write_Adress(0x8e);
	DS1302_Write_Command(0x00);
	DS1302_Write_Adress(W_Year);
	DS1302_Write_Command(year);
	DS1302_Write_Adress(W_Mon);
	DS1302_Write_Command(month);
	DS1302_Write_Adress(W_Date);
	DS1302_Write_Command(ndate);
	DS1302_Write_Adress(W_Day);
	DS1302_Write_Command(day);
	DS1302_Write_Adress(W_Hour);
	DS1302_Write_Command(hour);
	DS1302_Write_Adress(W_Min);
	DS1302_Write_Command(mintues);
	DS1302_Write_Adress(W_Sec);
	DS1302_Write_Command(second);
	DS1302_Write_Adress(0x8e);
	DS1302_Write_Command(0x80);	 	
}

void DS1302(unsigned char X,unsigned char Y,unsigned char adr)
{
	unsigned char dat,dat1,dat2;

	DS1302_Write_Adress(adr);
	dat = DS1302_Read_Data();
	dat1 = (dat&0xf0)>>4;
	dat2 = dat&0x0f;

	Lcd_display(X,Y,number[dat1]);
	Lcd_display(X,Y+1,number[dat2]);		
}

//		DS1302(1,0,R_Year);
//		DS1302(1,3,R_Mon);
//	    DS1302(1,6,R_Date);
//		DS1302(1,9,R_Day);
//		DS1302(1,12,R_Hour);
//		DS1302(2,0,R_Min);
//		DS1302(2,3,R_Sec);