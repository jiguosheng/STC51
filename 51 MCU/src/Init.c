#include <Var.h>

void MCU_Init()
{
	UartInit();
	WDT_CONTR = 0x38; 	//���Ź���ʱʱ��=12*Ԥ��Ƶ*32768/����Ƶ��
						//��ʱ71.1mS
}