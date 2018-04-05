#include "STC89C5xRC_RDP.h"
#include <string.h>
#include <intrins.h>
#include "main.h"
#include <absacc.h>
#include "SMS.H"
/*硬件功能及版本说明*/ 
/*


*/



unsigned char s = 0; //在中断函数中





unsigned int a;
unsigned int aa;//,set_long_time,set_long_time_flag;



uchar idata com_buf[173];//其实只需要接收172个字节。最后一个字节用来存储后续无用数据。
uchar recv_num;

//接收策略更新
uchar xdata com2_cmd_buf[100];
uchar com2_cmd_num=0;




void main( )
{    
 	
	  uchar del_1;
	  a = 0;
	  aa=0;

	
	
	 // InitializeSystem( );

	  Init_UART2();
	  EA = 1;
	  
	  ET0 = 1;
//	  ET1 = 1;
	


	  TMOD |= 0X01;
	  TH0 = 0Xc8;
	  TL0 = 0Xc0;	 
	for(del_1=0;del_1<100;del_1++)
		 DelayMs(200);
//	for(del_1=0;del_1<500;del_1++)
//		 DelayMs(200);
//	for(del_1=0;del_1<1000;del_1++)
//		 DelayMs(200);
//	for(del_1=0;del_1<500;del_1++)
//		 DelayMs(200);	 

	TR0 = 1;
	
	init_gprs();//init_sms();
    //	SMS_Del_All();
	BEEP(200);
while ( 1 )
{ 
			
		send_net();
	
}

}


void BEEP(unsigned int i)
{
    unsigned int k;
	k=i*45;		
	buzz = 0;
	
	
//	led =  0;	

	DelayMs(k);		
	buzz =1; 	

// 	led =  1;
   
}


/////////////////////////////////////////////////////////////////////
//延时子程序
/////////////////////////////////////////////////////////////////////
void DelayMs(unsigned int _MS)
{

while(_MS--)
 {
     //大致延时1ms
     Delay_50us(245);
	 Delay_50us(245);
 }
}
void Delay_50us(unsigned char _50us)
{
 while(--_50us);
}




void T0_time() interrupt 1
{
	TH0 = 0Xc8;
	TL0 = 0Xc0;

	a++;
	aa++;

	
	

if(aa == 250){
	aa = 0;
	//update_logo = 0;
	}	
//if(aa%50 == 0)
//	ask_it = 1;
	if(a == 40)
	{	
		a = 0;
	}

}
void ser() interrupt 4	   //串口中断服务
{
	uchar recv;	
	recv = SBUF;
	
	com_buf[recv_num]=recv;
	recv_num++;
	if(recv_num==173)
		recv_num=172;
	
	RI=0;
	
}

void ser2() interrupt 8	   //串口中断服务
{

//com2_buf[12];com2_cmd_buf[100]
	if(S2CON & 0X01)
	{
		S2CON &= 0XFE;
	
		com2_cmd_buf[com2_cmd_num] = S2BUF;
		com2_cmd_num++;
			
		
		
		if(com2_cmd_num>1)
		{
			if((com2_cmd_buf[com2_cmd_num-1] == 10)&&(com2_cmd_buf[com2_cmd_num-2] == 13))
			{
			
			
//			if((wait_send == 0x01)&& com2_cmd_num>=4)  //保证数组不越界，并且注意有些回复是只有回车换行
//			{
//					//BEEP(200);
//					if((com2_cmd_buf[com2_cmd_num-4]=='O') && (com2_cmd_buf[com2_cmd_num-3]=='K'))
//						wait_send = 0;
//			}
			com2_cmd_num=0;
			}
		 }
		
		
		
	}
	
}




