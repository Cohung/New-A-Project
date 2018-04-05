/*������������������˶�������֤�Ķ����ı�׼�����壬��RC531оƬ*/
#ifndef __MAIN_H
#define __MAIN_H
#define uchar unsigned char
#define uint unsigned int

/////////////////////////////////////////////////////////////////////
//�˿ڶ���
/////////////////////////////////////////////////////////////////////

//����оƬ����
sbit 	 sc_data 		=	 P4^7;
sbit 	 sc_rst 		=	 P4^5;
//����������
sbit     buzz       =    P2^7;
//sbit     flesh      =    P1^1;
sbit 	 RS       =    P2^3;
sbit 	 RW       =    P2^2;                      
sbit 	 E        =    P2^1; 

sbit     RST		=	 P1^2;
sbit     SCLK		=	 P1^4;
sbit 	 SDA		=	 P1^3;
//�û����ð���
sbit 	 SET		=	 P4^3;
sbit 	 TAB		=	 P3^4;
sbit 	 INC		=	 P3^2;
sbit 	 SUB		=	 P4^6;
//ͨ��ѡ�񰴼�
sbit     SCH1       =    P4^4;
//sbit 	 ch1 		= 	 P4^3;
//sbit 	 ch2 		= 	 P1^0;
//sbit 	 ch3 		=	 P3^1;
//sbit 	 ch4 		=	 P3^0;
//4·������(���ý�)
sbit     m1         =    P3^5;
sbit     m2         =    P1^5;
sbit     m3         =    P0^6;
sbit     m4         =    P0^7;
//�г̿��ش��㵽���ź�
sbit     pos1       =    P0^2;
//sbit     led        =    P1^1;

sbit     lcdak      =    P2^6;
//ȱ��ͨ����ȱ���ź����
sbit     out1       =    P4^0;
sbit  	 out2 		= 	 P4^1;
sbit     out3		=  	 P2^4;
sbit	 out4		=	 P2^5;
//LED�ƹ���������ź�
sbit     mled       =    P4^2;

/////////////////////////////////////////////////////////////////////
//��ʱ�����������ʶ���
/////////////////////////////////////////////////////////////////////


#define OSC_FREQ                22118400L	 
#define BOUND115200             256 - (OSC_FREQ/192L)/115200L   // 255
#define BOUND57600              256 - (OSC_FREQ/192L)/57600L    // 254
#define BOUND38400              256 - (OSC_FREQ/192L)/38400L    // 253
#define BOUND28800              256 - (OSC_FREQ/192L)/28800L    // 252
#define BOUND19200              256 - (OSC_FREQ/192L)/19200L    // 250
#define BOUND14400              256 - (OSC_FREQ/192L)/14400L    // 248
#define BOUND9600               256 - (OSC_FREQ/192L)/9600L     // 244
#define BOUND4800               256 - 24
#define RCAP2_50us              65536L - OSC_FREQ/240417L
#define RCAP2_1ms               65536L - OSC_FREQ/12021L
#define RCAP2_10ms              65536L - OSC_FREQ/1200L
#define RCAP2_1s                65536L - OSC_FREQ/12L


#define               USER_STATE               0X0A
#define               USER_STATE_ERR           0X0B
#define               POS_ON				   0x0c



/////////////////////////////////////////////////////////////////////
//����ԭ��
/////////////////////////////////////////////////////////////////////
void InitializeSystem();                                   
                           
void DelayMs(unsigned int j);                                      
void Delay_50us(unsigned char j);                                  


void BEEP(unsigned int i);

void Ini_UART(void);


#endif


	


