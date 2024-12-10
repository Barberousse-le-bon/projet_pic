#include <stdio.h>

#include "../mcc_generated_files/spi1.h"
#include "../mcc_generated_files/pin_manager.h"
#include "../mcc_generated_files/system.h"


#include "eeprom_driver.h"




uint8_t read_eeprom(uint16_t address){
    
    uint8_t message[5];
    uint8_t cmd = read;
    //0000 0011 aaaa aaaa 0000 0000 message à envoyer, les 0 c'est pour garder l'horloge active le temps de recevoir les données 
    sprintf(message, "%d%d%d", cmd, address, 0 ); 
    EEPROM_SELECT_SetLow();
    
    
    
    //SPI1_Exchange();
    EEPROM_SELECT_SetHigh();
    
}