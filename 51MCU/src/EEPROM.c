#include <Var.h>

unsigned char EEPROM_Read(unsigned int adr)
{
	unsigned char dat;

	IAP_CMD = EEPROM_BYTE_READ;
	IAP_CONTR = EEPROM_ENABLE|EEPROM_24MHZ;
	IAP_ADDRH = (adr&0xff00)>>8;
	IAP_ADDRL = adr&0x00ff;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	_nop_();
	dat = IAP_DATA;
	IAP_CMD = STANDBY;
	IAP_CONTR = EEPROM_UNENABLE;

 	return dat;
}

void EEPROM_Write(unsigned int adr,unsigned char dat)
{	
	IAP_CMD = EEPROM_BYTE_WRITE;
	IAP_CONTR = EEPROM_ENABLE|EEPROM_24MHZ;
	IAP_ADDRH = (adr&0xff00)>>8;
	IAP_ADDRL = adr&0x00ff;	
	IAP_DATA = dat;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	delay_us(55,T0);
	IAP_CMD = STANDBY;
	IAP_CONTR = EEPROM_UNENABLE;
}

void EEPROM_Erease(unsigned int adr)
{
	IAP_CMD = EEPROM_EREASE;
	IAP_CONTR = EEPROM_ENABLE|EEPROM_24MHZ;
	IAP_ADDRH = (adr&0xff00)>>8;
	IAP_ADDRL = adr&0x00ff;	
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	delay_ms(21,T0);
	IAP_CMD = STANDBY;
	IAP_CONTR = EEPROM_UNENABLE; 	
}
