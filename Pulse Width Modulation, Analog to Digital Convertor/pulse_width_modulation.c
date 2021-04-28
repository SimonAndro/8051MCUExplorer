#include<reg52.h>
#include<intrins.h>

sbit dc_motor = P1^0; 
sbit motor_switch = P3^4;
sbit speedUp = P3^6;
sbit speedDown = P3^7;

unsigned char dutyCyle = 0;
unsigned char period = 10;

void delay(unsigned char x);// delay function
	
void main()
{
	bit onFlag = 1;
	 while(1)
	 {
		 if(onFlag)
		 {
				P1 = 0x00;
				//dc_motor=1;
				delay(period*(dutyCyle/100));
				//dc_motor=0;
				P1 = 0xff;
				delay(period*((100-dutyCyle)/100));
		 }
		 
			if(motor_switch==0)
			{
				delay(20);
				if(motor_switch==0)
				{
					while(motor_switch==0);
					//dc_motor = ~dc_motor;
						onFlag = ~onFlag ;
				}
			}
			
			// speed up the motor
			if(speedUp==0)
			{
				delay(20);
				if(speedUp==0)
				{
					//dc_motor=1;
					while(speedUp==0);
					
					dutyCyle = dutyCyle<=10?(dutyCyle + 1):10;
					
				}
			}
			
			// speed down the motor
			if(speedDown==0)
			{
				delay(20);
				if(speedDown==0)
				{
					//dc_motor=1;
					while(speedDown==0);
					
					if(dutyCyle>0)
					{
						dutyCyle = dutyCyle-1;
					}
					
					
				}
			}
	 }
}


void delay(unsigned char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);

}