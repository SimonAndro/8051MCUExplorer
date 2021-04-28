#include<reg52.h>
#include<string.h>

sbit rs = P2^3; // register select
sbit rw = P2^4; // read/write
sbit en = P2^5; // read/write enable

char seconds = 0;
char minutes = 0;

char yourdata1[] ={"2020/7/19"};
char yourdata2[] ={"14:12:00 "};
	
void lcd_init(); // lcd initialization
void write_com(char com); //write command
void write_data(char _data); // write data

void delay(char x);// delay function
void main()
{
	char i;
	lcd_init();
	delay(20);
	
		//first information
		//display on line 1
		write_com(0x80);
		delay(10);
		
		for(i =0; i<strlen(yourdata1); i++)
		{
			write_data(yourdata1[i]);
			delay(10);
		}
		//display on line 2
		write_com(0xc0);
		delay(10);
		
		for(i =0; i<strlen(yourdata2); i++)
		{
			write_data(yourdata2[i]);
			delay(10);
		}
	
	while(1)
	{
		delay(10);
		seconds++;
		if(seconds>12)
		{
			seconds =0;
			minutes++;
			write_com(0xc0+3);
			write_data(minutes/10+48);
			write_com(0xc0+4);
			write_data(minutes%10+48);
		}
		else
		{
			write_com(0xc0+6);
			write_data(seconds/10+48);
			write_com(0xc0+7);
			write_data(seconds%10+48);
		}
	}
}

void lcd_init() // lcd initialization
{
		// prepare the screen ->16*2 cells, 5*7 matrix for each cell
		write_com(0x38);
		// turn on display
		write_com(0x08);
		// clear the screen
		write_com(1);
	  // prepare cursor and data pointer
		write_com(6);
	  // cursor setup
	  write_com(0x0c);
		
}
void write_com(char com) //write command
{
	rs = 0; rw =0; P0 = com;
	en = 0;
	delay(10);
	en = 1;
	delay(10);
	en = 0;
}
void write_data(char _data) // write data
{
	rs = 1;  rw = 0; P0 = _data;
	en = 0;
	delay(10);
	en = 1;
	delay(10);
	en = 0;
	
}

void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}