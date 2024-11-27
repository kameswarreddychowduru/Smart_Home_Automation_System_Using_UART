#include"header.h"
#include<lpc21xx.h>
extern unsigned char cmd;
extern int flag1;
void uart0_Handler(void) __irq {
	int r = U0IIR;
	r = (r>>1)&7;
	if(r == 2){
		cmd = U0RBR;
	}
	flag1 = 1;
	VICVectAddr = 0;
}

void config_vic_for_uart0(void){
	VICIntSelect = 0;
	VICVectCntl1 = 6 | (1<<5);
	VICVectAddr1 = (u32)uart0_Handler;
	VICIntEnable = (1<<6);
}

void config_uart0(void){
	U0IER = 1;
}

