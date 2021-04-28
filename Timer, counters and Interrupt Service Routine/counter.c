
#include<reg52.h>

sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;


char code segData[] =	   // 0 to 9 codes for segment display
{0x3f,0x06,0x5b,
0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f}; 

char code segment[] =	   // selection choice for one of the 6 display segments
{0xfe,0xfd,0xfb,
0xf7,0xef,0xdf};

void seg_disp(int seconds); // display to the 7 segment
void init_count(); // timer initialization
void delay(char x);// delay function

void main()
{

	init_count();
	while(1)
	{
		seg_disp(TL0);
	}
}



void init_count() // timer initialization
{
	//TMOD
		TMOD = 0x05; // counter 0 in counter mode 1
	//initial value to the timer
		TH0 = 0;
		TL0 = 0;	
	//TCON
		TR0 = 1;
}	

void seg_disp(int count) // display to the 7 segment
{
			char tens, ones, hunds;
			char t = 1;
			hunds = count/100;
			tens = (count%100)/10;
			ones = (count%100)%10;
	
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
	
			P0 = segData[tens]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			
			P0 = segment[3];
			selectionLatch = 1;
			selectionLatch = 0;
	
			P0 = segData[hunds]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			
}
void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}