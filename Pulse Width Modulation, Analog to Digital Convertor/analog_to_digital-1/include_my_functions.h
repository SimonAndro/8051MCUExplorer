#include<reg52.h>
#include<intrins.h>
//#include "lcd_display.c"
sbit Scl = P2^1;
sbit Sda = P2^0;

sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;

unsigned char code segData[] =	   // 0 to 9 codes for segment display
{0x3f,0x06,0x5b,
0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f}; 

unsigned  char code segment[] =	   // selection choice for one of the 6 display segments
{0xfe,0xfd,0xfb,
0xf7,0xef,0xdf};

/*
void iic_start();
void iic_send(char _data);
char iic_read();
void iic_ack(); 
void iic_noAck(); 
void iic_stop();
void DAC(char _byte); 
char ADC(char channel);
*/
//void delay(char x);// delay function
//void seg_disp(char seconds, char minutes); // display to the 7 segment
	
//void main()
//{
	//char num = 0;
	//char flag = 0;
	
	//lcd_init();
	//ADC(0);
	//write_data(ADC(0));
	//while(1)
	//{
		//DAC(num);
		//num++;
		//delay(30);
		//write_com(0x80);
		//write_data(48+ADC(0)/50);
		//write_data('.');
		//write_data(48+(ADC(0)%50)/10);
		//delay(100);
	//	num = ADC(0);
	//	seg_disp(num,0);
	//}
//}
void iic_start()
{
	
	Scl = 1;
	_nop_();
	Sda = 1;
	_nop_();
	Sda = 0;
	
}
void iic_send(char _data)
{
	char oneByte = 8;
	char temp = 0x80; // 1000 0000
	//1000 0000
	//0XXX XXXX
	//1XXX XXXX
	
	while(oneByte)
	{
		Scl = 0;   // added new line 1
		if((temp&_data)==0)
		//if(temp&_data==0) // changed this line 
		{
			Sda = 0;
		}
		else
		{
			Sda = 1;
		}
		Scl = 0;
		_nop_();
		Scl = 1;
		_nop_();  // added new line 2
		Scl = 0;  // added new line 3
		
		_data = _data<<1;
		oneByte--;
	}
	
}

unsigned char iic_read()
{
		 unsigned char check = 0x80;
		 unsigned char read = 0;
		 char bitCount=8;

	   Sda=1;
	   while(bitCount)
	   {
		  Scl=0;
          _nop_();
		  Scl=1;
		  _nop_();
		  if(Sda==1)
			{
				read = read|check;
			}
			check = check>>1;
			bitCount--;
		}
		return(read);
}

void iic_ack()
{
	Sda = 0;
	Scl = 0;
	_nop_();
	Scl = 1;
	_nop_();
	Scl = 0;
	
}
void iic_noAck()
{
	Scl = 0;
	Sda = 1;
	_nop_();
	Scl = 1;
	_nop_();
	Scl = 0;
	
}
void iic_stop()
{
	Scl = 1;
	_nop_();
	Sda = 0;
	_nop_();
	Sda = 1;
	
}

void myDAC(char _byte)
{
	iic_start();
	iic_send(0x90); // write to D/A convertor
	iic_ack();
	iic_send(0x40); //enable analog out
	iic_ack();
	iic_send(_byte); // send data
	iic_ack();
	iic_stop();
}	
	


void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}


void seg_disp(char seconds, char minutes) // display to the 7 segment
{
			char tens, ones;
			char mtens, mones;
			char t = 1; 
	
			tens = seconds/50;
			ones = (seconds%50)/10;
	
			mtens = minutes/10;
			mones = minutes%10;
	
			//seconds
			P0 = segment[5];
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = segData[ones]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			P0 = segment[4];
			selectionLatch = 1;
			selectionLatch = 0;
	
			P0 = segData[tens]|0x80; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			// minutes
			P0 = segment[3];
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = segData[mones]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			P0 = segment[2];
			selectionLatch = 1;
			selectionLatch = 0;
	
			P0 = segData[mtens]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
}


char ADC(char channel)
{
	char readData;
	iic_start();
	iic_send(0x90); // write to D/A convertor
	iic_ack();
	iic_send(0x40|channel); //enable analog out and read from channel
	iic_ack();
	
	iic_start();
	iic_send(0x91); // send read address
	iic_ack();
	readData = iic_read();
	iic_noAck();
	iic_stop();
	return readData;
}	

	