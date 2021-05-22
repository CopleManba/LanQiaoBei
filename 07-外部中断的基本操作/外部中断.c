#include"reg52.h"

sbit L1 = P0^0;
sbit L8 = P0^7;

void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2&0x1f)|0x80;
			break;
		case 5:
			P2=(P2&0x1f)|0xa0;
			break;
		case 6:
			P2=(P2&0x1f)|0xc0;
			break;
		case 7:
			P2=(P2&0x1f)|0xe0;
			break;
	}
	
}

void Delay(unsigned int t)
{
	while(t--);
}

void Working()
{
	SelectHC573(4);   //��ѡ������
	L1=0;
	Delay(100000000);
	Delay(100000000);
	L1=1;
	Delay(100000000);
	Delay(100000000);
}

////�жϷ�1
//void Init_INT0()//�жϳ�ʼ��
//{
//	IT0 = 1; //ѡ���ж�0���½��ش�����=0���ǵ͵�ƽ������
//	EX0 = 1; //���ⲿʹ��
//	EA = 1;  //���ܿ���
//}

//void ServiceINT0()  interrupt 0
//{
//	L8 = 0;
//	Delay(100000000);
//	Delay(100000000);
//	Delay(100000000);
//	Delay(100000000);
//	L8 = 1;
//}

//�жϷ�2
void Init_INT0()//�жϳ�ʼ��
{
	IT0 = 1; //ѡ���ж�0���½��ش�����=0���ǵ͵�ƽ������
	EX0 = 1; //���ⲿʹ��
	EA = 1;  //���ܿ���
}

unsigned char state_INT = 0;  //�����жϱ�־����
void ServiceINT0()  interrupt 0
{
	state_INT = 1; //�жϲ���ʱ��־λ�䣬�жϷ������������飬��Ӱ������ʵʱ��
}

void LEDINT()
{
	if(state_INT == 1)
	{
		L8 = 0;
		Delay(100000000);
		Delay(100000000);
		Delay(100000000);
		Delay(100000000);
		L8 = 1;
	}
	state_INT = 0; //�����ж�״̬��0
}

void main()
{
	Init_INT0();  //�򿪿���
	while(1)
	{
		Working();
		LEDINT();    //���������ж�״̬������ÿ���жϲ�������������ִ��һ��Working֮��
	}
}