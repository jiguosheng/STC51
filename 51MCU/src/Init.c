#include <Var.h>

void MCU_Init()
{
	UartInit();
	Init_MMA7660();
	Lcd_Init();
	WDT_CONTR = 0x3c; 	//���Ź���ʱʱ��=12*Ԥ��Ƶ*32768/����Ƶ��
						//��ʱ1.1377S
}