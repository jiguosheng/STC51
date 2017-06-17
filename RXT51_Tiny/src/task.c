#include <variable.h>

void UartInit()		//9600bps@12.000MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TI=1;
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
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
//		os_wait(K_IVL,10,0);	  //�Ժ����䲻ִ��
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
