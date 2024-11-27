#include"header.h"
#include<lpc21xx.h>
#define LED (1<<19)
#define FAN (1<<18)
#define BULB (1<<17)
#define SW1 ((IOPIN0>>14)&1)
#define SW2 ((IOPIN0>>15)&1)
#define SW3 ((IOPIN0>>16)&1)
int flag;
unsigned char cmd;
int flag1;
main(){
	
	IODIR0 = LED | FAN | BULB;
	IOSET0 = LED | FAN | BULB;
	uart0_init(9600);
	config_vic_for_eint0();
	config_eint0();
	config_vic_for_uart0();
	config_uart0();
	while(1){
		
		//bluetooth mode
		while(flag == 0){
			flag1=0;
			IOSET0 = LED;
			uart0_tx_string("\r\n\r\nMenu");
			uart0_tx_string("\r\na. Bulb ON \r\nb. Bulb OFF \r\nc. Fan ON \r\nd. Fan OFF \r\ne. Both ON \r\nf. Both OFF \r\nSelect option : ");
			while(flag1 == 0);
			if(flag == 1)
				break;
			uart0_tx(cmd);
			switch(cmd){
			case 'a' : IOCLR0 = BULB;
			break;
			case 'b' : IOSET0 = BULB;
			break;
			case 'c' : IOCLR0 = FAN;
			break;
			case 'd' : IOSET0 = FAN;
			break;
			case 'e' : IOCLR0 = BULB | FAN;
			break;
			case 'f' : IOSET0 = BULB | FAN;
			break;
			default : uart0_tx_string("\r\n invalid command");
			}
			//flag1 = 0;
		}
		
		//Manual Mode
		while(flag == 1){
			IOCLR0 = LED;
			if(SW1 == 0){
				while(SW1 == 0);
				if((IOPIN0>>17)&1)
					IOCLR0 = BULB;
				else
					IOSET0 = BULB;
			}
			
			if(SW2 == 0){
				while(SW2 == 0);
				if((IOPIN0>>18)&1)
					IOCLR0 = FAN;
				else
					IOSET0 = FAN;
			}
		}
}			
}
