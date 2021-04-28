#include<reg52.h>

sbit dc_motor = P1^0; 
sbit motor_switch = P3^4;
sbit speedUp = P3^6;
sbit speedDown = P3^7;

char dutyCyle = 10;
char period = 10;

void delay(char x);// delay function
	
void main()
{
	char count =0;
	 while(1)
	 {
			P1 = 0x00;
		 	delay(period*(dutyCyle/100));
			P1 = 0xff;
		  delay(period*((100-dutyCyle)/100));
		 
		 count++; 
		 if(count>=20)
		 {
				count = 0;
				P1 = 0xff;
				delay(200);
			 
			 dutyCyle ++;
			 
			 if(dutyCyle >=100)
			 {
					dutyCyle = 0;
			 }
			 
		 }
		 
	 }
}


void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<10; y++);
}