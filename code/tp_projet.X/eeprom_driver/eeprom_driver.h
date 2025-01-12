#define read 0x03;
#define write 0x2;

uint8_t read_eeprom(uint16_t address);
void write_eeprom(uint16_t address, uint8_t mot);