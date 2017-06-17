#ifndef LCD1602_H_
#define LCD1602_H_

	void Lcd_Init();
	void Lcd_display(unsigned char X,unsigned char Y,unsigned char dat);

	#define CLEAR 0x01
	#define RETURN 0x02				  
	#define CURSOR_LEFT 0x04	//д�����ݺ�������
	#define REVEAL_NOT_SHIFT 0x04    //��ʾ�����ƶ�
	#define CURSOR_RIGHT 0x06   //д�����ݺ�������
	#define REVEAL_SHIFT  0x05         //д�������ݺ���ʾ����������1���ַ�
	#define REVEAL_CYRSOR_OFF 0x08     //����ʾ
	#define CURSOR_OFF 0x08            //�޹��
	#define CURSOR_TWINKLE 0x08        //�����˸
	#define CURSOR__NOT_TWINKLE 0x09      //��겻��˸
	#define CURSOR_ON 0x0a      //��꿪
	#define REVEAL_ON 0x0c       //��ʾ��
	#define CURSOR_AC_LEFT 0x10    //�������1����AC��1
	#define CURSOR_AC_RIGHT 0x14   //�������1����AC��1
	#define REVEAL_LEFT 0x18     //��ʾ���ַ�ȫ�����ƣ���겻��
	#define REVEAL_RIGHT 0x1c	 //��ʾ���ַ�ȫ�����ƣ���겻��
	#define BUS_4 0x20           //��������Ϊ4λ
	#define BUS_8 0x30           //��������Ϊ8λ
	#define REVEAL_1 0x20        //��ʾ1��
	#define REVEAL_2 0x28        //��ʾ2��
	#define M57 0x20             //5*7����
	#define M510 0x24            //5*10����

//	extern unsigned char code number[];
//	extern unsigned char code String1[];
//	extern unsigned char code String2[];

#endif