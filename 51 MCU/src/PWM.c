#include <Var.h>

void PWM0(float duty)
{
 	CCON = 0;                       
    CL = 0;                         
    CH = 0;
    CMOD = 0x08;                    //����PCAʱ��ԴƵ��ΪFosc
    CCAP0H = CCAP0L = 0xff*duty;         //����PWM0�������ռ�ձ�
    CCAPM0 = 0x42;                  
    CR = 1;                         
}

void PWM1(float duty)
{
 	CCON = 0;                      
    CL = 0;                         
    CH = 0;
    CMOD = 0x00;                    //����PCAʱ��ԴƵ��ΪFosc/12                                    
    CCAP1H = CCAP1L = 0xff*duty;         //����PWM0�������ռ�ձ�
    CCAPM1 = 0x42;                  
    CR = 1;                         
}