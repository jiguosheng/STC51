#include <Var.h>

void T0_Init(unsigned char ms)
{
 	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = (65535-Fosc/12*ms*1000)%256;//)%256;		//���ö�ʱ��ֵ
	TH0 = (65535-Fosc/12*ms*1000)/256;//)/256;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
} 

void T1_Init(unsigned char ms)
{
 	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = (65535-Fosc/12*ms*1000)%256;//)%256;		//���ö�ʱ��ֵ
	TH1 = (65535-Fosc/12*ms*1000)/256;//)/256;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	ET1 = 1;
	EA = 1;
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}

void PCA0_Init(unsigned char ms)					//CL��CH��0ͨ��ʱ�Ӽ�������CH��CL�ﵽCCAP0L��CCAP0Hʱ�����ж�
{
 	CCON = 0;                       //��ʼ��PCA
                                    //PCA��ʱ��ֹͣ����
                                    //���CF��־λ
                                    //��������жϱ�־
    CL = 0;                         //��λPCA������ʱ��
    CH = 0;
    CMOD = 0x00;                    //PCAʱ��ԴΪFosc/12
                                    //ʧЧPCA��ʱ������ж�
    CCAP0L = (Fosc/12*ms*1000)%256;
	CCAP0H = (Fosc/12*ms*1000)/256;           
    CCAPM0 = 0x49;                  //PCA��ʱ��������16-bit��ʱ��ģʽ��ʹ��PCA�ж�
    CR = 1;                         //PCA��ʱ����ʼ����
    EA = 1;
}

void PCA1_Init(unsigned char ms)					//CL��CH��0ͨ��ʱ�Ӽ�������CH��CL�ﵽCCAP0L��CCAP0Hʱ�����ж�
{
 	CCON = 0;                       //��ʼ��PCA
                                    //PCA��ʱ��ֹͣ����
                                    //���CF��־λ
                                    //��������жϱ�־
    CL = 0;                         //��λPCA������ʱ��
    CH = 0;
    CMOD = 0x00;                    //PCAʱ��ԴΪFosc/12
                                    //ʧЧPCA��ʱ������ж�
    CCAP1L = (Fosc/12*ms*1000)%256;
	CCAP1H = (Fosc/12*ms*1000)/256;           
    CCAPM1 = 0x49;                  //PCA��ʱ��������16-bit��ʱ��ģʽ��ʹ��PCA�ж�
    CR = 1;                         //PCA��ʱ����ʼ����
    EA = 1;
}

void delay_ms(unsigned char ms,unsigned char flag)
{
	switch(flag)
	{
		case 1:	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
				TMOD &= 0xF0;		//���ö�ʱ��0ģʽ
				TMOD |= 0x01;		//���ö�ʱ��0ģʽ
				TL0 = (65535-Fosc/12*ms*1000)%256;//)%256;		//���ö�ʱ��ֵ
				TH0 = (65535-Fosc/12*ms*1000)/256;//)/256;		//���ö�ʱ��ֵ
				TF0 = 0;		//���TF0��־
				ET0 = 0;
				TR0 = 1;		//��ʱ��0��ʼ��ʱ
				while(!TF0);
				TR0 = 0;
				TF0 = 0;
				break;
		case 2:	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
				TMOD &= 0x0F;		//���ö�ʱ��1ģʽ
				TMOD |= 0x10;		//���ö�ʱ��1ģʽ
				TL1 = (65535-Fosc/12*ms*1000)%256;//)%256;		//���ö�ʱ��ֵ
				TH1 = (65535-Fosc/12*ms*1000)/256;//)/256;		//���ö�ʱ��ֵ
				TF1 = 0;		//���TF0��־
				ET1 = 0;
				TR1 = 1;		//��ʱ��0��ʼ��ʱ
				while(!TF1);
				TR1 = 0;
				TF1 = 0;
				break;
		case 3:	CCON = 0;                       //��ʼ��PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCAʱ��ԴΪFosc/12
    			CCAP0L = (Fosc/12*ms*1000)%256;
				CCAP0H = (Fosc/12*ms*1000)/256;           
    			CCAPM0 = 0x48;                  //PCA��ʱ��������16-bit��ʱ��ģʽ��ʹ��PCA�ж�
    			CR = 1; 						 //PCA��ʱ����ʼ����
			    while(!CCF0);
				CR = 0;
				CCF0 = 0;                   
				break;
		case 4:	CCON = 0;                       //��ʼ��PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCAʱ��ԴΪFosc/12
    			CCAP1L = (Fosc/12*ms*1000)%256;
				CCAP1H = (Fosc/12*ms*1000)/256;           
    			CCAPM1 = 0x48;                  //PCA��ʱ��������16-bit��ʱ��ģʽ��ʹ��PCA�ж�
    			CR = 1;                         //PCA��ʱ����ʼ����
				while(!CCF1);
				CR = 0;
				CCF1=0;
				break;
	}	
}

void delay_us(unsigned char us,unsigned char flag)
{
	switch(flag)
	{
		case 1:	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
				TMOD &= 0xF0;		//���ö�ʱ��0ģʽ
				TMOD |= 0x02;		//���ö�ʱ��0ģʽ
				TL0 = 255-Fosc/12*us;		//���ö�ʱ��ֵ
				TH0 = 255-Fosc/12*us;		//���ö�ʱ��ֵ
				TF0 = 0;		//���TF0��־
				ET0 = 0;
				TR0 = 1;		//��ʱ��0��ʼ��ʱ
				while(!TF0);
				TR0 = 0;
				TF0 = 0;
				break;
		case 2:	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
				TMOD &= 0x0F;		//���ö�ʱ��1ģʽ
				TMOD |= 0x20;		//���ö�ʱ��1ģʽ
				TL1 = 256-Fosc/12*us;		//���ö�ʱ��ֵ
				TH1 = 256-Fosc/12*us;		//���ö�ʱ��ֵ
				TF1 = 0;		//���TF0��־
				ET1 = 0;
				TR1 = 1;		//��ʱ��0��ʼ��ʱ
				while(!TF1);
				TR1 = 0;
				TF1 = 0;
				break;
		case 3:	CCON = 0;                       //��ʼ��PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCAʱ��ԴΪFosc/12
    			CCAP0L = (Fosc/12*us)%256;
				CCAP0H = (Fosc/12*us)/256;           
    			CCAPM0 = 0x48;                  //PCA��ʱ��������16-bit��ʱ��ģʽ��ʹ��PCA�ж�
    			CR = 1; 						 //PCA��ʱ����ʼ����
			    while(!CCF0);
				CR = 0;
				CCF0 = 0;                   
				break;
		case 4:	CCON = 0;                       //��ʼ��PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCAʱ��ԴΪFosc/12
    			CCAP1L = (Fosc/12*us)%256;
				CCAP1H = (Fosc/12*us)/256;           
    			CCAPM1 = 0x48;                  //PCA��ʱ��������16-bit��ʱ��ģʽ��ʹ��PCA�ж�
    			CR = 1;                         //PCA��ʱ����ʼ����
				while(!CCF1);
				CR = 0;
				CCF1=0;
				break;
	}	 	
}