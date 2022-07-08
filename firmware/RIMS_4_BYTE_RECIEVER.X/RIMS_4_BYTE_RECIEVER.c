
// PIC16F877 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 8000000


//#define FOSC 		2000000
//#define BAUDRATE 	9600
//#define BRGVAL (((FOSC/64)/BAUDRATE)/16)-1 // for BRGH = 0


#include <xc.h>
#include "Config.h"



void delay()
{
    for(i=0;i<100;i++);
}


void interrupt isr()
{
    
    if(PIR1bits.TMR1IF)
    {
   
        
        TMR1L = 0;
       TMR1H = 0;
            DRREq_Delay++;
         if(DRREq_Delay==10)   
         {   
        //PORTBbits.RB5 = ~PORTBbits.RB5;    
        //PrintMsg("\n\r DR1 request sent :");
        //Transmit(DR1);
        
        DRREq_Delay=0;
         
         }
        
        PIR1bits.TMR1IF=0;
    
    }   
        
        
    if(RCIF)
    {          
        data_Rx_Buff[count] = RCREG;    
        count++; 
        RCIF=0;
        RCREG=0;
       }

}


void Init_interrupts()
{    

	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
    RCIF=0;
    //INTCONbits.T0IF=0;

 }



void main(void)
{
   
    
    Config_Ports();
    Init_interrupts();
    Config_Timer();    
    Init_Serial();
    Init_Display();

     while(1)
     {
   
        ProcData();        

        // if(Computed_Checksum == RX_Checksum)
         //{         
            Display_Data(data_Rx[11]); 
            _CLK1();        
            Display_Data(data_Rx[8]);              
            _CLK2();
            Display_Data(data_Rx[5]);
            _CLK3();        
            Display_Data(data_Rx[2]);       
            _CLK4();
                        
         //}
 
      }
    

     
}
