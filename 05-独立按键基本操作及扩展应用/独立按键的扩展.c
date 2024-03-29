#include"reg52.h"

sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

sbit L1 = P0^0;
sbit L2 = P0^1;
sbit L3 = P0^2;
sbit L4 = P0^3;
sbit L5 = P0^4;
sbit L6 = P0^5;


void SelctHC573(unsigned char channel)
{
	switch (channel)
	{
		case 4:
			P2=(P2 & 0x1f) | 0x80;
		break;
		case 5:
			P2=(P2 & 0x1f) | 0xa0;
		break;
		case 6:
			P2=(P2 & 0x1f) | 0xc0;
		break;
		case 7:
			P2=(P2 & 0x1f) | 0xe0;
		break;
	}
}



void DelayK(unsigned char t)
{
	while(t--);
}

unsigned char state_k = 0;  //定义一个状态变量
void ScanKeys_Alone()
{
	if(S7==0)
	{
		DelayK(100);
		if(S7==0)
		{
			if(state_k==0)
			{
				L1=0;    //点亮L1
				state_k = 1;
			}
			else if(state_k == 1)
			{
				L1=1;    //关灯
				state_k = 0;
			}
			while(S7==0);  //避免多次按键导致L灯闪烁
		}		
	}
	
	if(S6==0)
	{
		DelayK(100);
		if(S6==0)
		{
			if(state_k==0)
			{
				L2 = 0;
				state_k = 2;
			}
			else if(state_k==2)
			{
				L2 = 1;
				state_k = 0;
			}
			while(S6==0);
		}
	}
	
	if(S5==0)
	{
		DelayK(100);
		if(S5==0)
		{
			if(state_k==1)
			{
				L3=0;
				while(S5==0);
				L3=1;
			}
			else if(state_k==2)
			{
				L5=0;
				while(S5==0);
				L5=1;
			}
		}
	}
	
	if(S4==0)
	{
		DelayK(100);
		if(S4==0)
		{
			if(state_k==1)
			{
				L4=0;
				while(S4==0);
				L4=1;
			}
			else if(state_k==2)
			{
				L6=0;
				while(S4==0);
				L6=1;
			}
		}
	}
	
}



void main()
{
	SelctHC573(4);
	while(1)
	{
		ScanKeys_Alone();
	}
}