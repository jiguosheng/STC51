#ifndef LCD1602_H_
#define LCD1602_H_

	void Lcd_Init();
	void Lcd_display(unsigned char X,unsigned char Y,unsigned char dat);

	#define CLEAR 0x01
	#define RETURN 0x02				  
	#define CURSOR_LEFT 0x04	//写入数据后光标左移
	#define REVEAL_NOT_SHIFT 0x04    //显示屏不移动
	#define CURSOR_RIGHT 0x06   //写入数据后光标右移
	#define REVEAL_SHIFT  0x05         //写入新数据后显示屏整体右移1个字符
	#define REVEAL_CYRSOR_OFF 0x08     //关显示
	#define CURSOR_OFF 0x08            //无光标
	#define CURSOR_TWINKLE 0x08        //光标闪烁
	#define CURSOR__NOT_TWINKLE 0x09      //光标不闪烁
	#define CURSOR_ON 0x0a      //光标开
	#define REVEAL_ON 0x0c       //显示开
	#define CURSOR_AC_LEFT 0x10    //光标左移1格，且AC减1
	#define CURSOR_AC_RIGHT 0x14   //光标右移1格，且AC加1
	#define REVEAL_LEFT 0x18     //显示器字符全部左移，光标不动
	#define REVEAL_RIGHT 0x1c	 //显示器字符全部右移，光标不动
	#define BUS_4 0x20           //数据总线为4位
	#define BUS_8 0x30           //数据总线为8位
	#define REVEAL_1 0x20        //显示1行
	#define REVEAL_2 0x28        //显示2行
	#define M57 0x20             //5*7点阵
	#define M510 0x24            //5*10点阵

//	extern unsigned char code number[];
//	extern unsigned char code String1[];
//	extern unsigned char code String2[];

#endif