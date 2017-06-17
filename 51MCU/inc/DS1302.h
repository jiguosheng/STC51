#ifndef DS1302_H_
#define DS1302_H_

	void DS1302_Write_Adress(unsigned char adr);
	unsigned char DS1302_Read_Data();
	void DS1302_Write_Command(unsigned char com);
	void DS1302_Init(unsigned char year,unsigned char month,unsigned char ndate,unsigned char day,unsigned char hour,unsigned char mintues,unsigned char second);
	void DS1302(unsigned char X,unsigned char Y,unsigned char adr);

	#define R_Sec 0x81
	#define W_Sec 0x80
	#define R_Min 0x83
	#define W_Min 0x82
	#define R_Hour 0x85
	#define W_Hour 0x84
	#define R_Date 0x87
	#define W_Date 0x86
	#define R_Mon 0x89
	#define W_Mon 0x88
	#define R_Day 0x8B
	#define W_Day 0x8A
	#define R_Year 0x8D
	#define W_Year 0x8C

#endif