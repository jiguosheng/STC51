#include <Var.h>

void MCU_Init()
{
	UartInit();
	WDT_CONTR = 0x38; 	//看门狗定时时间=12*预分频*32768/晶振频率
						//定时71.1mS
}