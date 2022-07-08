

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



#include <xc.h>

#define _XTAL_FREQ 8000000


unsigned char receive();
volatile unsigned char go=0;
int i=0;
unsigned char recv_Dat=0,data=0;
unsigned char rec_dat[4]={0};
void delay()
{
    for(i=0;i<100;i++);
}


void interrupt isr()
{
    if(RCIF)
    {
         rec_dat[data]=receive();
         data=data+1;
         if(data==4)
         {
             data=0;
         }
         go =1;
         RCIF=0;
    }
    
}


void Init_Serial()
{
        RCSTA = 0b10010000;
        // TXSTA = 0b00000100;
        SPBRG = 12;                 //8Mhz,9600
        RCSTAbits.SPEN = 1;	
        RCSTAbits.CREN = 1;	
}

void Init_interrupts()
{
	INTCONbits.PEIE =1;
	INTCONbits.GIE = 1;
	PIE1bits.RCIE = 1;
    RCIF=0;
 }

void Transmit(unsigned char Dat)
{
   while(!TXSTAbits.TRMT); 
	TXREG = Dat;
		
}	

unsigned char receive()
{

    while(!RCIF);
	recv_Dat=RCREG;
    
    return recv_Dat;
	
}

void main(void)
{
   
    
    TRISE=0;
    ADCON1bits.PCFG3=0;
    ADCON1bits.PCFG2=1;
    ADCON1bits.PCFG1=1;
    ADCON1bits.PCFG0=0;
    
    TRISA=0;
    TRISB=0;
    TRISD=0;
    TRISC=0b10000000;
  
    Init_Serial();
    Init_interrupts();
   
     while(1)
     {
         while(go==0);

         PORTD=rec_dat[0];
         PORTB=rec_dat[1];
         PORTE=(rec_dat[2]&(0x07)); 
         PORTC=(rec_dat[2]&(0xf8))>>3;
         PORTA=(rec_dat[3]&(0x7f));
         go=0;
     }
    
      return;
}
