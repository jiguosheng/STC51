#include <Var.h>

void main()
{  
	MCU_Init();
		
	while(1)
	{		
		MMA7660(M_GZ);

		WDT_CONTR |= 0x10; 			
	}
}

//void INT0() interrupt 0
//{
//
//} 

//void T0_ISR() interrupt 1
//{
// 	/*TL0 = (65535-Fosc/12*ms*1000)%256;//)%256;		//���ö�ʱ��ֵ
//	TH0 = (65535-Fosc/12*ms*1000)/256;//)/256;		//���ö�ʱ��ֵ*/
//
//}

//void INT1() interrupt 2
//{
//
//}

//void T1_ISR() interrupt 3
//{
//   	TL1 = (65535-Fosc/12*4*1000)%256;		//���ö�ʱ��ֵ
//	TH1 = (65535-Fosc/12*4*1000)/256;		//���ö�ʱ��ֵ
//
//}

void Uart1() interrupt 4
{
	static unsigned char count = 0;

	if(RI)
	{
		RI = 0;
		if(SBUF == 0x7F)
		{
			count++;
			if(count == 5)
			{
				count = 0;
		 		IAP_CONTR = 0x60;  //��Ƭ�������������������ֺ󣬵�Ƭ����λ����������Ҫ������λ�ˡ�
			}
		}
		else
		{
		 	count = 0;

		}
	}
}

//void LVD() interrupt 6
//{
// 	PCON &= 0xdf;	//���LVD��־λ
//}

//void PCA_Interrupt() interrupt 7
//{
//	/*CCF0 = 0;
//	CCF1 = 0;*/
//
//} 

//void PCA_isr() interrupt 7 						//�����������
//{
//    /*CCF0 = 0;                       //Clear interrupt flag
//    CCAP0L = (unsigned char)(Fosc*1000000/(4*f)+0.5);
//	CCAP1L = (unsigned char)(Fosc*1000000/(4*f)+0.5); */
//}

//void Uart2() interrupt 8
//{
// 	if (S2CON & S2RI)
//    {
//        S2CON &= ~S2RI;     //Clear receive interrupt flag
//         = S2BUF;         //P0 show UART data
//    }	
//}

//void SPI() interrupt 9
//{
// 	/*SPSTAT = SPIF | WCOL;       //clear SPI status			 //��Ϊ����
//    if (MSSEL)
//    {
//        SPCTL = SPEN;           //reset as slave
//        MSSEL = 0;
//        SPISS = 1;              //push high slave SS
//        SendUart(SPDAT);        //return received SPI data
//    }
//    else
//    {                           //for salve (receive SPI data from master and
//        SPDAT = SPDAT;	        //           send previous SPI data to master)
//    } */
//	/*
//	SPSTAT = SPIF | WCOL;       //clear SPI status				//��������
//	#ifdef MASTER
//    	SPISS = 1;                  //push high slave SS
//    	SendUart(SPDAT);            //return received SPI data
//	#else							//for salve (receive SPI data from master and
//    	SPDAT = SPDAT;	            //           send previous SPI data to master)
//	#endif
//	*/
//}