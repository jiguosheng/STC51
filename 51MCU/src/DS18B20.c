#include <Var.h>

void init_DS18B20()
{
	DQ=1;
	delay_us(5,T0);
	DQ=0;
	delay_ms(1,T0);//delay(500);
	DQ=1;
 	delay_us(60,T0);
 	while(DQ==0);
 	delay_ms(1,T0);//delay(500);
}

void write_DS18B20(unsigned char cmd)
{
	unsigned char i;
  	for(i=1;i<=8;i++)
  	{
  		DQ=0;
  		delay_us(15,T0);
  		DQ=(bit)(cmd & 0x01);
  		cmd=_cror_(cmd,1);
  		delay_us(60,T0);
  		DQ=1;
  	}
}

unsigned char read_DS18B20()
{
	unsigned char i=0,cmd=0,jishu[9]={0},quan=1;

	for(i=1;i<=8;i++)
	{
		DQ=0;
		delay_us(15,T0);
		DQ=1;
		if(DQ==1)  
		{
		  	jishu[i]=1;
		}
		cmd=_cror_(cmd,1);
		delay_us(60,T0);
	}
	for(i=1;i<=8;i++)
  	{
		cmd=cmd+jishu[i]*quan;
		quan=quan*2;
  	} 

 	return cmd;
} 

void DS18B20work()
{
	init_DS18B20();
	write_DS18B20(0xcc);
	write_DS18B20(0x44);
	delay_ms(10,T0);
	init_DS18B20();
	write_DS18B20(0xcc);
	write_DS18B20(0xbe);
}

float dispaly_DS18B20()
{
  	unsigned char i,cmdl,templ,temph,cmdh ;
	float tem = 0.0;

  	DS18B20work();
  	cmdl=read_DS18B20();
  	cmdh=read_DS18B20();
  	for(i=0;i<=8;i++)
  	{
  		Lcd_display(1,i,String2[i]);
  		delay_us(70,T0);     //修改此处的延时时间，使得lcd1602完整显示温度值。注：有关DS18B20的程序无错误，主要是lcd602不能正确显示而已。
  	}
  	delay_us(80,T0);     //修改此处的延时时间，使得lcd1602完整显示温度值。注：有关DS18B20的程序无错误，主要是lcd602不能正确显示而已。
  	if(cmdh&0x80)
  	{
  		cmdh=~cmdh;
  		cmdl=~cmdl;
  		cmdl=cmdl+1;
  		Lcd_display(1,i,String2[9]);
  		_nop_();
  		_nop_();
  	}
  	temph=cmdh*16+cmdl/16;	
  	templ=(cmdl%16)*10/16;
	tem = temph+templ*0.1;
  	Lcd_display(1,9,number[temph/100]);
  	delay_us(30,T0);     //修改此处的延时时间，使得lcd1602完整显示温度值。注：有关DS18B20的程序无错误，主要是lcd602不能正确显示而已。
  	Lcd_display(1,10,number[(temph%100)/10]);
  	delay_us(30,T0);     
  	Lcd_display(1,11,number[temph%10]);
  	delay_us(30,T0);     
  	Lcd_display(1,12,String2[10]);
  	delay_us(30,T0);    
  	Lcd_display(1,13,number[templ]);
  	delay_us(30,T0);
  	Lcd_display(1,14,0xdf);   
 	delay_us(30,T0);    
  	Lcd_display(1,15,String2[11]);

	return tem;
}