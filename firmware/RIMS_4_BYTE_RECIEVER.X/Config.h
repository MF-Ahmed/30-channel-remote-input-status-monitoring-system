
#include <string.h>

unsigned char receive();
volatile unsigned char go=0;
volatile unsigned tmepLB =0;
volatile unsigned tmepHB =0;
int i=0;
unsigned char recv_Dat=0,data=0;
unsigned char rec_dat[4]={0};
volatile unsigned char data_Rx[25]={0};
volatile unsigned char data_Rx_Buff[25]={0};
volatile unsigned char data_Rx_ASCii[25]={0};

volatile unsigned char data_Rx_Curr[25]={0};
volatile unsigned char data_Rx_Prev[25]={0};
volatile unsigned Data_CNT = 0;
volatile unsigned char RX_Checksum_Curr = 0;
volatile unsigned char RX_Checksum_Prev = 0;
volatile unsigned char RX_Checksum = 0;

volatile unsigned Computed_Checksum = 0;

unsigned char count=0;
unsigned char DRREq_Delay=0;
void Config_Ports();
void Init_Serial();
void delay();
void Hex2Asc(unsigned char BinBuf, unsigned char PrtBlkFlag);
void Hex2AscW(unsigned int BinBufW);
void Transmit(unsigned char Dat);
void Display_Data(unsigned char databyte);
void _CLK1(void);
void _CLK2(void);
void _CLK3(void);
void _CLK4(void);
void Init_Display();
void ProcData();
 void Config_Timer();
unsigned char  Asc2Hex(unsigned char Byte1, unsigned char Byte2);
void PrintMsg(unsigned char *Buf);
int ComputeChkSum(void);

#define  ON 1
#define  OFF 0

#define  CLK1 PORTBbits.RB1
#define  CLK2 PORTBbits.RB2
#define  CLK3 PORTBbits.RB3
#define  CLK4 PORTBbits.RB4
#define  CheckSum_LED PORTBbits.RB5
#define DR1   0x31
#define DR2   0x32
#define DR3   0x33
#define   Blank		32

enum {CHILLER1_ON,CHILLER1_OFF,CHILLER1_TRIP,CHILLER2_ON,CHILLER2_OFF,CHILLER2_TRIP,CHILLER3_ON,CHILLER3_OFF,CHILLER3_TRIP,
      PUMP1_ON,PUMP1_OFF,PUMP1_TRIP,PUMP2_ON,PUMP2_OFF,PUMP2_TRIP,PUMP3_ON,PUMP3_OFF,PUMP3_TRIP,PUMP4_ON,PUMP4_OFF,PUMP4_TRIP,
      PUMP5_ON,PUMP5_OFF,PUMP5_TRIP, PUMP6_ON,PUMP6_OFF,PUMP6_TRIP,EQUIP_ON,EQUIP_OFF,EQUIP_TRIP
     } Chiller_PumpsEnums;

enum { CR,LF,DataByte1,Space1,Space2,DataByte2,Space3,Space4,DataByte3,Space5,Space6,DataByte4,Space7,Space8,CheckSum 

    }dataEnum;     
     
     
     
//enum {PUMP1_ON,PUMP1_OFF,PUMP1_TRIP} Pump1Enums;
//enum {PUMP2_ON,PUMP2_OFF,PUMP2_TRIP} Pump2Enums;
//enum {PUMP3_ON,PUMP3_OFF,PUMP3_TRIP} Pump3Enums;
//enum {PUMP4_ON,PUMP4_OFF,PUMP4_TRIP} Pump4Enums;
//enum {PUMP5_ON,PUMP5_OFF,PUMP5_TRIP} Pump5Enums;
//enum {PUMP6_ON,PUMP6_OFF,PUMP6_TRIP} Pump6Enums;
//enum {EQUIP_ON,EQUIP_OFF,EQUIP_TRIP} EquipEnums;




//enum {sa,s,s};



