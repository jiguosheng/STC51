#include <Var.h>

void PWM0(float duty)
{
 	CCON = 0;                       
    CL = 0;                         
    CH = 0;
    CMOD = 0x08;                    //设置PCA时钟源频率为Fosc
    CCAP0H = CCAP0L = 0xff*duty;         //设置PWM0输出方波占空比
    CCAPM0 = 0x42;                  
    CR = 1;                         
}

void PWM1(float duty)
{
 	CCON = 0;                      
    CL = 0;                         
    CH = 0;
    CMOD = 0x00;                    //设置PCA时钟源频率为Fosc/12                                    
    CCAP1H = CCAP1L = 0xff*duty;         //设置PWM0输出方波占空比
    CCAPM1 = 0x42;                  
    CR = 1;                         
}