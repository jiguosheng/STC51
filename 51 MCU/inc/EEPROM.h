#ifndef EEPROM_H_
#define EEPROM_H_

	unsigned char EEPROM_Read(unsigned int adr);
	void EEPROM_Write(unsigned int adr,unsigned char dat);
	void EEPROM_Erease(unsigned int adr);

	#define STANDBY 0x00
	#define EEPROM_BYTE_READ  0x01
	#define EEPROM_BYTE_WRITE 0x02
	#define EEPROM_EREASE 0x03
	#define EEPROM_ENABLE 0x80
	#define EEPROM_UNENABLE 0x00
	#define CMD_FAIL 0x10
	#define EEPROM_30MHZ 0x00
	#define EEPROM_24MHZ 0x01
	#define EEPROM_20MHZ 0x02
	#define EEPROM_12MHZ 0x03
	#define EEPROM_6MHZ 0x04
	#define EEPROM_3MHZ 0x05
	#define EEPROM_2MHZ 0x06
	#define EEPROM_1MHZ 0x07

#endif