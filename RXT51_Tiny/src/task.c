#include <variable.h>

void UartInit()		//9600bps@12.000MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TI=1;
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void Init(void) _task_ 0
{
 	os_create_task(1);
	os_create_task(2);
	os_create_task(3);
	UartInit();
	A1 = 0;
	A2 = 0;
	A3 = 0;
	os_delete_task(0);
}

void T11(void) _task_ 1
{
	while(1)
	{
	 	os_wait(K_IVL,10,0);
		A1 = ~A1;
	}
}

void T12(void) _task_ 2
{
 	static unsigned char i = 1;
	while(1)
	{	
//		os_wait(K_IVL,10,0);
		i++;
		if(i>10)
		{
		 	os_send_signal(3);
			i = 1;
		}
//		os_wait(K_IVL,10,0);	  //以后的语句不执行
		os_wait(K_TMO,10,0);
	 	A2 = ~A2;	 	
	}
}

void T13(void) _task_ 3
{
	while(1)
	{
 		os_wait(K_SIG,0,0);
		A3 = ~A3;
		printf ("\nHello World\n");
	}
}
