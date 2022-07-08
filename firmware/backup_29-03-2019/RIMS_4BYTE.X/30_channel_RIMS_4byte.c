
#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1H
#pragma config OSC = HS       // Oscillator Selection bits (RC oscillator w/ OSC2 configured as RA6)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bit (Brown-out Reset enabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = ON         // Low Voltage ICSP Enable bit (Low Voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)



#include <pic18f452.h>

#define __XTAL_FREQ 8000000

#define   sw1 PORTBbits.RB4
#define   sw2 PORTBbits.RB5
#define   sw3 PORTBbits.RB6
#define   sw4 PORTBbits.RB7
            


int COUNT=0,VAL=0,VAL1=0;
int b=0,i=0 ,j=0;
int ch1=0,ch2=0,ch3=0,ch4=0,ch5=0,ch6=0,ch7=0,ch8=0,ch9=0,ch10=0,ch11=0,ch12=0,ch13=0,ch14=0,ch15=0,ch16=0;
unsigned char data[32]={0};

 unsigned  int  dat=0;
 unsigned  int  dat1=0;
 unsigned  int  dat2=0;
 unsigned  int  dat3=0;

void Transmit(unsigned char);
void Init_Serial();

void delay()
{
   for(i=0;i<500;i++);
 
 }

void interrupt isr()
{
     if(TMR0IF)
    {
        TMR0ON=0;
       
        VAL=VAL+1;
        if(VAL==2)  
      {
            PORTDbits.RD1=~PORTDbits.RD1;
            if(COUNT==0)
            {
                ch1=0;
            }
            if(COUNT==1)
            {
                ch2=0;
            }
            if(COUNT==2)
            {
                ch3=0;
            }
            if(COUNT==3)
            {
                ch4=0;
            }
            if(COUNT==4)
            {
                ch5=0;
            }
            if(COUNT==5)
            {
                ch6=0;
            }
            if(COUNT==6)
            {
                ch7=0;
            }
            if(COUNT==7)
            {
                ch8=0;
            }
            if(COUNT==8)
            {
                ch9=0;
            }
            if(COUNT==9)
            {
                ch10=0;
            }
            if(COUNT==10)
            {
                ch11=0;
            }
            if(COUNT==11)
            {
                ch12=0;
            }
            if(COUNT==12)
            {
                ch13=0;
            }
            if(COUNT==13)
            {
                ch14=0;
            }
            if(COUNT==14)
            {
                ch15=0;
            }
            if(COUNT==15)
            {
                ch16=0;
            }
      
            if(COUNT<=7)
          {
           dat=(dat|(0<<COUNT));
           COUNT=COUNT+1;
           PORTA=COUNT;
           VAL=0;
          
          }
            
             if(COUNT>=8 && COUNT<16)
            {
               dat1=(dat1|(0<<(COUNT-8)));
               COUNT=COUNT+1;
               PORTA=COUNT;
               VAL=0;
               
            }
             
             if(COUNT==16)
            {
            COUNT=0;
            VAL=3;  
            PORTBbits.RB3=1;
            INT0IE=0;
            INT1IE=1;
            PORTBbits.RB2=0;  //MUX 2 Enable pin active
            TMR0ON=1;
             }
         }
       
        
         TMR0L=0x00;
         TMR0H=0x00;
         TMR0IF=0;
        if(VAL>=0&&VAL<2)
        {
            TMR0ON=1;
        }
    }
     
 /////////////////////////////////////////////////////////////////////////////////
     if(TMR1IF)
    {
         TMR1ON=0;
        TMR1L=0x00;
             TMR1H=0x00;
         PORTDbits.RD2=~PORTDbits.RD2;
         VAL1=VAL1+1;
      
        if(VAL1==2)   
      {
            PORTDbits.RD3=~PORTDbits.RD3;
            if(COUNT==0)
            {
                ch1=0;
            }
            if(COUNT==1)
            {
                ch2=0;
            }
            if(COUNT==2)
            {
                ch3=0;
            }
            if(COUNT==3)
            {
                ch4=0;
            }
            if(COUNT==4)
            {
                ch5=0;
            }
            if(COUNT==5)
            {
                ch6=0;
            }
            if(COUNT==6)
            {
                ch7=0;
            }
            if(COUNT==7)
            {
                ch8=0;
            }
            if(COUNT==8)
            {
                ch9=0;
            }
            if(COUNT==9)
            {
                ch10=0;
            }
            if(COUNT==10)
            {
                ch11=0;
            }
            if(COUNT==11)
            {
                ch12=0;
            }
            if(COUNT==12)
            {
                ch13=0;
            }
            if(COUNT==13)
            {
                ch14=0;
            }
            if(COUNT==14)
            {
                ch15=0;
            }
            if(COUNT==15)
            {
                ch16=0;
            }
            
            
            
            if(COUNT<=7)
            {
            dat2=(dat2|(0<<COUNT));
            COUNT=COUNT+1;
            PORTB=COUNT<<4;
            VAL1=0;
            ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8=0;
            }
            if(COUNT>=8 && COUNT<16)
            {
            dat3=(dat3|(0<<(COUNT-8)));
            COUNT=COUNT+1;
            PORTB=COUNT<<4;
            VAL1=0;
            ch9,ch10,ch11,ch12,ch13,ch14,ch15,ch16=0;
            }
             if(COUNT==16)
             {
            
            Transmit(dat);
            Transmit(dat1);
            Transmit(dat2);
            Transmit(dat3);

             COUNT=0;
            PORTBbits.RB3=0;
            //TMR0IE=1;
            INT0IE=1;
            INT1IE=0;
            TMR1L=0x00;
             TMR1H=0x00;
             PORTBbits.RB2=1;
            
            VAL1=3;          
            //INT1IF=0;
       
             }
             
        }
         TMR1IF=0;
        if(VAL1>=0&&VAL1<2)
        {
            TMR1ON=1;
        }
    }
    
 ///////////////////////////////////////////////////////////////////////////////////   
  if(INT0IE && INT0IF)
    {  PORTDbits.RD6=1; 
       if(COUNT==0)
        {   
            TMR0ON=0;
            TMR0IF=0;

           TMR0L=0x00;
             TMR0H=0x00;
            VAL=0;
            TMR0ON=1;
            PORTA=0;
            ch1=ch1+1;
            if(ch1==4)
            {
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch1=0;
            }
            INT0IF=0;
         }
       if(COUNT==1)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
         TMR0L=0x00;
             TMR0H=0x00; 
           TMR0ON=1;
           PORTA=1;
           ch2=ch2+1;
            if(ch2==4)
            {   
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch2=0;
            }
            INT0IF=0;
         }
        if(COUNT==2)
        { 
            TMR0ON=0;
            TMR0IF=0;
            VAL=0;
            TMR0L=0x00;
             TMR0H=0x00;
            TMR0ON=1;
            PORTA=2;
            ch3=ch3+1;
            if(ch3==4)
            {
                VAL=0;
                TMR0ON=0;
                 TMR0IF=0;
                  dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch3=0;
            }
            INT0IF=0;
         }
        if(COUNT==3)
        { 
            TMR0ON=0;
            TMR0IF=0;
            VAL=0;
          TMR0L=0x00;
             TMR0H=0x00;
            TMR0ON=1;

            PORTA=03;
            ch4=ch4+1;
            if(ch4==4)
            {
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                  dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch4=0;
            }
            INT0IF=0;
         }
       if(COUNT==4)
        {
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
           TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=04;
            ch5=ch5+1;
            if(ch5==4)
            {
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch5=0;
            }
            INT0IF=0;
         }
        if(COUNT==5)
        {
            TMR0ON=0;
            TMR0IF=0;
            
           VAL=0;
           TMR0L=0x00;
           TMR0H=0x00;
           TMR0ON=1;
            PORTA=05;
            ch6=ch6+1;
            if(ch6==4)
            {
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch6=0;
            }
            INT0IF=0;
         }
         if(COUNT==6)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=06;
            ch7=ch7+1;
            if(ch7==4)
            {
                VAL=0;
                 TMR0ON=0;
                 TMR0IF=0;
                 dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch7=0;
            }
            INT0IF=0;
         }
          if(COUNT==7)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=0x07;
            ch8=ch8+1;
            if(ch8==4)
            {
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                dat=dat|(1<<COUNT);
                COUNT=COUNT+1;
                ch8=0;
                
            }
            INT0IF=0;
         }
        
          if(COUNT==8)
        { 
           TMR0ON=0;
           TMR0IF=0;
           PORTA=0x08;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;
           ch9=ch9+1;
           if(ch9==4)
            {
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch9=0;
            }
            INT0IF=0;
        }
        
         if(COUNT==9)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=0b00001001;
            ch10=ch10+1;
            if(ch10==4)
            {
                VAL=0;
                TMR0ON=0;
               TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch10=0;
                
            }
            INT0IF=0;
         }
         if(COUNT==10)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=0b00001010;
            ch11=ch11+1;
            if(ch11==4)
            {
                VAL=0;
                TMR0ON=0;
              TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch11=0;
                
            }
            INT0IF=0;
         }
         if(COUNT==11)
        { 
            TMR0ON=0;
            TMR0IF=0;
            VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
            TMR0ON=1;

            PORTA=0b00001011;
            ch12=ch12+1;
            if(ch12==4)
            {
                VAL=0;
                TMR0ON=0;
              TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch12=0;
                
            }
            INT0IF=0;
         }
         if(COUNT==12)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=0b00001100;
            ch13=ch13+1;
            if(ch13==4)
            {
                VAL=0;
                TMR0ON=0;
              TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch13=0;
               
            }
            INT0IF=0;
         }
         if(COUNT==13)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=0b00001101;
            ch14=ch14+1;
            if(ch14==4)
            {
                VAL=0;
                TMR0ON=0;
             TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch14=0;
              
            }
            INT0IF=0;
         }
         if(COUNT==14)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
             TMR0L=0x00;
             TMR0H=0x00;
           TMR0ON=1;

            PORTA=0b00001110;
            ch15=ch15+1;
            if(ch15==4)
            {
                VAL=0;
                TMR0ON=0;
                 TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch15=0;
                
            }
            INT0IF=0;
         }
         if(COUNT==15)
        { 
           TMR0ON=0;
           TMR0IF=0;
           VAL=0;
           TMR0L=0x00;
           TMR0H=0x00;
           TMR0ON=1;

            PORTA=0b00001111;;
            ch16=ch16+1;
            if(ch16==4)
            {
                VAL=0;
                TMR0ON=0;
                TMR0IF=0;
                dat1=(dat1|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch16=0;      
             }
            INT0IF=0;
            
        }
      
        if(COUNT==16)
        {
            TMR0ON=0;
            TMR0IF=0;
            INT0IF=0;
             TMR0L=0x00;
             TMR0H=0x00;
            COUNT=0;
            VAL=0;
            PORTD=0; //LED ZERO
           
            PORTEbits.RE1=0; //Timer interrupt indication clear
            PORTEbits.RE2=0; //Timer interrupt indication clear
            
            PORTBbits.RB3=1;

            INT0IE=0;
            INT1IE=1;
            PORTBbits.RB2=0;  //MUX 2 Enable pin active
            
        }     
     }
       
       
       if(INT1IE && INT1IF)
    {   PORTDbits.RD6=1;
       if(COUNT==0)
        {   
            TMR1ON=0;
            TMR1IF=0;
            VAL1=0;
            
            TMR1L=0x00;
             TMR1H=0x00;
            TMR1ON=1;
            sw1=0;
            sw2=0;
            sw3=0;
            sw4=0;
           
            ch1=ch1+1;
            if(ch1==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch1=0;
            }
            INT1IF=0;
         }
       if(COUNT==1)
        { 
           TMR1ON=0;
           TMR1IF=0;
           VAL1=0;
           TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;
            sw1=1;
            sw2=0;
            sw3=0;
            sw4=0;
           ch2=ch2+1;
            if(ch2==4)
            {   
                VAL1=0;
                TMR1ON=0;
                dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch2=0;
            }
            INT1IF=0;
         }
        if(COUNT==2)
        { 
            TMR1ON=0;
            TMR1IF=0;
            VAL1=0;
         TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;
            sw1=0;
            sw2=1;
            sw3=0;
            sw4=0;
            ch3=ch3+1;
            if(ch3==4)
            {
                VAL1=0;
                TMR1ON=0;
               dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch3=0;
            }
            INT1IF=0;
         }
        if(COUNT==3)
        { 
            TMR1ON=0;
            TMR1IF=0;
            VAL1=0;
          TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;

            sw1=1;
            sw2=1;
            sw3=0;
            sw4=0;
            ch4=ch4+1;
            if(ch4==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch4=0;
            }
            INT1IF=0;
         }
       if(COUNT==4)
        {
           TMR1ON=0;
           TMR1IF=0;
           VAL1=0;
           TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;

            sw1=0;
            sw2=0;
            sw3=1;
            sw4=0;
            ch5=ch5+1;
            if(ch5==4)
            {
                VAL1=0;
                TMR1ON=0;

                dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch5=0;
            }
            INT1IF=0;
         }
        if(COUNT==5)
        {
            TMR1ON=0;
            TMR1IF=0;
             TMR1L=0x00;
             TMR1H=0x00;
            TMR1H=0;
            TMR1ON=1;

            sw1=1;
            sw2=0;
            sw3=1;
            sw4=0;
            ch6=ch6+1;
            if(ch6==4)
            {
                VAL1=0;
                 TMR1ON=0;
                dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch6=0;
            }
            INT1IF=0;
         }
         if(COUNT==6)
        { 
             TMR1ON=0;
             TMR1IF=0;
             VAL1=0;
              TMR1L=0x00;
             TMR1H=0x00;
             TMR1ON=1;

            sw1=0;
            sw2=1;
            sw3=1;
            sw4=0;
            ch7=ch7+1;
            if(ch7==4)
            {
                VAL1=0;
                 TMR1ON=0;
                dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch7=0;
            }
            INT1IF=0;
         }
          if(COUNT==7)
        { 
              TMR1ON=0;
              TMR1IF=0;
              VAL1=0;
             TMR1L=0x00;
             TMR1H=0x00;
              TMR1ON=1;

            sw1=1;
            sw2=1;
            sw3=1;
            sw4=0;
            ch8=ch8+1;
            if(ch8==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat2=dat2|(1<<COUNT);
                COUNT=COUNT+1;
                ch8=0;
                
            }
            INT1IF=0;
         }
        
          if(COUNT==8)
        { 
              TMR1ON=0;
            TMR1IF=0;
           VAL1=0;
          TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;

            sw1=0;
            sw2=0;
            sw3=0;
            sw4=1;
            ch9=ch9+1;
            if(ch9==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch9=0;
                
            }
            INT1IF=0;
         }
        
         if(COUNT==9)
        { 
             TMR1ON=0;
            TMR1IF=0;
              VAL1=0;
            TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;

            sw1=1;
            sw2=0;
            sw3=0;
            sw4=1;
            ch10=ch10+1;
            if(ch10==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch10=0;
                
            }
            INT1IF=0;
         }
         if(COUNT==10)
        { 
             TMR1ON=0;
            TMR1IF=0;
              VAL1=0;
           TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;

            sw1=0;
            sw2=1;
            sw3=0;
            sw4=1;
            ch11=ch11+1;
            if(ch11==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch11=0;
                
            }
            INT1IF=0;
         }
         if(COUNT==11)
        { 
             TMR1ON=0;
            TMR1IF=0;
            VAL1=0;
          TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;

            sw1=1;
            sw2=1;
            sw3=0;
            sw4=1;
            ch12=ch12+1;
            if(ch12==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch12=0;
                
            }
            INT1IF=0;
         }
         if(COUNT==12)
        { 
             TMR1ON=0;
              TMR1IF=0;
              VAL1=0;
           TMR1L=0x00;
             TMR1H=0x00;
             TMR1ON=1;

            sw1=0;
            sw2=0;
            sw3=1;
            sw4=1;
            ch13=ch13+1;
            if(ch13==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch13=0;
               
            }
            INT1IF=0;
         }
         if(COUNT==13)
        { 
           TMR1ON=0;
           TMR1IF=0;
           VAL1=0;
           TMR1L=0x00;
             TMR1H=0x00;
           TMR1ON=1;

            sw1=1;
            sw2=0;
            sw3=1;
            sw4=1;
            ch14=ch14+1;
            if(ch14==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch14=0;
              
            }
            INT1IF=0;
         }
         if(COUNT==14)
        { 
             TMR1ON=0;
             TMR1IF=0;
             VAL1=0;
           TMR1L=0x00;
             TMR1H=0x00;
            TMR1ON=1;

            sw1=0;
            sw2=1;
            sw3=1;
            sw4=1;
            ch15=ch15+1;
            if(ch15==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch15=0;
                
            }
            INT1IF=0;
         }
         if(COUNT==15)
        { 
          TMR1ON=0;
          TMR1IF=0;
          VAL1=0;
           TMR1L=0x00;
             TMR1H=0x00;
          TMR1ON=1;

            sw1=1;
            sw2=1;
            sw3=1;
            sw4=1;
            ch16=ch16+1;
            if(ch16==4)
            {
                VAL1=0;
                TMR1ON=0;
                dat3=(dat3|(1<<(COUNT-8)));
                COUNT=COUNT+1;
                ch16=0;
            }
            INT1IF=0;
         }
         
        if(COUNT==16)
        {   TMR1ON=0;
            Transmit(dat);
            Transmit(dat1);
            Transmit(dat2);
            Transmit(dat3);

           
            PORTBbits.RB3=0;
            TMR0IE=1;
            INT0IE=1;
            INT1IE=0;
            TMR1H=0x00;
            TMR1L=0x00;
            COUNT=0;
            VAL1=0;          
            PORTEbits.RE1=0;
            PORTEbits.RE2=0;
            INT1IF=0;
            
        } 
     }
}


