#include<reg52.h>

sbit buzzer = P0^7; 
char count = 0;

void timer0_init(); // timer 0 initialization

void timer0_poll(); // polling for timer 0

void delay(char x);// delay function 
	
void main()
{
	buzzer = 0;
	timer0_init();
	while(1)
	{
		timer0_poll();
	}	
}

void timer0_init()
{
	//Set the TMOD register
	TMOD = 0x01; // timer 0 in timer mode 1
	//initialize the timer
	TH0 = (65536-46082)/256;
	TL0 = (65536-46082)%256;
	//start the timer
	TR0 = 1; // start the timer
}

void timer0_poll() // polling for timer 0
{
	while(TF0==0);
	TF0 = 0; // reset the overflow flag
	// reload timer 0
	TH0 = (65536-46082)/256;
	TL0 = (65536-46082)%256;
	
	count++; // increament count
	if(count==20)
	{
		//timer 0 has counted upto 1 second
		count = 0;
		buzzer = 1;
		delay(10);
		buzzer = 0;	
		
	}
}

void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}