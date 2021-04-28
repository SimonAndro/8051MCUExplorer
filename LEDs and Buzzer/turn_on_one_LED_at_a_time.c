#include<reg52.h>
#include<intrins.h>


void delay(char x); // delay function
void main()
{
	char port1 = 0xfe;
	while(1)
	{
		P1 = port1;
		delay(100);
		port1 = _crol_(port1,1);
		P1 = port1;
		delay(100);
		
	}
}

void delay(char x)
{
	char y;
	while(x--)
		for(y = 0; y<120; y++);

}