void Config_Ports()
{    

     // TRISX 
    // 0 = Output
    // 1= Input   
    
    
    TRISDbits.TRISD0=0;   // D0
    TRISDbits.TRISD1=0;   // D1
    TRISDbits.TRISD2=0;   // D2
    TRISDbits.TRISD3=0;   // D3
    TRISDbits.TRISD4=0;   // D4
    TRISDbits.TRISD5=0;   // D5
    TRISDbits.TRISD6=0;   // D6
    TRISDbits.TRISD7=0;   // D7
        
    PORTDbits.RD0=0;      // D0      
    PORTDbits.RD1=0;      // D1 
    PORTDbits.RD2=0;      // D2 
    PORTDbits.RD3=0;      // D3 
    PORTDbits.RD4=0;      // D4 
    PORTDbits.RD5=0;      // D5 
    PORTDbits.RD6=0;      // D6 
    PORTDbits.RD7=0;      // D7 

    
    TRISBbits.TRISB1=0;   // CLK1 for O0...O7
    TRISBbits.TRISB2=0;   // CLK2 for O8...O15
    TRISBbits.TRISB3=0;   // CLK2 for O16...O23
    TRISBbits.TRISB4=0;   // CLK2 for O24...O29
    TRISBbits.TRISB5=0;   // Data_Communication Error LED    
    // All select lines are disabled
    
    PORTBbits.RB1= 1;
    PORTBbits.RB2= 1;
    PORTBbits.RB3= 1;
    PORTBbits.RB4= 1;
    PORTBbits.RB5= 0; // No Checksum error initially
    
    
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1; 
    
}


void Init_Serial()
{

    SPBRG = 12;                 //8Mhz,9600       
    TXSTAbits.SYNC=0;   
    RCSTAbits.SPEN = 1;	
    PIE1bits.RCIE = 1;        
    RCSTAbits.CREN = 1;	
    TXSTAbits.TXEN = 1;
        
        
}


void Init_Display()
{
 
    Display_Data(0); 
    _CLK1();        
    Display_Data(0);              
    _CLK2();
    Display_Data(0);
    _CLK3();        
    Display_Data(0);       
    _CLK4();   

}

void Transmit(unsigned char Dat)
{
	while(!TXSTAbits.TRMT);
    TXREG = Dat;
	
}	


unsigned char Receive()
{
    unsigned char RxData=0;
    
	while(RCSTAbits.SREN);
    RxData = RCREG;
    return RxData;
    
    
	
}	


 void Config_Timer()
 {
     T1CONbits.T1CKPS0=1;   //1:8Prescaler
     T1CONbits.T1CKPS1=1; 
     
     T1CONbits.T1OSCEN=0;
     T1CONbits.TMR1CS=0;
       
    TMR1L = 0;
    TMR1H = 0;
    T1CONbits.TMR1ON=1;    
    PIE1bits.TMR1IE=1;

 }




void Display_Data(unsigned char databyte)
{
    

PORTDbits.RD0 = (databyte & 0x01)>> CHILLER1_ON;
PORTDbits.RD1 = (databyte & 0x02)>> CHILLER1_OFF;
PORTDbits.RD2 = (databyte & 0x04)>> CHILLER1_TRIP;
PORTDbits.RD3 = (databyte & 0x08)>> CHILLER2_ON;
PORTDbits.RD4 = (databyte & 0x10)>> CHILLER2_OFF;
PORTDbits.RD5 = (databyte & 0x20)>> CHILLER2_TRIP;
PORTDbits.RD6 = (databyte & 0x40)>> CHILLER3_ON;
PORTDbits.RD7 = (databyte & 0x80)>> CHILLER3_OFF; 


}



void _CLK1()
{
    PORTBbits.RB1= 0;
    delay();
    PORTBbits.RB1= 1;
    delay();
    PORTBbits.RB1= 0;
}



void _CLK2()
{
    PORTBbits.RB2= 0;
    delay();
    PORTBbits.RB2= 1;
    delay();
    PORTBbits.RB2= 0;
}

void _CLK3()
{
    PORTBbits.RB3= 0;
    delay();
    PORTBbits.RB3= 1;
    delay();
    PORTBbits.RB3= 0;
}

void _CLK4()
{
    PORTBbits.RB4= 0;
    delay();
    PORTBbits.RB4= 1;
    delay();
    PORTBbits.RB4= 0;
}


