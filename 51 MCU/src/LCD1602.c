#include <Var.h>

unsigned char code number[] = {"0123456789"};
unsigned char code String2[] = {"tempture:-.C"};
unsigned char code String1[] = {"Voltage: .  V"};

bit lcd_bz()
{
	bit result;
	RS = 0;
	RW = 1;
	E = 1;	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	result = (bit)(DATA & 0x80);
	E = 0;
	return result;
}
 
void lcd_wcmd(unsigned char cmd)
{
	while(lcd_bz());//ÅÐ¶ÏLCDÊÇ·ñÃ¦Âµ
	RS = 0;
	RW = 0;
	E = 0;
	DATA = cmd;
	delay_us(5,T0);
	E = 1;
	delay_us(5,T0);
	E = 0;
}
 
void lcd_wdat(unsigned char dat)
{
	while(lcd_bz());//ÅÐ¶ÏLCDÊÇ·ñÃ¦Âµ
	RS = 1;
	RW = 0;
	E = 0;
	DATA = dat;
	delay_us(5,T0);
	E = 1;
	delay_us(5,T0);
	E = 0;
}

void Lcd_Init()
{
	lcd_wcmd(BUS_8|REVEAL_2|M57);
	delay_ms(5,T0);
	lcd_wcmd(REVEAL_ON|CURSOR_OFF);
	delay_ms(5,T0);
	lcd_wcmd(CURSOR_RIGHT);
	delay_ms(5,T0);
	lcd_wcmd(CLEAR);
	delay_ms(5,T0);
}

void Lcd_display(unsigned char X,unsigned char Y,unsigned char dat)
{
 	switch(X)
	{
	 	case 1: lcd_wcmd(0x80+Y);
				break;
		case 2:	lcd_wcmd(0xc0+Y);
				break;
	}
	lcd_wdat(dat);
}