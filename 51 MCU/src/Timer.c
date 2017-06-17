#include <Var.h>

void T0_Init(unsigned char ms)
{
 	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = (65535-Fosc/12*ms*1000)%256;//)%256;		//设置定时初值
	TH0 = (65535-Fosc/12*ms*1000)/256;//)/256;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//定时器0开始计时
} 

void T1_Init(unsigned char ms)
{
 	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = (65535-Fosc/12*ms*1000)%256;//)%256;		//设置定时初值
	TH1 = (65535-Fosc/12*ms*1000)/256;//)/256;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	ET1 = 1;
	EA = 1;
	TR1 = 1;		//定时器1开始计时
}

void PCA0_Init(unsigned char ms)					//CL与CH从0通过时钟计数，当CH、CL达到CCAP0L与CCAP0H时产生中断
{
 	CCON = 0;                       //初始化PCA
                                    //PCA定时器停止运行
                                    //清除CF标志位
                                    //清除所有中断标志
    CL = 0;                         //复位PCA基础定时器
    CH = 0;
    CMOD = 0x00;                    //PCA时钟源为Fosc/12
                                    //失效PCA定时器溢出中断
    CCAP0L = (Fosc/12*ms*1000)%256;
	CCAP0H = (Fosc/12*ms*1000)/256;           
    CCAPM0 = 0x49;                  //PCA定时器工作于16-bit定时器模式并使能PCA中断
    CR = 1;                         //PCA定时器开始工作
    EA = 1;
}

void PCA1_Init(unsigned char ms)					//CL与CH从0通过时钟计数，当CH、CL达到CCAP0L与CCAP0H时产生中断
{
 	CCON = 0;                       //初始化PCA
                                    //PCA定时器停止运行
                                    //清除CF标志位
                                    //清除所有中断标志
    CL = 0;                         //复位PCA基础定时器
    CH = 0;
    CMOD = 0x00;                    //PCA时钟源为Fosc/12
                                    //失效PCA定时器溢出中断
    CCAP1L = (Fosc/12*ms*1000)%256;
	CCAP1H = (Fosc/12*ms*1000)/256;           
    CCAPM1 = 0x49;                  //PCA定时器工作于16-bit定时器模式并使能PCA中断
    CR = 1;                         //PCA定时器开始工作
    EA = 1;
}

void delay_ms(unsigned char ms,unsigned char flag)
{
	switch(flag)
	{
		case 1:	AUXR &= 0x7F;		//定时器时钟12T模式
				TMOD &= 0xF0;		//设置定时器0模式
				TMOD |= 0x01;		//设置定时器0模式
				TL0 = (65535-Fosc/12*ms*1000)%256;//)%256;		//设置定时初值
				TH0 = (65535-Fosc/12*ms*1000)/256;//)/256;		//设置定时初值
				TF0 = 0;		//清除TF0标志
				ET0 = 0;
				TR0 = 1;		//定时器0开始计时
				while(!TF0);
				TR0 = 0;
				TF0 = 0;
				break;
		case 2:	AUXR &= 0xBF;		//定时器时钟12T模式
				TMOD &= 0x0F;		//设置定时器1模式
				TMOD |= 0x10;		//设置定时器1模式
				TL1 = (65535-Fosc/12*ms*1000)%256;//)%256;		//设置定时初值
				TH1 = (65535-Fosc/12*ms*1000)/256;//)/256;		//设置定时初值
				TF1 = 0;		//清除TF0标志
				ET1 = 0;
				TR1 = 1;		//定时器0开始计时
				while(!TF1);
				TR1 = 0;
				TF1 = 0;
				break;
		case 3:	CCON = 0;                       //初始化PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCA时钟源为Fosc/12
    			CCAP0L = (Fosc/12*ms*1000)%256;
				CCAP0H = (Fosc/12*ms*1000)/256;           
    			CCAPM0 = 0x48;                  //PCA定时器工作于16-bit定时器模式并使能PCA中断
    			CR = 1; 						 //PCA定时器开始工作
			    while(!CCF0);
				CR = 0;
				CCF0 = 0;                   
				break;
		case 4:	CCON = 0;                       //初始化PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCA时钟源为Fosc/12
    			CCAP1L = (Fosc/12*ms*1000)%256;
				CCAP1H = (Fosc/12*ms*1000)/256;           
    			CCAPM1 = 0x48;                  //PCA定时器工作于16-bit定时器模式并使能PCA中断
    			CR = 1;                         //PCA定时器开始工作
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
		case 1:	AUXR &= 0x7F;		//定时器时钟12T模式
				TMOD &= 0xF0;		//设置定时器0模式
				TMOD |= 0x02;		//设置定时器0模式
				TL0 = 255-Fosc/12*us;		//设置定时初值
				TH0 = 255-Fosc/12*us;		//设置定时初值
				TF0 = 0;		//清除TF0标志
				ET0 = 0;
				TR0 = 1;		//定时器0开始计时
				while(!TF0);
				TR0 = 0;
				TF0 = 0;
				break;
		case 2:	AUXR &= 0xBF;		//定时器时钟12T模式
				TMOD &= 0x0F;		//设置定时器1模式
				TMOD |= 0x20;		//设置定时器1模式
				TL1 = 256-Fosc/12*us;		//设置定时初值
				TH1 = 256-Fosc/12*us;		//设置定时初值
				TF1 = 0;		//清除TF0标志
				ET1 = 0;
				TR1 = 1;		//定时器0开始计时
				while(!TF1);
				TR1 = 0;
				TF1 = 0;
				break;
		case 3:	CCON = 0;                       //初始化PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCA时钟源为Fosc/12
    			CCAP0L = (Fosc/12*us)%256;
				CCAP0H = (Fosc/12*us)/256;           
    			CCAPM0 = 0x48;                  //PCA定时器工作于16-bit定时器模式并使能PCA中断
    			CR = 1; 						 //PCA定时器开始工作
			    while(!CCF0);
				CR = 0;
				CCF0 = 0;                   
				break;
		case 4:	CCON = 0;                       //初始化PCA
				CL = 0;
    			CH = 0;
    			CMOD = 0x00;                    //PCA时钟源为Fosc/12
    			CCAP1L = (Fosc/12*us)%256;
				CCAP1H = (Fosc/12*us)/256;           
    			CCAPM1 = 0x48;                  //PCA定时器工作于16-bit定时器模式并使能PCA中断
    			CR = 1;                         //PCA定时器开始工作
				while(!CCF1);
				CR = 0;
				CCF1=0;
				break;
	}	 	
}