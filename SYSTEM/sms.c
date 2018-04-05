#include "STC89C5xRC_RDP.h"
#include "MAIN.H"
#include "sms.h"


uchar code ATE0[]="ATE0\r\n";	//ȡ��������� 

extern unsigned char xdata com2_cmd_buf[100];

uchar code SEND[]={0x1A,'\0'};		//���Ͷ���
 /*	flag:��7λ����1����ʾ���Է�������������
 	��6λ����ʾ�����������ѷ���
	��5λ����ʾ��ȡ��������ʱ���յ��ڶ����س����з�
	��4λ����ʾ����������������ʱ���յ�����
	��3��2λ������	
	��1λ����ʾ����������ʱ�յ���һ���س�����
	��0λ����ʾ��ȡ��ַʱ���յ���һ���ո�	*/
//uchar flag2=0;		//��־λ,һ���շ��������ʱΪF3
//extern uchar Position[5];	  //�յ��Ķ��Ŵ洢��λ�ã�Ĭ�϶�Ϣ��ַ�Ǹ�λ����ֻ��һλ��
//extern uchar YN;			  //�յ��Ķ������ݣ�y��n����Сд����
//extern uchar i;		   //�洢��ַʱ�����ڱ�ʾPosition�е�λ�á�
//extern uchar recv_temp;	 //�洢��һ���յ���ֵ
uchar code CCID[]="AT+CCID\r\n";	//��ѯsim���Ƿ����
uchar code CREG[]="AT+CREG?\r\n"; 	//��ѯ�ź�ǿ��
uchar code CGATT[]="AT+CGATT=1\r\n";	// 
uchar code CGACT[]="AT+CGACT=1,1\r\n"; //

uchar code CIPSTART[]="AT+CIPSTART=\"TCP\",\"api.heclouds.com\",80\r\n";
uchar code CIPSEND[]="AT+CIPSEND\r\n";
uchar code CIPCLOSE[]="AT+CIPCLOSE\r\n";
//�½�������
uchar code POST[]="POST /devices/17706707/datapoints HTTP/1.1\r\napi-key:X6gNMI=4KPqDDLuHNLR40rS=9nY=\r\nHost:api.heclouds.com\r\nContent-Length:";
unsigned int POST_num = 58;
uchar code POST2[]="\r\n\r\n{\"datastreams\":[{\"id\":\"001\",\"datapoints\":[{\"value\":\"";
//string POST_name = conghun2;
uchar code POST3[]="\"}]}]}\r\n";
//������͵���ȱ����ʾ������ˢ����¼������������id�ı���ϣ�
uchar code POST4[]="\r\n\r\n{\"datastreams\":[{\"id\":\"002\",\"datapoints\":[{\"value\":\"";


void delay(uint ms)// ��ʱ�ӳ��� ,delay(1)��Լ0.09s
{
    uint i;
    while(ms--)
    {
        for(i=0;i<30000;i++);
    }
}



void Print_Char(uchar ch)//���͵����ַ�
{
    S2BUF=ch; //���뻺����
    while((S2CON&0X02)!=0X02); //�ȴ��������
    S2CON &= 0XFD; //�������
}

//void Print_Str(uchar *str)//��
//{
//    while(*str!='\0')
//    {
//        Print_Char(*str);
//       //for(i=0;i<200;i++); //delayl(2);
//        str++;
//    }

//}  
/*void get_sms(unsigned char the_term)
{
	uchar i;
	for(i=0;i<8;i++)
		Print_Char(CMGR[i]);
	Print_Char(the_term);
	Print_Char(13);
	Print_Char(10);
}*/
/*void dele_sms(unsigned char the_term)
{
	uchar i;
	for(i=0;i<8;i++)
		Print_Char(CMGD[i]);
	Print_Char(the_term);
	Print_Char(13);
	Print_Char(10);
}*/
void init_gprs()
{
	uchar i;
	//ȡ��������ԣ��෢����
	

	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';
	for(i=0;i<6;i++)
		Print_Char(ATE0[i]);	
	delay(10);
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';
	for(i=0;i<6;i++)
		Print_Char(ATE0[i]);	
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	
	for(i=0;i<6;i++)
		Print_Char(ATE0[i]);	
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	//�鿴�ֻ���
	
	for(i=0;i<9;i++)
		Print_Char(CCID[i]);
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	//�鿴�ź�ǿ��
	
	for(i=0;i<10;i++)
		Print_Char(CREG[i]);
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	//
	
	for(i=0;i<12;i++)
		Print_Char(CGATT[i]);
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	//
	
	for(i=0;i<14;i++)
		Print_Char(CGACT[i]);
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	
}
void send_net()
{	
	
	
	

}


