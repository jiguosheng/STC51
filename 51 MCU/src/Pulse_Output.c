#include <Var.h>

void Pulse_Output(unsigned long f,unsigned char ch)	    //fµ¥Î»ÎªHz
{
	COMD = 0x02;
	CCON = 0x00;
	CH = 0;
	CL = 0;
	if(f != 0)
	{
		switch(ch)
		{
	 		case C0:CCAPM0 = 0x4d;
					CCAP0L = (unsigned char)(Fosc*1000000/(4*f)+0.5);
					break;
			case C1:CCAPM1 = 0x4d;
					CCAP1L = (unsigned char)(Fosc*1000000/(4*f)+0.5);
					break;
		}
	}
	CR = 1; 
	EA = 1;	
}