void Init_Serial()
{
        //RCSTA = 0b00010000;
        TXSTA = 0b00100000;
        SPBRG = 12; //8Mhz,9600
        RCSTAbits.SPEN = 1;	
        TXSTAbits.TXEN=1;
}


void Transmit(unsigned char Dat)
{
	while(!TXSTAbits.TRMT);
    TXREG = Dat;
	
}	

   void main(void) 
   {
            ADCON1=0b00000110;
            PORTA=0;   //CHANNEL SELECTION PORT
            TRISA=0;
           
            
            PORTD=0;  //LED LOWER 8 CHANNEL
            TRISD=0;
            
              
            TRISBbits.RB0=1;   //INT 0  INPUT PIN
            TRISBbits.RB1=1;   //INT 1  INPUT PIN
            
            TRISBbits.RB3=0;   //ENABLE PIN FOR MUX 1
            TRISBbits.RB2=0;   //ENABLE PIN FOR MUX 2
            
            TRISBbits.RB4=0;   // mux 2 selection Bit0
            TRISBbits.RB5=0;   // mux 2 selection Bit1
            TRISBbits.RB6=0;   // mux 2 selection Bit2
            TRISBbits.RB7=0;   // mux 2 selection Bit3
            
             T0CON=0x00100111;   //FOR Mux 1
             TMR0L=0x00;
             TMR0H=0x00;
              
             
             T1CON=0x10110000;    //for mux 2
             TMR1L=0x00;
             TMR1H=0x00;
    
             PEIE=1;
    
             TMR0IF=0;
             TMR0IE=1;
             TMR1IF=0;
             TMR1IE=1;
             
             TXIE=1;
             TXIF=0;
    
             INT0IE=1; //EXTERNAL INTERRUPT 0 ENABLE
             INT0IF=0; //EXTERNAL INTERRUPT 0 FLAG CLEAR
             INTEDG0=1; //EXTERNAL INTERRUPT ON RISING EDGE
             

             INT1IF=0; //EXTERNAL INTERRUPT 1 FLAG CLEAR
             INTEDG1=1; //EXTERNAL INTERRUPT ON RISING EDGE
    
             TMR0ON=0;
             TMR1ON=0;

             Init_Serial();
             PORTBbits.RB2=1;
             PORTBbits.RB3=1;
             for(b=0;b<500;b++)
                 {
                    delay();
                 }
             PORTBbits.RB3=0;    
              GIE=1;
              
        
             while(1);
             return;
    } 