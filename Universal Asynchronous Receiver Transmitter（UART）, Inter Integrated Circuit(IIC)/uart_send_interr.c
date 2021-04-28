#include<reg52.h>
#include<string.h>

#define uchar unsigned char
	
char code myMSG[] = 
{
"program file begins here\n"
"#include<reg52.h>\n"
"#include<string.h>  \n"
"  \n"
"#define uchar unsigned char\n"
"	 \n"
"char code myMSG[] = {\"The world is a beautiful place\n\"};\n"					
"  \n"
"  \n"
"void delay(uchar x);\n"
"void uart_init();\n"
"  \n"
"  \n"
"bit txFlag = 1;  \n"
"  \n"
"void main()  \n"
"{ \n"
"	unsigned int i = 0;\n"
"	uart_init();\n"
"	 \n"
"	while(1)\n"
"	{\n"
"		      \n"
"		      \n"
"			if(txFlag)  \n"
"			{   \n"
"				txFlag = 0;  \n"
"				SBUF = myMSG[i];    \n"
"				i++;  \n"
"				if(i==strlen(myMSG))\n"
"				{ \n"
"					i  = 0; \n"
"				} \n"
"				delay(10);\n"
"			}   \n"
"	 \n"
"		      \n"
"		      \n"
"	}\n"
"} \n"
"  \n"
"void delay(uchar x) \n"
"{ \n"
"	uchar y;\n"
"	while(x--)  \n"
"		for(y = 0; y<120; y++); \n"
"} \n"
"void uart_init() \n"
"{ \n"
"	// initialize timer 1 in mode 2(8 bit auto reload)  \n"
"	TMOD = 0x20;\n"
"	TH1 = 0xfd; \n"
"	SCON = 0x50;\n"
"	TR1 = 1;\n"
"	TI =  0;\n"
"	//using inteerrupt \n"
"	EA = 1; // allow all interrupts   \n"
"	ES = 1; // enable serial interrupt\n"
"	 \n"
"} \n"
"  \n"
"  \n"
"void serial_ISR() interrupt 4  \n"
"{ \n"
"	TI = 0; \n"
"	txFlag = 1; \n"
"	 \n"
"} \n"
"  \n"
"program file ends here \n\n\n\n\n"
}; 									                                            


void delay(uchar x);
void uart_init();


bit txFlag = 1;

void main()
{
	unsigned int i = 0;
	uart_init();
	
	while(1)
	{
		
			if(txFlag)
			{
				txFlag = 0;
				SBUF = myMSG[i];
				i++;
				if(i==strlen(myMSG))
				{
					i  = 0;
				}
			}
	
		
		
	}
}

void delay(uchar x)
{
	uchar y;
	while(x--)
		for(y = 0; y<120; y++);
}
void uart_init()
{
	PCON = PCON|0x80; //set SMOD to 1 to double the speed of the uart
	// initialize timer 1 in mode 2(8 bit auto reload)
	TMOD = 0x20;
	TH1 = 0xfd;
	SCON = 0x50;
	TR1 = 1;
	TI =  0;
	//using interrupt
	EA = 1; // allow all interrupts
	ES = 1; // enable serial interrupt
	
}


void serial_ISR() interrupt 4
{
	if(RI)
	{
		
	}
	else{
		TI = 0;
		txFlag = 1;
	}
}
