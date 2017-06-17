#include <Var.h>

void ADC_Init()
{
 	P1ASF=0xff;      //¿ª8Í¨µÀ
	ADC_RES=0;
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL;
}

float ADC_Result(unsigned char channel)
{
	int Res=0;
	float res=0.0;

 	ADC_CONTR=ADC_POWER|ADC_SPEEDLL|channel|ADC_START;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while(!(ADC_CONTR&ADC_FLAG));
	ADC_CONTR&=~ADC_FLAG;
	Res=(ADC_RES<<2)|ADC_RESL;
	res=Res*5.0/1024;

	return res;
}