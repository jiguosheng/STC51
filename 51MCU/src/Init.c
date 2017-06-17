#include <Var.h>

void MCU_Init()
{
	UartInit();
	Init_MMA7660();
	Lcd_Init();
	WDT_CONTR = 0x3c; 	//看门狗定时时间=12*预分频*32768/晶振频率
						//定时1.1377S
}