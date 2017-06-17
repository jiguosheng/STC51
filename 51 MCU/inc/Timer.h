#ifndef Timer_H_
#define Timer_H_

	void T0_Init(unsigned char ms);
	void T1_Init(unsigned char ms);
	void PCA0_Init(unsigned char ms);
	void PCA1_Init(unsigned char ms);
	void delay_ms(unsigned char ms,unsigned char flag);
	void delay_us(unsigned char us,unsigned char flag);

	#define T0 1
	#define T1 2
	#define CC0 3
	#define CC1 4

#endif