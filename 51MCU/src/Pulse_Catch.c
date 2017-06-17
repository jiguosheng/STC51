#include <Var.h>

void Pulse_Rise_Catch(unsigned char ch)
{
 	COMD = 0x08;
	CCON = 0x00;
	CH = 0;
	CL = 0;
	switch(ch)
	{
		case C0:CCAPM0 = 0x21;
				break;
		case C1:CCAPM1 = 0x21;
				break;	
	}
	CR = 1;
	EA = 1;
} 

void Pulse_Up_Catch(unsigned char ch)
{
 	COMD = 0x08;
	CCON = 0x00;
	CH = 0;
	CL = 0;
	switch(ch)
	{
		case C0:CCAPM0 = 0x11;
				break;
		case C1:CCAPM1 = 0x11;
				break;	
	}
	CR = 1;
	EA = 1;
}

void Pulse_Rise_Up_Catch(unsigned char ch)
{
 	COMD = 0x08;
	CCON = 0x00;
	CH = 0;
	CL = 0;
	switch(ch)
	{
		case C0:CCAPM0 = 0x31;
				break;
		case C1:CCAPM1 = 0x31;
				break;	
	}
	CR = 1;
	EA = 1;
}