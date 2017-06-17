#ifndef LCD12864_H_
#define LCD12864_H_

	void LCD12864_Init();
	void LCD12864_Display(unsigned char X,unsigned char Y,unsigned char dat);
	void LCD12864_Display2(unsigned char X,unsigned char Y,unsigned char len,unsigned char *dat);
	void LCD12864_DrawPoint(unsigned char X,unsigned char Y,unsigned char Color);
	void ClrRAM_12864();

#endif