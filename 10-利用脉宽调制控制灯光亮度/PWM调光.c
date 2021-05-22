#include"reg52.h"

sbit L1=P0^0;
sbit S7=P3^0;

unsigned char cnt=0;
unsigned char pwm_duty=0;

void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2&0x1f)|0x80;
		break;
	}
}

//*****************��ʱ����غ���*****************
void Init_Timer0()
{
	TMOD=0x01;    //ѡ16λ��װ��8λ�Զ���װ����
	TH0=(65535-100)%256;  //100us���ж�
	TL0=(65535-100)/256;

	ET0=1;
	EA=1;
//	TR0=1;  //���Դ򿪣������ڱ�������ڲ����������ʱ�ٴ�
}

void ServiceTimer0() interrupt 1
{
	TH0=(65535-100)%256;  
	TL0=(65535-100)/256;
	
	cnt++;
	if(cnt<=pwm_duty)
	{
		L1=0;
	}
	else if(cnt<100)
	{
		L1=1;
	}
	else if(cnt==100)
	{
		L1=0;
		cnt=0;
	}
}



//*************************************************


//************************������غ���**************
void Delay(unsigned char t)
{
	while(t--);
}

unsigned char state=0;

void KeyScan()
{
	if(S7==0)
	{
		Delay(100);
		if(S7==0)
		{
			switch(state)
			{
				case 0:     //���°����������Ҷ�ʱ���򿪣�����λ10%
					L1=0;
					TR0=1;
					pwm_duty=10;
				  state=1;    //״̬1
				break; 
				
				case 1:
					pwm_duty=50;
					state=2;
				break;
				
				case 2:
					pwm_duty=90;
					state=3;
				break;
				
				case 3:
					L1=1;  //�ص�
					TR0=0; //�ض�ʱ��
					state=0;
				break;
			}
			while(S7 == 0);
		}
	}
}

//************************************************





void main()
{
	SelectHC573(4);
	Init_Timer0();
	while(1)
	{
		KeyScan();
	}
}