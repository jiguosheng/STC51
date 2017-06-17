#include <Var.h>

void Check_Busy()
{  
    RS=0;
    RW=1;
    E=1;
    DATA=0xff;
    while((DATA&0x80)==0x80);//æ��ȴ�
    E=0;
}

void Write_Cmd(unsigned char Cmd)
{
	Check_Busy();
	RS=0;
	RW=0;
	E=1;
	DATA=Cmd;
	delay_us(5,T0);
	E=0;
	delay_us(5,T0);
}

/*��ʾ��ʵ�ʵ�ֱַ����void lcd_wcmd(ʵ�ʵ�ַ��80H��90H��88H��98H)*/

void Write_Data(unsigned char Data)
{
	Check_Busy();
	RS=1;
	RW=0;
	E=1;
	DATA=Data;
	delay_us(5,T0);
	E=0;
	delay_us(5,T0);
}

unsigned char Read_Data()
{
 	unsigned char rdata;
	Check_Busy();
	RS=1;
	RW=1;
	E=0;
	delay_us(5,T0);
	E=1;
	delay_us(3,T0);
	rdata=DATA;
	E=0;
	delay_us(5,T0);

	return rdata;
}

void LCD12864_Init()  //LCD��ʼ��
{
	RES = 1;
	PSB = 1;
   	Write_Cmd(0x30);       //ѡ�����ָ�
   	delay_us(50,T0);         //��ʱ����100us
   	Write_Cmd(0x30);       //ѡ��8bit������
   	delay_us(20,T0);         //��ʱ����37us
	Write_Cmd(0x08);       
   	delay_us(50,T0);         
   	Write_Cmd(0x14);
	delay_us(50,T0);
   	Write_Cmd(0x0c);       //����ʾ(���αꡢ������)
   	delay_us(50,T0);         //��ʱ����100us
   	Write_Cmd(0x01);       //�����ʾ�������趨��ַָ��Ϊ00H
   	delay_ms(15,T0);           //��ʱ����10ms
   	Write_Cmd(0x06);       //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ�������������1λ�ƶ�
    delay_us(50,T0);         //��ʱ����100us
}

void LCD12864_Display(unsigned char X,unsigned char Y,unsigned char dat)
{
 	switch(X)
	{
	 	case 1: Write_Cmd(0x80+Y);
				break;
		case 2:	Write_Cmd(0x90+Y);
				break;
		case 3: Write_Cmd(0x88+Y);
				break;
		case 4:	Write_Cmd(0x98+Y);
				break;
	}
	Write_Data(dat);
}

void LCD12864_Display2(unsigned char X,unsigned char Y,unsigned char len,unsigned char *dat)
{
	 char i=0;
	 switch(X)
	{
	 	case 1: Write_Cmd(0x80+Y);
				break;
		case 2:	Write_Cmd(0x90+Y);
				break;
		case 3: Write_Cmd(0x88+Y);
				break;
		case 4:	Write_Cmd(0x98+Y);
				break;
	}
	for(i=0;i<len;i++)
	{
		Write_Data(*(dat+i));
	}
}

void LCD12864_DrawPoint(unsigned char X,unsigned char Y,unsigned char Color)   //X:0~127;Y:0~63
{
    unsigned char Row,Tier,Tier_bit ;
    unsigned char ReadOldH,ReadOldL ;

    Write_Cmd(0x34);
    Write_Cmd(0x36);
    Tier=X>>4 ;
    Tier_bit=X&0x0f ;
    if(Y<32)
    {
        Row=Y ;
    }
    else 
    {
        Row=Y-32 ;
        Tier+=8 ;
    }
    Write_Cmd(Row+0x80);
    Write_Cmd(Tier+0x80);
    Read_Data();
    ReadOldH=Read_Data();
    ReadOldL=Read_Data();
    Write_Cmd(Row+0x80);
    Write_Cmd(Tier+0x80);
    if(Tier_bit<8)
    {
        switch(Color)
        {
            case 0 :
            ReadOldH&=(~(0x01<<(7-Tier_bit)));		 //��n������ȥ
            break ;
            case 1 :
            ReadOldH|=(0x01<<(7-Tier_bit));			 //��n��������һ���� 
            break ;
            case 2 :
            ReadOldH^=(0x01<<(7-Tier_bit));			 //���n�������ģ��ͱ䱻���������n���ǿհ׵ģ��ͱ�����
            break ;
            default :
            break ;
        }
        Write_Data(ReadOldH);
        Write_Data(ReadOldL);
    }
    else 
    {
        switch(Color)
        {
            case 0 :
            ReadOldL&=(~(0x01<<(15-Tier_bit)));
            break ;
            case 1 :
            ReadOldL|=(0x01<<(15-Tier_bit));
            break ;
            case 2 :
            ReadOldL^=(0x01<<(15-Tier_bit));
            break ;
            default :
            break ;
        }
        Write_Data(ReadOldH);
        Write_Data(ReadOldL);
    }
    Write_Cmd(0x30);
}

void ClrRAM_12864() 
{   
	unsigned char i,j;   
	for(i=0;i<64;i++)   
		for(j=0;j<16;j++)   
		{     
			Write_Cmd(0x34);    
			Write_Cmd(i+0x80);    
			Write_Cmd(j+0x80);
   			Write_Cmd(0x30);    
   			Write_Data(0x00);   
    		Write_Data(0x00);   
		} 
} 