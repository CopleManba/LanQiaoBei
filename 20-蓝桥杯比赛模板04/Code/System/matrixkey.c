#include"matrixkey.h"   

/***************************************************
*���ж���ʵ�־������
****************************************************/
bit keyflag = 0;   					// keyflagΪ1���ǰ��°�����0����
unsigned char keyvalue = 0;	// �����ֵ
void MatrixKeyScan()
{
	unsigned char kx=0,ky=0,i,j;
	if(keyflag == 0)  // û�а���ʱһֱɨ��
	{
		P3=(P3&0xc0)|0x0f;P42=0;P44=0;
		for(i=0;i<=3;i++)
		{
			if((	P3&(0x01<<i)) != (0x01<<i))
				ky=i+1;
		}
		
		P3=(P3&0xc0)|0x30;P42=1;P44=1;
		
	  for(j=0;j<=1;j++)
		{
			if((P3&(0x10<<j)) != (0x10<<j))
				kx=4-j;
		}
		if(!P42|!P44)
		{
			if(P42==0) kx=2;
			if(P44==0) kx=1;
		}
		
	}
	if(kx==0)  // �ų�û�а������¾ͼ���keyvalue�Ŀ���
	{
		keyflag=0;
	}
	else
	{
		keyvalue = kx+(ky-1)*4;
		keyflag=1; 
	}
	 
}


//void MatrixKeyScan()
//{
//	unsigned char kx=0,ky=0;
//	if(keyflag == 0)  // û�а���ʱһֱɨ��
//	{
//		P3=(P3&0xc0)|0x0f;P42=0;P44=0;
//		if(!P30|!P31|!P32|!P33)
//		if((P3&0x0f)!=0x0f)
//		{
//			if(P30==0) ky=1;
//			if(P31==0) ky=2;
//			if(P32==0) ky=3;
//			if(P33==0) ky=4;
//			
//	

//		}
//	
//		P3=(P3&0xc0)|0x30;P42=1;P44=1;
//		if(!P34|!P35|!P42|!P44)
//		{
//			if(P34==0) kx=4;
//			if(P35==0) kx=3;
//			if(P42==0) kx=2;
//			if(P44==0) kx=1;
//		}
//		
//	}	
//	if(kx==0)  // �ų�û�а������¾ͼ���keyvalue�Ŀ���
//	{
//	
//		keyflag=0;
//	}
//	else
//	{
//		keyvalue = kx+ky*4-4;
//		keyflag=1; 
//	}
//	 
//}

/*****************************************************/

/*****************************************************
*��������
******************************************************/
void KeyEliminatBuffet()
{
	Delayms(10);
	while(!(P34&P35&P42&P44));

	Delayms(10);
}

//void MatrixKeyScanNi()  //������ɨ��
//{
//	unsigned char kx=0,ky=0,i,j;
//	P3=(P3&0xc0)|0x0f;P42=0;P44=0;
//	for(i=0;i<=3;i++)
//	{
//		if((	P3&(0x01<<i)) != (0x01<<i))
//			ky=i+1;
//	}
//		
//	P3=(P3&0xc0)|0x30;P42=1;P44=1;
//		
//	for(j=0;j<=1;j++)
//	{
//		if((P3&(0x10<<j)) != (0x10<<j))
//			kx=4-j;
//	}
//	if(!P42|!P44)
//	{
//		if(P42==0) kx=2;
//		if(P44==0) kx=1;
//	}
//		
//	if(kx==0)  // �ų�û�а������¾ͼ���keyvalue�Ŀ���
//	{
//		keyflag=0;
//	}
//	else
//	{
//		keyvalue = kx+(ky-1)*4;
//		keyflag=1; 
//	}
//	 
//}
