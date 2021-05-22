#include"reg52.h"

//sfr AUXR= 0x8e;

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
		case 0:   //�������������ر�
			P2=(P2&0x1f)|0x00;
		break;
	}		
}

void InitSystem()  
{
	SelectHC573(5);  //�رշ������ͼ̵���
	P0=0x00;
	SelectHC573(4);
	P0=0xff;
}

//****************������ش���***************
void InitUart()
{
	TMOD = 0x20;
	TH1=0xfd;  //9600
	TL1=0xfd;
	TR1=1;   //Open Timer
	
	SCON=0x50; //���ô���λģʽ1(��λ�Զ���װģʽ)
	AUXR=0x00;
	
	ES=1;
	EA=1;
}

unsigned char command =0x00; //�����λ������ı���

void ServiceUart() interrupt 4
{
	if(RI==1)    //��Ƭ���ǽ�����ɽ�����ж�
	{
		command = SBUF; //����
		RI=0;  //��ʾλ����
	}
	
	
//	if(TI==1)  //������ɽ����жϵ�
//	{
//	}
}

void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);  //Ҫ��TI==1�ͷ��꼴����ѭ��
	TI=0; //�ֶ�����
}

void SendString(unsigned char *str)  //
{
	while(*str !='\0')
	{
		SendByte(*str++);
	}	
}

//*******************************************

void Working()   //������λ������
{
	if(command != 0x00)
	{
		switch(command & 0xf0)   //ѡ��command�ĸ���λ
		{
			case 0xa0:
				P0=(P0|0x0f)&(~command|0xf0);
				command=0x00;
			break;
			case 0xb0:
				P0=(  P0|0xf0)&((~command<<4)|0x0f);
				//P0=(~command|0x0f)&(P0|0xf0);
				command=0x00;
			break;
			case 0xc0:
				SendString("The System is Running...\r\n");
				command=0x00;   //commandҪ���㣬��Ȼ��main��while(1)ѭ��
			break;
		}
	}
}


void main()
{
	InitSystem();
	InitUart();
	SendString("Welcome to Cople!\r\n");
	while(1)
	{
		Working();
	}
}