#include<LPC21XX.H>
#include"header.h"
void lcd_data(unsigned char data){
unsigned int temp;
IOCLR1 = 0xfe<<16;
temp = (data&0xf0)<<16;
IOSET1 = temp;
IOSET1 = 1<<17;
IOCLR1 = 1<<18;
IOSET1 = 1<<19;
delay_ms(2);
IOCLR1 = 1<<19;

IOCLR1 = 0XFE<<16;
temp = (data&0x0f)<<20;
IOSET1 = temp;
IOSET1 = 1<<17;
IOCLR1 = 1<<18;
IOSET1 = 1<<19;
delay_ms(2);
IOCLR1 = 1<<19;
}

void lcd_cmd(unsigned char cmd){
unsigned int temp;
IOCLR1 = 0XFE<<16;
temp = (cmd&0xf0)<<16;
IOSET1 = temp;
IOCLR1 = 1<<17;
IOCLR1 = 1<<18;
IOSET1 = 1<<19;
delay_ms(2);
IOCLR1 = 1<<19;

IOCLR1 = 0XFE<<16;
temp = (cmd&0xf)<<20;
IOSET1 = temp;
IOCLR1 = 1<<17;
IOCLR1 = 1<<18;
IOSET1 = 1<<19;
delay_ms(2);
IOCLR1 = 1<<19;
}

void lcd_init(){
IODIR1 = 0XFE<<16;
IOCLR1 = 1<<19;
PINSEL2 =0X0;
lcd_cmd(0x02);
lcd_cmd(0x03);
lcd_cmd(0x28);
lcd_cmd(0x0e);
lcd_cmd(0x01);
}

void lcd_string(char *p){
while(*p){
lcd_data(*p);
p++;
}
}

void lcd_integer(int num){
int a[10],i=0;
if(num == 0)
lcd_data('0');

if(num<0){
lcd_data('-');
num = -num;
}

while(num){
a[i] = num%10 + 48;
num = num/10;
i++;
}
for(i--;i>=0;i--)
lcd_data(a[i]);

}

void lcd_float(float num){
int i,j;
i = num;
lcd_integer(i);
lcd_data('.');
j = (num - i)*100;
if(j<0)
j = -j;
if((num-i) < 1)
lcd_data('0');

lcd_integer(j);
}

void lcd_cgram(){
	int a[8] = {0x0,0xa,0xa,0x0,0x0,0x11,0xe,0x0};
	lcd_cmd(0x40);
	for(int i=0;i<8;i++)
	lcd_data(a[i]);
}
	