void ProcData()
{
    char TxData=0;
  if(count==19 )
  {   
   
    data_Rx_Curr[2] = Asc2Hex(data_Rx_Buff[2],data_Rx_Buff[3]);
    data_Rx_Curr[5] = Asc2Hex(data_Rx_Buff[5],data_Rx_Buff[6]);    
    data_Rx_Curr[8] = Asc2Hex(data_Rx_Buff[8],data_Rx_Buff[9]);   
    data_Rx_Curr[11] = Asc2Hex(data_Rx_Buff[11],data_Rx_Buff[12]);
    RX_Checksum_Curr = Asc2Hex(data_Rx_Buff[14],data_Rx_Buff[15]); 
   
   if( data_Rx_Prev[2] == data_Rx_Curr[2])
   {   
        data_Rx_Prev[2] = data_Rx_Curr[2];
        data_Rx[2] =  data_Rx_Prev[2]; 
        PrintMsg("\r\n data_Rx[2] = ");
        Hex2Asc( data_Rx[2],0);         
   }
    if( data_Rx_Prev[5] == data_Rx_Curr[5])
    {    
        data_Rx_Prev[5] = data_Rx_Curr[5];
         data_Rx[5] =  data_Rx_Prev[5]; 
        PrintMsg("\r\n data_Rx[5] = ");
        Hex2Asc(data_Rx[5],0);         
    }
    if( data_Rx_Prev[8] == data_Rx_Curr[8])
    {    
        data_Rx_Prev[8] = data_Rx_Curr[8]; 
         data_Rx[8] =  data_Rx_Prev[8];
        PrintMsg("\r\n data_Rx[8] = ");
        Hex2Asc(data_Rx[8],0);         
    }
    if( data_Rx_Prev[11] == data_Rx_Curr[11])
    {  
               
        data_Rx_Prev[11] = data_Rx_Curr[11]; 
          data_Rx[11] =  data_Rx_Prev[11]; 
        PrintMsg("\r\n data_Rx[11] = ");
        Hex2Asc(data_Rx[11],0);          
    }
   
   if( RX_Checksum_Prev == RX_Checksum_Curr)
   {   
         RX_Checksum_Prev = RX_Checksum_Curr;
         RX_Checksum = RX_Checksum_Prev; 
        
         
        if(ComputeChkSum())  // if return 1 the checksum error
        {
            //PrintMsg("\n\r Checksum Error ");
            CheckSum_LED = 1;
        
        }    
        else CheckSum_LED = 0;            
   }
        
           
    data_Rx_Prev[2] = data_Rx_Curr[2];
    data_Rx_Prev[5] = data_Rx_Curr[5];   
    data_Rx_Prev[8] = data_Rx_Curr[8];   
    data_Rx_Prev[11] = data_Rx_Curr[11];   
    RX_Checksum_Prev = RX_Checksum_Curr;  
     count=0;
     
  
 }
    
    


}


int ComputeChkSum()
{
   
    char i,a,b=0;
    char checksum=0;
    
    
    
    checksum = (char)(data_Rx[2] + data_Rx[5] + data_Rx[8] + data_Rx[11]) & 0xFF;
     
    //PrintMsg("\r\n Computed Checksum = ");
    //Hex2Asc(checksum,1);
    
       // PrintMsg("\r\n RX_Checksum = ");
       // Hex2Asc( (char)RX_Checksum,1); 
    

        
    if(checksum == RX_Checksum)
    {
       //PrintMsg("\r\n No Checksum error good to Go!!");
        return 0;
    }
        
    else
    {
        //PrintMsg("\r\n Checksum error!!");
        return 1;
    }    
    
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


unsigned char  Asc2Hex(unsigned char Byte1, unsigned char Byte2)
{
  	unsigned char Cnt, tmpLB, tmpHB, Data=0; 
        
               if(((Byte1>='0') && (Byte1<='9'))  ||  ((Byte2>='0') && (Byte2<='9')))
                {               
                   if(Byte1<='9'){
                        tmpLB  = Byte1 & 0x0F;  
                        Data |= (tmpLB & 0x0F)<<4;
                    
                   }
                    if(Byte2<='9'){
                                                           
                    tmpHB  = Byte2 & 0x0F;  
                    Data |= (tmpHB & 0x0F);
                  
                    }
                }       
        
                if(((Byte1>='A') && (Byte1<='F'))  || ((Byte2>='A') && (Byte2<='F') ))
                { 
                    
                    if(((Byte1>='A') && (Byte1<='F'))){
                          tmpLB  =   (Byte1 & 0x0F)- 0x37;                   
                         Data |= (tmpLB & 0x0F) <<4;                   

 
                    }
                    
                    if(((Byte2>='A') && (Byte2<='F'))){
                    tmpHB  =  ((Byte2 & 0x0F) - 0x37);

                    Data |= (tmpHB & 0x0F);                      
       
                    }
                }       
        
        
        return  Data;
        

	 
}


//========================================================

void PrintMsg(unsigned char *Buf)
{
    unsigned int BLen, Cnt;
    BLen = (int)strlen(Buf);
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
