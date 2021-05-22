#include"interrupt.h"

unsigned int cnt=0;
unsigned char t_s=0,t_m=0,t_h=0;
bit timer0_flag=0;   //�жϱ�־λ

void Init_Timer0()		//1ms@11.0592MHz
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;		    //16λ�Զ�����ģʽ
	TL0 = 0xCD;		
	TH0 = 0xD4;		
	TF0 = 0;		        //�����־λ
	TR0 = 1;	          //�򿪶�ʱ��0
	
	ET0=1;
	EA=1;
}


void Serve_Timer0() interrupt 1
{
	cnt++;
	if(cnt==1000)
	{
		t_s++;
		cnt=0;
	}
	if(t_s==60)
	{
		t_m++;
		t_s=0;
	}
	if(t_m==60)
	{
		t_h++;
		t_m=0;
	}
	Display_SMG_DT();
	
	timer0_flag=1;
}