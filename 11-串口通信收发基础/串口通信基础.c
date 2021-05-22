#include "reg52.h"
#include "stdio.h"

sfr AUXR=0x8e; //51��Ƭ��û��Ҫ���õ�ַ

sbit S7=P3^0;

unsigned char urdat;
unsigned char Adata=0;
void SendByte(unsigned char dat);

void Delay(unsigned char t)
{
	while(t--);
}

void KeyScan()
{
	
	if(S7==0)
	{
		Delay(100);
		if(S7==0)
		{
			Adata++;

			while(S7==0);
			SendByte(Adata);			
		}
	}
}


//���ڳ�ʼ������
void InitUart()
{
	TMOD = 0x20;  //ѡ��8λ�Զ���װ
	TH1=0xfd;  //���ֲ�
	TL1=0xfd;  //��װģʽ�¶���һ��
	
	TR1=1;
	SCON=0x50;
	AUXR=0x00;
	
	ES=1;
	EA=1;
		
}



//����ʱҪ�õ��жϷ�����
void ServiceUart() interrupt 4
{
	if(RI == 1)  //���ݽ�����ϣ�TI==1�������
	{
		RI=0;   //�������
		urdat=SBUF;  //����
		SendByte(urdat); //����֮��Ҫ����
	}
}

//��ѯ����
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}

void SendStr(char *s)
{
	while(*s)
	{
		SendByte(*s++);
	}
}

void main()
{
	unsigned int tim=0;
	unsigned int i=0;
	unsigned char str[35];
	InitUart();
//	SendByte(0x5a);
//	SendByte(0xa5);
	
	while(1)
	{
		tim++;
//		KeyScan();
		sprintf(str,"%d",tim);
		SendStr(str);
		for(i=0;i<60000;i++);
//		for(i=0;i<60000;i++);
//		for(i=0;i<60000;i++);
//		for(i=0;i<60000;i++);
		
	}
}