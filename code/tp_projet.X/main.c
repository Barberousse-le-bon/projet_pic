/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device            :  PIC24FJ1024GB610
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include <math.h>
#include "lcd/lcd.h"
#include <stdio.h>
#include "eeprom_driver/eeprom_driver.h"

/*
                         Main application
 */


    uint8_t tmr_flag = 0;
    uint8_t time_flag = 0;


void setupLCD(){
    
    LCD_Initialize();
    LCD_PutString("Hello World!", 12);
    
}
void  TMR1_CallBack(void)
{
    tmr_flag = 1;
}

void RTCC_CallBack(void)
{
    time_flag = 1;
}


float get_temp(){
    uint16_t adc_value = ADC1BUF4;
    float temp = ((adc_value*3.3/1023)-0.5)*100;
    return temp;
}


int main(void)
{
    
    float temperature;
    char temp[5];

    
    
    char secondes[3];
    char minutes[3];
    char heures[3];
    char jour[3];
    char mois[3];
    char year[3];

    
    
    // initialize the device
    SYSTEM_Initialize();
    setupLCD();
    
    //EEPROM_SELECT_SetHigh();
    

    
    while (1)
    {

        if(tmr_flag == 1){
            tmr_flag =0;


        }
        if(time_flag){
            time_flag = 0;
            
            temperature = get_temp();
            sprintf( temp, "%.1f", temperature );
            
            sprintf( secondes, "%d%d", TIMELbits.SECTEN, TIMELbits.SECONE );
            sprintf( minutes, "%d%d", TIMEHbits.MINTEN, TIMEHbits.MINONE );
            sprintf( heures, "%d%d", TIMEHbits.HRTEN, TIMEHbits.HRONE );

            sprintf( jour, "%d%d", DATELbits.DAYTEN, DATELbits.DAYONE );
            sprintf( mois, "%d%d", DATEHbits.MTHTEN, DATEHbits.MTHONE );
            sprintf( year, "%d%d", DATEHbits.YRTEN, DATEHbits.YRONE );


            
            LCD_ClearScreen();
            LCD_PutString(temp, 5);
            LCD_PutString("C   ", 4);
            

            LCD_PutString(heures, 2 );
            LCD_PutString(":", 1 );
            LCD_PutString(minutes, 2 );
            LCD_PutString(":", 1 );
            LCD_PutString(secondes, 2 );

            LCD_PutString("\r\n", 4 );
            LCD_PutString(jour, 2 );
            LCD_PutString("/", 1 );
            LCD_PutString(mois, 2 );
            LCD_PutString("/", 1 );
            LCD_PutString(year, 2 );
        }


    }

    return 1;
}
/**
 End of File
*/

