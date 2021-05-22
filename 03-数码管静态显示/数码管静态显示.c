#include "reg52.h"


//�������úò����ٱ䣬���ñ����ʽ�����ڴ�
unsigned char code SMG_Duanma[18] = 
   {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
    0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
    0xbf,0x7f};
		
void Delay(unsigned int t)
{
	while(t--);
	while(t--);
}

void InitHC138(unsigned char n)
{
	switch(n)
	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80;
		  break;
		case 5:
			P2 = (P2 & 0x1f) | 0xa0;
		  break;
		case 6:
			P2 = (P2 & 0x1f) | 0xc0;
		  break;
		case 7:
			P2 = (P2 & 0x1f) | 0xe0;
		  break;
	}	
}

void ShowSMG_Bit(unsigned char dat, unsigned pos)
{
	InitHC138(6);  //����ܵ�λ��
	P0 = 0x01 << pos;
	InitHC138(7);  //����ܵ�����
	P0 = dat;
}

void SMG_Static()
{
  char i,j;  //λ��,����λѡ��
	for(i = 0; i < 8; i++)
	{
		for(j = 0;j < 10; j++)
		{
			ShowSMG_Bit(SMG_Duanma[j],i);
			Delay(60000);
		}
	}
  
	for(j = 0;j < 16; j++)
	{
		InitHC138(6);  //����ܵ�λ��
		P0 = 0xff;
		InitHC138(7);  //����ܵ�����
		P0 = SMG_Duanma[j];
		Delay(600000000);
		Delay(600000000);
		Delay(600000000);
		Delay(600000000);
	}
	
}

void main()
{
	
	while(1)
	{
		SMG_Static();
	}
}