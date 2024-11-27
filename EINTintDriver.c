#include"header.h"
#include<lpc21xx.h>
extern int flag;
extern int flag1;
void EINT0_Handler(void) __irq{
		flag ^= 1;
	  flag1 = 1;
		EXTINT = 1;
		VICVectAddr = 0;
}
	
void config_vic_for_eint0(void){
	VICIntSelect = 0;
	VICVectCntl0 = 14 | (1<<5);
	VICVectAddr0 = (u32)EINT0_Handler;
	VICIntEnable = (1<<14);
}

void config_eint0(void){
	PINSEL1 |= 1;
	EXTMODE = 1;
	EXTPOLAR = 0;
}


