#include <pic18f4550.h>
#include <string.h>


#define __XTAL_FREQ 8000000

volatile int COUNT=0,VAL=0,VAL1=0;
volatile int b=0,i=0 ,j=0;
volatile int ch1=0,ch2=0,ch3=0,ch4=0,ch5=0,ch6=0,ch7=0,ch8=0,ch9=0,ch10=0,ch11=0,ch12=0,ch13=0,ch14=0,ch15=0,ch16=0;
volatile unsigned char data[4]={0};
volatile unsigned char Checksum=0;
 volatile unsigned char DataValid=0;
  volatile unsigned char DataReadFinal=0;
   volatile unsigned char DR1=0;
 volatile unsigned  int  ChannelNo=1; 

#define   sw1 PORTDbits.RD0
#define   sw2 PORTDbits.RD1
#define   sw3 PORTDbits.RD2
#define   sw4 PORTDbits.RD3


#define   TwoPulseT0L      0x00  // 50mSec
#define   TwoPulseT0H      0x9F  
 
#define   TwoPulseT1L      0x00
#define   TwoPulseT1H      0xBB  // 70mSec
  
#define   OnePulseT0L      0x00  // 30mSec
#define   OnePulseT0H      0xC3 
  
#define   OnePulseT1L      0x00
#define   OnePulseT1H      0xCE  // 50mSec
 
 
 

#define   Blank		32

#define   Max_Channel_Count		31
 
#define MAX_PULSES 1      //  Max no. of pulses to count for a channel

void Transmit(unsigned char);
void Init_Serial(void);
void Config_Ports(void);
void PrintMsg(unsigned char *Buf);
void PrintLFCR();
void Hex2Asc(unsigned char BinBuf, unsigned char PrtBlkFlag);
void Hex2AscW(unsigned int BinBufW);
void Config_Timers_INT(void);
void Select_Channel(unsigned int ChNo);
unsigned char Receive(void);


void Init_Serial()
{
        SPBRG = 12; //8Mhz,9600 8N1
        RCSTAbits.SPEN = 1;     // USART Enable	
        TXSTAbits.TXEN=1;       // TX Enable
        RCSTA1bits.SREN=1;      // Rx Enable 
        RCSTA1bits.CREN=1;      // Rx Enable 
        TXSTA1bits.SYNC=0;      // Asynchronous mode
        
}


void Transmit(unsigned char Dat)
{
	while(!TXSTAbits.TRMT);
    TXREG = Dat;
	
}	


unsigned char Receive()
{
    unsigned char RxData=0;
    
	while(!RCSTA1bits.SREN);
    RxData = RCREG;
    return RxData;
    
    
	
}	




void delay()
{
   int i=0;
   for(i=0;i<500;i++);
 
 }


void Config_Ports()
{
    ADCON1=0b00000110;
    ///// ADC AN0... AN12 bits are digital  I/O
    ADCON1bits.PCFG0=1;
    ADCON1bits.PCFG1=1;
    ADCON1bits.PCFG2=1;
    ADCON1bits.PCFG3=1;    

    PORTA=0;   //CHANNEL SELECTION PORT
    TRISA=0;


    PORTD=0;  //LED LOWER 8 CHANNEL
    TRISD=0;

    

    TRISBbits.RB0=1;   //INT 0  INPUT PIN
    TRISBbits.RB1=1;   //INT 1  INPUT PIN

    TRISEbits.RE0=0;   //ENABLE PIN FOR MUX 1 (EN_MUX1)
    TRISEbits.RE1=0;   //ENABLE PIN FOR MUX 2 (EN_MUX2)
    
    PORTEbits.RE1=1;  // Initially select Mux 1 for 1-16 channels
    

    TRISDbits.RD0=0;   // mux selection Bit0 sw1 
    TRISDbits.RD1=0;   // mux selection Bit1 sw2 
    TRISDbits.RD2=0;   // mux selection Bit2 sw3 
    TRISDbits.RD3=0;   // mux selection Bit3 sw4 
    
    TRISDbits.RD4=0;   // for Testing only 
    TRISDbits.RD5=0;   // for Testing only 
    TRISDbits.RD6=0;   // for Testing only 
    TRISDbits.RD7=0;   // for Testing only 
    
    
    PORTDbits.RD4=0;
    PORTDbits.RD5=0;
    PORTDbits.RD6=0;
    PORTDbits.RD7=0;
    
    sw1 = 0;
    sw2 = 0;
    sw3 = 0;
    sw4 = 0;

}


void Hex2AscW(unsigned int BinBufW)
{
 unsigned char *cptr;

    cptr = (unsigned char *)&BinBufW;
    Hex2Asc(cptr[1],0);			// Print high byte in ascii format
    Hex2Asc(cptr[0],0);			// Print low byte in ascii format
    Transmit(Blank);
	
}
//================================================================================================//

void Hex2Asc(unsigned char BinBuf, unsigned char PrtBlkFlag)
{
  	unsigned char Cnt, tmp;
  

		tmp = BinBuf & 0x0F;
		BinBuf = (BinBuf &0xF0)>>4;   
		for (Cnt=0; Cnt<2; Cnt++)
		{
			if (Cnt)
				BinBuf = tmp;
			if ((unsigned char)BinBuf>=0 && (unsigned char)BinBuf <=9)
				BinBuf += '0';
			else if ((BinBuf>= 0x0A) && (BinBuf <= 0x0F))
				BinBuf += 0x37;
			   Transmit(BinBuf);    
			
		} 
		if (PrtBlkFlag) 
		 Transmit(Blank); 
	 
}

//========================================================

