#ifndef ADC_H_
#define ADC_H_

	void ADC_Init();
	float ADC_Result(unsigned char channel);

	#define ADC_POWER 0x80
	#define ADC_FLAG  0x10
	#define ADC_START 0x08
	#define ADC_SPEEDLL 0x00
	#define ADC_SPEEDL 0x20
	#define ADC_SPEEDH 0x40
	#define ADC_SPEEDHH  0x60

#endif