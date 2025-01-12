#include <stdio.h>

#include "../mcc_generated_files/spi1.h"
#include "../mcc_generated_files/pin_manager.h"
#include "../mcc_generated_files/system.h"


#include "eeprom_driver.h"




uint8_t read_eeprom(uint16_t address){
    
    uint8_t message[4];
    uint8_t data[4];
    uint8_t cmd = read;
    //0000 0011 aaaa aaaa aaaa aaaa 0000 0000 message à envoyer, les 0 c'est pour garder l'horloge active le temps de recevoir les données 
    message[0] = cmd;
    message[1] = address>> 8;               //8 premiers
    message[2] = address;        // 8 derniers
    message[3] = 0x00;
    
    uint8_t total = 0;
    EEPROM_SELECT_SetLow();
    do{
        
        total = SPI1_Exchange8bitBuffer(&message[total],4, &data[total]);
        
    } while(total<4);
    
   
    EEPROM_SELECT_SetHigh();
    
    return data[3];
}


void write_eeprom(uint16_t address, uint8_t mot){
    
    uint8_t message[4];
    uint8_t data[4];
    uint8_t cmd = write;
    //0000 0011 aaaa aaaa aaaa aaaa mmmm mmmm message à envoyer, les 0 c'est pour garder l'horloge active le temps de recevoir les données 
    message[0] = cmd;
   message[1] = address>> 8;               //8 premiers
    message[2] = address;        // 8 derniers
    message[3] = mot;
    
    uint8_t total = 0;
    EEPROM_SELECT_SetLow();
    do{
        
        total = SPI1_Exchange8bitBuffer(&message[total],4 , &data[total]);
        
    } while(total<4);
    
   
    EEPROM_SELECT_SetHigh();
    

}

