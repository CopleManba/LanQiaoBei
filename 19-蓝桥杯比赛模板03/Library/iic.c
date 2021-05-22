/*
  ����˵��: IIC������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨ 8051��12MHz
  ��    ��: 2011-8-9
*/

#include "iic.h"


#define somenop Delay5us()   


#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//�������Ŷ���
sbit SDA = P2^1;  /* ������ */
sbit SCL = P2^0;  /* ʱ���� */


//������������
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	somenop;
	SDA = 0;
	somenop;
	SCL = 0;	
}

//����ֹͣ����
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	somenop;
	SDA = 1;
}

//Ӧ��λ����
void IIC_Ack(bit ackbit)
{
	if(ackbit) 
	{	
		SDA = 0;
	}
	else 
	{
		SDA = 1;
	}
	somenop;
	SCL = 1;
	somenop;
	SCL = 0;
	SDA = 1; 
	somenop;
}

//�ȴ�Ӧ��
bit IIC_WaitAck(void)
{
	SDA = 1;
	somenop;
	SCL = 1;
	somenop;
	if(SDA)    
	{   
		SCL = 0;
		IIC_Stop();
		return 0;
	}
	else  
	{ 
		SCL = 0;
		return 1;
	}
}

//ͨ��I2C���߷�������
void IIC_SendByte(unsigned char byt)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{   
		if(byt&0x80) 
		{	
			SDA = 1;
		}
		else 
		{
			SDA = 0;
		}
		somenop;
		SCL = 1;
		byt <<= 1;
		somenop;
		SCL = 0;
	}
}

//��I2C�����Ͻ�������
unsigned char IIC_RecByte(void)
{
	unsigned char da;
	unsigned char i;
	
	for(i=0;i<8;i++)
	{   
		SCL = 1;
		somenop;
		da <<= 1;
		if(SDA) 
		da |= 0x01;
		SCL = 0;
		somenop;
	}
	return da;
}

unsigned char PCF8591_ADC(unsigned char addr)  //���ص���0-255֮������֣�Ҫ���ѹҪ3*ֵ/256
{
	unsigned char dat;  //�������ݵı���
	//д����
	IIC_Start();  //IIC��ʼ����
	IIC_SendByte(0x90);   //����IIC��PCF8591��ַ��w
	IIC_WaitAck();    //�ȴ�Ӧ��
	
	IIC_SendByte(addr);  //ѡ��Ҫ����AIN��
	IIC_WaitAck(); 
	
	IIC_Stop();       //IIC���߿���
	
	//������
	IIC_Start();
	IIC_SendByte(0x91);  //R 
	IIC_WaitAck(); 
	dat=IIC_RecByte();
	IIC_Ack(0);  //��Ƭ��Ӧ��PF8591
	IIC_Stop();   
	
	return dat;
}


void PCF8591_DAC(unsigned char dat)  //DA
{
	IIC_Start();  //IIC��ʼ����
	IIC_SendByte(0x90);   //����IIC��PCF8591��ַ��w
	IIC_WaitAck();    //�ȴ�Ӧ��
	
	IIC_SendByte(0x40);  //����оƬ��������תģ����
	IIC_WaitAck(); 

	IIC_SendByte(dat);  //����8λ��ѹ���ݣ������Ǹ�����ɶ��
	IIC_WaitAck(); 
	IIC_Stop();   

}


unsigned char E2Prom_Read(unsigned char addr)  //e2prom��������
{
	unsigned char dat;  //�������ݵı���

	IIC_Start();  //IIC��ʼ����
	IIC_SendByte(0xa0);   //����IIC��AT24C02��ַ��w
	IIC_WaitAck();    //�ȴ�Ӧ��
	
	IIC_SendByte(addr);  //Ҫ�������ݵ�ַ
	IIC_WaitAck(); 
	
	IIC_Stop();       //IIC���߿���
	
	//������
	IIC_Start();
	IIC_SendByte(0xa1);  //R���� 
	IIC_WaitAck(); 
	dat=IIC_RecByte();
	IIC_Ack(0);  //��Ƭ��Ӧ��AT24C02
	IIC_Stop();   
	
	return dat;
}


void E2Prom_Write(unsigned char addr,dat)  //д��e2prom
{
	IIC_Start();  //IIC��ʼ����
	IIC_SendByte(0xa0);   //����IIC��AT24C02��ַ��w
	IIC_WaitAck();    //�ȴ�Ӧ��
	
	IIC_SendByte(addr);  //����оƬ������оƬ�ڴ洢��λ��
	IIC_WaitAck(); 

	IIC_SendByte(dat);  //���洢�����ݷ���оƬ
	IIC_WaitAck(); 
	IIC_Stop();   
}
