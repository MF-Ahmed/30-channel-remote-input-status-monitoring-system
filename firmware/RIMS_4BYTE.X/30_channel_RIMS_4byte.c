
#include <xc.h>
#include <pic18f4550.h>
#include "Config.h"



// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements 

// CONFIG1L
//#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
//#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
//#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 256      // Watchdog Timer Postscale Select bits (1:256)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = ON       // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
 
 
 
 
void interrupt isr()
{
    if(PIR1bits.RCIF)
    {
        PrintMsg("You Typed : ");
        DR1 = RCREG;
        
        Hex2Asc(DR1,1);
        //if((DR1 == 0x31)  &&  (DataReadFinal==1))
        //{    
//            PrintMsg("\n\r");                
//            Hex2Asc(data[3],1);  
//            Hex2Asc(data[2],1); 
//            Hex2Asc(data[1],1);  
//            Hex2Asc(data[0],1);
//            
//            Checksum +=  data[0]; 
//            Checksum +=  data[1];                 
//            Checksum +=  data[2]; 
//            Checksum +=  data[3]; 
//            Hex2Asc(Checksum ,1);             
//            PrintMsg("\n\r");           
//             data[0]=0x00;
//             data[1]=0x00;                         
//             data[2]=0x00;
//             data[3]=0x00; 
//             Checksum=0;
             //DR1=0;
             //DataReadFinal=0;
        //}    
    }
    
    if(PIR1bits.TMR1IF)
    {    
        
    TMR1L=0x00;
    TMR1H=0xDE;    // 35mSec    
        TMR1ON=1;         
        
       //PORTDbits.RD4 = ~PORTDbits.RD4;
       INTCONbits.TMR0IE=0; 
       INTCONbits.INT0IE=0;  
       
       Checksum=0;       
       ChannelNo++;
     
        if( ChannelNo>= Max_Channel_Count)
        {
            PORTDbits.RD4 = ~PORTDbits.RD4;  
             DataReadFinal=1;
//            if(DR1==0x31)
//            {
            PrintMsg("\n\r");                
            Hex2Asc(data[3],1);  
            Hex2Asc(data[2],1); 
            Hex2Asc(data[1],1);  
            Hex2Asc(data[0],1);
            
            Checksum +=  data[0]; 
            Checksum +=  data[1];                 
            Checksum +=  data[2]; 
            Checksum +=  data[3]; 
            Hex2Asc(Checksum ,1);             
            PrintMsg("\n\r");           
             data[0]=0x00;
             data[1]=0x00;                         
             data[2]=0x00;
             data[3]=0x00; 
             Checksum=0;
             ChannelNo=0;
            }
//            DR1=0;
//       }

        Select_Channel(ChannelNo); 
        
        TMR0ON=0;        
        TMR0L=0x00;
        TMR0H=0xCF;  // 25mSec   
        TMR0ON=1; 
        
        INTCONbits.TMR0IE=1;      
        INTCONbits.INT0IE=1;            
        PIR1bits.TMR1IF=0;    
    }    
    
    
    
    if(INTCONbits.INT0IF || INTCONbits.TMR0IF)     
    {
        TMR0L=0x00;
        TMR0H=0xCF;  // 25mSec   
        TMR0ON=1;     
       // PORTDbits.RD5 = ~PORTDbits.RD5;
          if(INTCONbits.INT0IF && (TMR0IF==0))
          { 
            COUNT++; 
            INTCONbits.INT0IF=0;           
          }  

           if((COUNT==MAX_PULSES)  && (TMR0IF==0))
           {
               if(ChannelNo<=8)
               {         
                        
                   data[0] |= (0x01<<(ChannelNo-1));         
               }
               else if(ChannelNo<=16)
               {                                     
                    data[1] |= (0x01<<(ChannelNo-9));         
               }
               else if(ChannelNo<=24)
               {                                     
                    data[2] |= (0x01<<(ChannelNo-17));         
               }                      
               else if(ChannelNo<=30)
               {                                    
                    data[3] |= (0x01<<(ChannelNo-25));         
               }                 
                          
               COUNT=0;
               INTCONbits.INT0IF=0;  

            }  
           else if ((TMR0IF))
           {
               if(ChannelNo<=8)
               {              
                data[0] &= ~(0x01<<(ChannelNo-1));     
               }
               else if(ChannelNo<=16)
               {              
                data[1] &= ~(0x01<<(ChannelNo-9));     
               }  
               else if(ChannelNo<=24)
               {              
                data[2] &= ~(0x01<<(ChannelNo-17));     
               }  
               else if(ChannelNo<=30)
               {              
                data[3] &= ~(0x01<<(ChannelNo-25));     
               }                                        
               COUNT=0;  
               INTCONbits.TMR0IF=0;        

           }          
     }   
 
}




   void main(void) 
   {           
        Config_Ports();        
        Config_Timers_INT();   
        Init_Serial();
        Select_Channel(ChannelNo);  
        while(1);
        return;
    } 