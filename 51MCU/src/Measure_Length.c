#include <Var.h>

float Measure_Length()
{
 	double len = 0.0;
	double ms = 0.0;
	unsigned int tim = 0;	
	
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器1模式
	TMOD |= 0x10;		//设置定时器1模式
	TL1 = 0;
	TH1 = 0;
	TF1 = 0;		//清除TF0标志
	ET1 = 0;
	Trig = 0;
	delay_us(10,T0);
	Trig = 1;
	delay_us(10,T0);
	Trig = 0;
	while(!Echo);
	TR1 = 1;
	while(Echo);
	TR1 = 0;
	tim = TH1;
	tim = tim*256+TL1;
//	if(TF1 == 1)
//	{
//	 	TF1 = 0;
//		tim = tim+65535;
//	}
	ms = tim*12/11.0592*0.001;
	len = sqrt(1.4*287*(273.15+dispaly_DS18B20()))*ms*0.001/2.0+0.01;

	Lcd_display(2,0,number[(unsigned int)len]);
	Lcd_display(2,1,String2[10]);
	Lcd_display(2,2,number[((unsigned int)(len*10))%10]);
	Lcd_display(2,3,number[((unsigned int)(len*100))%10]);
    Lcd_display(2,4,'m');

	return len;
}