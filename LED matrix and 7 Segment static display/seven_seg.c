#include <reg52.h>

sbit position4 = P0^3;
sbit position5 = P0^4;
sbit position6 = P0^5;
sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;
char time = 3;
void delay(char x); // delay function
void main()
{
		while(1)
		{
			P0 = 0xff;
			position4 = 0;
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = 0x06; //1--> 0x06,
			dataLatch = 1;
			dataLatch = 0;
		
			delay(time);
		
			P0 = 0xff;
			position5 = 0;
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = 0x5b; //2--> 0x5b,
			dataLatch = 1;
			dataLatch = 0;
		
			delay(time);
		
			P0 = 0xff;
			position6 = 0;
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = 0x4f; //3--> 0x4f,
			dataLatch = 1;
			dataLatch = 0;
			
			delay(time);
		}
		
}

void delay(char x)
{
	char y;
	while(x--)
		for(y = 0; y<120; y++);

}