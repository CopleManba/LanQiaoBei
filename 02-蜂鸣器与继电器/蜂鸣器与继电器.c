/*
��ˮ�������£����ε���LED�Ƽ̵������ϣ�����Ϩ��LED�Ʒ���������
*/

#include"reg52.h"

sbit  HC138_A = P2^5;
sbit  HC138_B = P2^6;
sbit  HC138_C = P2^7;

void Delay(unsigned int t);
void LEDRunning();
void InitSystem();
void Relay_spdt();
void Buzzer();

void Delay(unsigned int t)
{
	while(t--);
	while(t--);
}


//ѡ��HC138����˿ڵĺ���
//void InitHC138(unsigned char n)
//{
//	switch(n)
//	{
//		case 4:
//			HC138_A = 0;
//			HC138_B = 0;
//			HC138_C = 1;   //P2 = (P2 & 0x1f) | 0x80;
//		break;
//		case 5:
//			HC138_A = 1;
//			HC138_B = 0;
//			HC138_C = 1;
//		break;
//		case 6:
//			HC138_A = 0;
//			HC138_B = 1;
//			HC138_C = 1;
//		break;
//		case 7:
//			HC138_A = 1;
//			HC138_B = 1;
//			HC138_C = 1;
//		break;
//	}	
//}

//λ�����Ż�
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



//�Ż�����������
void OutPutP0(unsigned char channel, unsigned char dat)
{
	InitHC138(channel);
	P0=dat;
}

//�ص��޹ص�����
void InitSystem()
{
	OutPutP0(5,0x00);
}

void LEDRunning()
{
	int i;
	for(i=0;i<3;i++)
	{
		OutPutP0(4,0x00);
		Delay(60000);
		OutPutP0(4,0xff);
		Delay(60000);	
	}
	for(i=1;i<=8;i++)
	{
		OutPutP0(4,(0xff<<i));
		Delay(60000);
		
	}
	
	Relay_spdt();
	
	
	InitHC138(4);   //�ٴ�ѡ��Y4	

	for(i=1;i<=8;i++)
	{
		
		OutPutP0(4,~(0xff<<i));
		Delay(60000);
	}
	
	Buzzer();	
}


//�̵�������
void Relay_spdt()
{
	OutPutP0(5,0x10);
	Delay(60000);
	OutPutP0(5,0x00);
}

//����������
void Buzzer()
{
	OutPutP0(5,0x40);
	Delay(60000);
	OutPutP0(5,0x00);
}


void main()
{
	InitSystem();
	while(1)
	{
		LEDRunning();
	}
}



