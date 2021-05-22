#include"reg52.h"

sbit L1=P0^0;
sbit L8=P0^7;

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

/******************************************************************
 *�ú������ö�ʱ��0��ʱ0.5s������10��ÿ�ζ�ʱ50ms
 *
********************************************************************/
//��ʼ���������ö�ʱ��
void InitTimer0()
{
	TMOD=0x01;   //����λ����һ����д��
	TH0=(65535-50000)/256;  //16λ���ʱ��65.5ms,���ڴ���65.5ms�Ĳ��ö�ζ�ʱ
	TH0=(65535-50000)%256;
	
	ET0=1;
	EA=1;
	TR0=1;
}

//unsigned char count = 0;  //�����жϴ���->�õ�����0.5s
//unsigned char count1 = 0;   //�õ�����10s
//void ServiceTimer0() interrupt 1    //�жϷ�����(������ж�Դ��ע�ⶨ����0�ڵ�һ���ж�Դ)
//{
//	TH0=(65535-50000)/256;  //��װ��ֵ����Ϊ�޷��Զ���װ
//	TH0=(65535-50000)%256;
//	
//	count++;
//	count1++;
//	if(count == 10)  //50ms*10=500ms=0.5s
//	{
//		L1=~(L1);
//		count=0;
//	}
//	if(count1 == 100)  //50ms*100=5000ms=5s
//	{
//		L8 = ~(L8);
//		count1 = 0;
//	}
//}


//�Ż��жϷ�����
unsigned char count = 0;  
void ServiceTimer0() interrupt 1    //�жϷ�����(������ж�Դ��ע�ⶨ����0�ڵ�һ���ж�Դ)
{
	TH0=(65535-50000)/256;  //��װ��ֵ����Ϊ�޷��Զ���װ
	TH0=(65535-50000)%256;
	
	count++;
	if(count%10==0)  //100����10�ı���
	{
		L1=~(L1);
	}
	if(count == 100)  //50ms*100=5000ms=5s
	{
		L8 = ~(L8);
		count = 0;
	}
	
}

//������룬����д���жϷ���������
//void LEDWorking()
//{
//	if(count%10==0)  //100����10�ı���
//	{
//		L1=~(L1);
//	}
//	if(count == 100)  //50ms*100=5000ms=5s
//	{
//		L8 = ~(L8);
//		count = 0;
//	}
//}


void main()
{
	InitTimer0();
	while(1)
	{
		SelectHC573(4);
//		LEDWorking();
	}
}