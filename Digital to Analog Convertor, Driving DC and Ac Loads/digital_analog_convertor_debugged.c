#include<reg52.h>
#include<intrins.h>
sbit Scl = P2^1;
sbit Sda = P2^0;

void icc_start();
void icc_send(char _data);
void icc_ack(); 
void icc_stop();
void DAC(char _byte); 

void delay(char x);// delay function
	
void main()
{
	int num = 0;
	 while(1)
	 {
		 DAC(num);
		 num++;
		 delay(10);
		 if(num==256)
		 {
				num = 0;
		 }
	 }
}
void icc_start()
{
	Scl = 1;
	_nop_();
	Sda = 1;
	_nop_();
	Sda = 0;
}
void icc_send(char _data)
{
	char oneByte = 8;
	char temp = 0x80; // 1000 0000
	//1000 0000
	//0XXX XXXX
	//1XXX XXXX
	
	while(oneByte)
	{
		Scl = 0;
		if((temp&_data)==0)
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
		_nop_();  //added line 1
		Scl = 0;	//added line 1
		
		_data = _data<<1;
		oneByte--;
	}
	
}
void icc_ack()
{
	//Sda = 0;
	Scl = 0;
	_nop_();
	Scl = 1;
	_nop_();
	Scl = 0;
}
void icc_stop()
{
	Scl = 1;
	_nop_();
	Sda = 0;
	_nop_();
	Sda = 1;
}

void DAC(char _byte)
{
	icc_start();
	icc_send(0x90); // write to D/A convertor
	icc_ack();
	icc_send(0x40); //enable analog out
	icc_ack();
	icc_send(_byte); // send data
	icc_ack();
	icc_stop();
}	
	
void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}