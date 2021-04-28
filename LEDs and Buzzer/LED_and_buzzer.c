#include<reg52.h>

sbit led1 = P1^0;
sbit buzzer = P0^0;
void delay(char x); // delay function
void main()
{
	while(1)
	{
		led1 = 0;
		buzzer = 1;
		delay(100);
		led1 = 1;
		buzzer = 0;
		delay(100);
	}
}

void delay(char x)
{
	char y;
	while(x--)
		for(y = 0; y<120; y++);

}