void PrintMsg(unsigned char *Buf)
{
    unsigned int BLen, Cnt;
    BLen= (int)strlen(Buf);
    for (Cnt=0; Cnt<BLen; Cnt++)
    {            
        Transmit(Buf[Cnt]);
    }
}		
//========================================================
void PrintLFCR()
{  	
  PrintMsg("\r\n");

}		


void Config_Timers_INT()
{
    T0CONbits.T0PS0=1;             // 1:4 PreScaler for 125ms overflow interrupt
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=0;
    
    T0CONbits.T0CS=0;
    T0CONbits.PSA=0;
    T0CONbits.T08BIT=0;
    T0CONbits.T0SE=0;


   //T1CON=0x10110000;    //for mux 2

    T1CONbits.RD16 = 1;    //Enables register Read/Write of Timer1 in one 16-bit operation
    T1CONbits.T1CKPS0 = 1;  // 1:8 Prescaler value          
    T1CONbits.T1CKPS1 = 1;   
    T1CONbits.NOT_T1SYNC=1; // do not synchronise external clock input

    T1CONbits.TMR1CS=0;
    T1CONbits.T1OSCEN=1;
    

    
    RCONbits.IPEN=0;    
    INTCONbits.PEIE=1;        // Peripheral interrupt enable bit
    INTCONbits.GIE=1;
  
   INTCONbits.TMR0IE=0;
   INTCONbits.INT0IF=0;
 
   PIE1bits.TMR1IE=0;   //Timer 1 interrupt enable  
   PIR1bits.TMR1IF=0;

    TXIE=1;
    TXIF=0;
    
    INTCONbits.INT0IF=0; //EXTERNAL INTERRUPT 0 FLAG CLEAR
    INTCONbits.INT0IE=1; //EXTERNAL INTERRUPT 0 ENABLE
    INTCON2bits.INTEDG0=1; //EXTERNAL INTERRUPT ON RISING EDGE
    
    //TMR0L=0x00;
   // TMR0H=0x66;  // 67mSec     

    //TMR0L=0x00;
    //TMR0H=0x9F;  // 50mSec  
    
    //TMR0L=0x00;
    //TMR0H=0x95;  // 55mSec  
    
    //TMR0L=0x00;
    //TMR0H=0xBB;  // 35mSec  
    
   TMR0L=0x00;
   TMR0H=0xCF;  // 25mSec   
    
    
//    TMR0L=0x00;
//    TMR0H=0xE2;  // 15mSec     
    
    //(TimerValue-65536)*2 = Delay for Timer 0
    //(TimerValue-65536)*4 = Delay for Timer 1
    
    INTCONbits.TMR0IE=1;  //Timer 0 interrupt enable       
    TMR0ON=1;  

    //TMR1L=0x00;
    //TMR1H=0x99;    // 104mSec    
    
    //TMR1L=0x00;
    //TMR1H=0xBB;    // 69mSec    
    
    
    //TMR1L=0x00;
    //TMR1H=0xB6;    // 75mSec    
       
    
   // TMR1L=0x00;
   // TMR1H=0xC5;    // 60mSec  
    TMR1L=0x00;
    TMR1H=0xDE;    // 35mSec    
    
//    TMR1L=0x00;
//    TMR1H=0xE2;    // 30mSec   
//    
     

//    TMR1L=0x00;
//    TMR1H=0xD9;    // 40mSec       
    
//    TMR1L=0x00;
//    TMR1H=0xD5;    // 44mSec    
    
    
    
//    
//    TMR1L=0x00;
//    TMR1H=0xD0;    // 49mSec     
    
//    TMR1L=0x00;
//    TMR1H=0xC0;    // 65mSec      
    
    
    
    
    T1CONbits.TMR1ON=1;  //Timer 1 ON      
    PIE1bits.TMR1IE=1;   //Timer 1 interrupt enable       


}

void Select_Channel(unsigned int ChNo)
{
    if((ChNo<=16))  // for first 16 channels
    {
        PORTEbits.RE1=1;     
        //goto sw;       
    }
    else 
    {
      ChNo = ChNo-16;
      PORTEbits.RE1=0;
        //goto sw;
    } 
    
//sw: 
switch(ChNo)        
    {
        case 1:
        sw4=0;sw3=0;sw2=0;sw1=0;
        break;
        case 2:
        sw4=0;sw3=0;sw2=0;sw1=1;
        break;    
        case 3:
        sw4=0;sw3=0;sw2=1;sw1=0;
        break;    
        case 4:
        sw4=0;sw3=0;sw2=1;sw1=1;
        break;
        case 5:
        sw4=0;sw3=1;sw2=0;sw1=0;
        break;        
        case 6:
        sw4=0;sw3=1;sw2=0;sw1=1;
        break;    
        case 7:
        sw4=0;sw3=1;sw2=1;sw1=0;
        break;     
        case 8:
        sw4=0;sw3=1;sw2=1;sw1=1;
        break;  
        case 9:
        sw4=1;sw3=0;sw2=0;sw1=0;
        break;  
        case 10:
        sw4=1;sw3=0;sw2=0;sw1=1;
        break;  
        case 11:
        sw4=1;sw3=0;sw2=1;sw1=0;
        break;  
        case 12:
        sw4=1;sw3=0;sw2=1;sw1=1;
        break;  
        case 13:
        sw4=1;sw3=1;sw2=0;sw1=0;
        break;  
        case 14:
        sw4=1;sw3=1;sw2=0;sw1=1;
        break;  
        case 15:
        sw4=1;sw3=1;sw2=1;sw1=0;
        break;  
        case 16:
        sw4=1;sw3=1;sw2=1;sw1=1;
        break;            
        default: 
        sw4=0;sw3=0;sw2=0;sw1=0;
        break;
    }

}