void Init_UART2(void)//���ڳ�ʼ������ʱ����ʼ��
{
    //Baud=22118400/12/4/(65536-T2H,T2L)
	S2CON = 0x50 ;  //S2CON: serail mode 0, 8-bit UART, enable ucvr
    //UARTΪģʽ0��8λ���ݣ��������
    T2H = 0xFF ;   //Baud=115200(A6��Ĭ�ϲ�����): fosc=22.1184MHz
    T2L=0xFC;
    IE2 |= 0x01 ;     //Enable Serial Interrupt
    AUXR &= 0XF3 ;       // timer 2 to be timer but not counter��and use 8051 speed
	AUXR |= 0X10 ;			  //timer 2 run
 
}

/*void  EncodeTele(uchar *t)		//?????????t????????F????????
{
	uint i,temp;

	for(i=0;i<12;i+=2)	//???????,????????
	{
		temp=*(t+i);	//
		*(t+i)=*(t+i+1);
		*(t+i+1)=temp;
	}
}

void EncodeMachine(uchar *c,uchar *n)	 //?????,*c???????????,*n??????????
{
	uchar i;
	for(i=0;i<9;i++)
	{
		*(c+i*4)='0';
		*(c+i*4+1)='0';
		*(c+i*4+2)='3';
		switch(*(n+i))
		{
			case 0:
					*(c+i*4+3)='0';break;
			case 1:
					*(c+i*4+3)='1';break;
			case 2:
					*(c+i*4+3)='2';break;
			case 3:
					*(c+i*4+3)='3';break;
			case 4:
					*(c+i*4+3)='4';break;
			case 5:
					*(c+i*4+3)='5';break;
			case 6:
					*(c+i*4+3)='6';break;
			case 7:
					*(c+i*4+3)='7';break;
			case 8:
					*(c+i*4+3)='8';break;
			case 9:
					*(c+i*4+3)='9';break;
			default: break;
					
		}

	}
}
 */

/*void Send(uchar i,uchar *t,uchar *c) //???????i????????????,*t?????????????,*c????????????
 { 
 		uchar j=0;
		for(j=0;j<13;j++)
		Print_Char(CMNI[j]);
	 
	    wait_send = 0x01;
	    while(wait_send);
		delay(40);
	 delay(40);
		Print_Str(CMGF); //PDU��ʽ���Է������Ķ���
	 wait_send = 0x01;
	    while(wait_send);
	 delay(40);
	 delay(40);
//	 delay(40);//120w count
//	 delay(40);
//	 delay(40);
//	 delay(40);
//	 delay(40);
//	 delay(40);
//	 
//	 delay(40);
//	 delay(40);
	 
	 
	 
		Print_Str(CMGS);//???????
	 delay(40);
	 delay(40);
	 delay(40);
	 delay(40);
	 delay(40);
	 delay(40);
	 delay(40);
	
	 
	  
		Print_Str(MS);
		Print_Str(t);
		Print_Str(MM1);
		
		Print_Str(c);
		Print_Str(MM2);
		
		switch(i)
		{	
			case 1:
				Print_Str("0031");break;
			case 2:
				Print_Str("0032");break; 
			case 3:
				Print_Str("0033");break; 
			
			case 4:
				Print_Str("0034");break; 
			default:
				break;
		}
	//	delay(4);

		Print_Str(ME);
		Print_Str(SEND);   //????
		delay(100);
   	
 } */
/*void SMS_Del_All()
{
 	uchar i;
			   
	uchar p[4]="0\r\n";

	for(i=0;i<5;i++)
	{
		p[0]+=1;
		Print_Str("AT+CMGD=");		  //????
		Print_Str(p);
		delay(50);	
	}
	delay(40);
	 delay(40);
	 delay(40);

	
 } */
 /*void message(uchar *tele,uchar *mach_num,uchar channel)   //t??????,c??????,i?????
 {
 	uchar j;
  	uchar telenum[13];	   // ??????????,?????
	uchar machinecode[37];	 //??????????,?????
	
		for(j=0;j<11;j++)	//???????,??????,????	   
		{
			telenum[j]=(*(tele+j)+0x30);
		}
		telenum[11]='F';	  
		telenum[12]='\0';		//?????
		machinecode[36]='\0'; //?????????????
	
		EncodeTele(telenum);		//??????
		EncodeMachine(machinecode,mach_num);	 //?????
		Send(channel,telenum,machinecode);	 //????
	
 } 	*/



