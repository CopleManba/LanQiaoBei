#include"main.h"


void main()
{
	Init_Timer0();
	while(1)
	{
		if(keyflag==1)  // �жϰ�����־λ
		{
			KeyEliminatBuffet();
			Display_Buffer_Change(0,0,0,0,0,0,keyvalue/10,keyvalue%10);
			keyflag=0;    // ��־λ���㣬���¿�ʼɨ��
		}
//		MatrixKeyScanNi();
//		Display_Buffer_Change(0,0,0,0,0,0,keyvalue/10,keyvalue%10);
	}
}