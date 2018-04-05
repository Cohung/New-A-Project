#ifndef __SMS_H
#define __SMS_H


void delay(unsigned int ms);
void Print_Char(unsigned char ch);
void Print_Str(unsigned char *str);
void Init_UART2(void);
uchar ChangeChar(uchar in);
void send_net();
//void dele_sms(unsigned char the_term);
void init_gprs();
//void SMS_Del_All();
void message(uchar *tele,uchar channel);

#endif
