#include <Var.h>

unsigned char key_message()
{
	unsigned char keymessagehang,keymessagelie;
	unsigned char keymessage=0xff;

	keyboard=0xf0;
 	if(keyboard!=0xf0) 
	{ 
		delay_ms(10,T0);
      	if(keyboard!=0xf0)
		{
	  		keymessagehang=keyboard;
		}
	  	keyboard=0x0f;
		delay_ms(10,T0);
	  	keymessagelie=keyboard;
		keymessage=keymessagehang+keymessagelie;  
		switch(keymessage)
		{
	   		case 0xe7: keymessage=0;break ;
	   		case 0xeb: keymessage=1;break ;
	   		case 0xed: keymessage=2;break ;
	   		case 0xee: keymessage=3;break ;
	   		case 0xd7: keymessage=4;break ;
	   		case 0xdb: keymessage=5;break ;
	   		case 0xdd: keymessage=6;break ;
	   		case 0xde: keymessage=7;break ;
	   		case 0xb7: keymessage=8;break ;
	   		case 0xbb: keymessage=9;break ;
	   		case 0xbd: keymessage=10;break ;
	   		case 0xbe: keymessage=11;break ;
	   		case 0x77: keymessage=12;break ;
	   		case 0x7b: keymessage=13;break ;
	   		case 0x7d: keymessage=14;break ;
	   		case 0x7e: keymessage=15;break ;
		} 
	}

	return keymessage;
}

		
	    /* unsigned char dat=0xff;		
		dat = key_message(); 
		if(dat != 0xff)
		{
			while(key_message() != 0xff);
			displayshumaguan(dat,dat);
			delay_ms(50,T0);
		}*/

