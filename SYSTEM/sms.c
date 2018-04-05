#include "STC89C5xRC_RDP.h"
#include "MAIN.H"
#include "sms.h"


uchar code ATE0[]="ATE0\r\n";	//取消命令回显 

extern unsigned char xdata com2_cmd_buf[100];

uchar code SEND[]={0x1A,'\0'};		//发送短信
 /*	flag:第7位：置1，表示可以发读短信命令了
 	第6位：表示读短信命令已发送
	第5位：表示读取短信内容时，收到第二个回车换行符
	第4位：表示解析短信提醒命令时，收到逗号
	第3、2位：保留	
	第1位：表示读短信内容时收到第一个回车换行
	第0位：表示获取地址时，收到第一个空格	*/
//uchar flag2=0;		//标志位,一轮收发短信完毕时为F3
//extern uchar Position[5];	  //收到的短信存储的位置，默认短息地址是个位数，只有一位。
//extern uchar YN;			  //收到的短信内容，y或n，大小写均可
//extern uchar i;		   //存储地址时，用于表示Position中的位置。
//extern uchar recv_temp;	 //存储上一个收到的值
uchar code CCID[]="AT+CCID\r\n";	//查询sim卡是否插入
uchar code CREG[]="AT+CREG?\r\n"; 	//查询信号强度
uchar code CGATT[]="AT+CGATT=1\r\n";	// 
uchar code CGACT[]="AT+CGACT=1,1\r\n"; //

uchar code CIPSTART[]="AT+CIPSTART=\"TCP\",\"api.heclouds.com\",80\r\n";
uchar code CIPSEND[]="AT+CIPSEND\r\n";
uchar code CIPCLOSE[]="AT+CIPCLOSE\r\n";
//新建传感器
uchar code POST[]="POST /devices/17706707/datapoints HTTP/1.1\r\napi-key:X6gNMI=4KPqDDLuHNLR40rS=9nY=\r\nHost:api.heclouds.com\r\nContent-Length:";
unsigned int POST_num = 58;
uchar code POST2[]="\r\n\r\n{\"datastreams\":[{\"id\":\"001\",\"datapoints\":[{\"value\":\"";
//string POST_name = conghun2;
uchar code POST3[]="\"}]}]}\r\n";
//如果发送的是缺货提示而不是刷卡记录，区别体现在id的编号上：
uchar code POST4[]="\r\n\r\n{\"datastreams\":[{\"id\":\"002\",\"datapoints\":[{\"value\":\"";


void delay(uint ms)// 延时子程序 ,delay(1)大约0.09s
{
    uint i;
    while(ms--)
    {
        for(i=0;i<30000;i++);
    }
}



void Print_Char(uchar ch)//发送单个字符
{
    S2BUF=ch; //送入缓冲区
    while((S2CON&0X02)!=0X02); //等待发送完毕
    S2CON &= 0XFD; //软件清零
}

//void Print_Str(uchar *str)//串
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
	//取消命令回显，多发几次
	

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

	//查看手机号
	
	for(i=0;i<9;i++)
		Print_Char(CCID[i]);
	while(com2_cmd_buf[0]!='O');
	com2_cmd_buf[0]=' ';
	com2_cmd_buf[1]=' ';

	//查看信号强度
	
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


void Init_UART2(void)//串口初始化、定时器初始化
{
    //Baud=22118400/12/4/(65536-T2H,T2L)
	S2CON = 0x50 ;  //S2CON: serail mode 0, 8-bit UART, enable ucvr
    //UART为模式0，8位数据，允许接收
    T2H = 0xFF ;   //Baud=115200(A6的默认波特率): fosc=22.1184MHz
    T2L=0xFC;
    IE2 |= 0x01 ;     //Enable Serial Interrupt
    AUXR &= 0XF3 ;       // timer 2 to be timer but not counter；and use 8051 speed
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
		Print_Str(CMGF); //PDU格式，以发送中文短信
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



