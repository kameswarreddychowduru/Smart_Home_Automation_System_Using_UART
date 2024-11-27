#include<lpc21xx.h>
void uart0_init(unsigned int baud){
	unsigned int result = 0;
	int a[] = {15,60,30,15,15};
	unsigned int pclk = a[VPBDIV]*1000000;
	result = pclk/(16 * baud);
	PINSEL0 |= 5;
	U0LCR = 0X83;
	U0DLL = result&0xff;
	U0DLM = (result>>8)&0xff;
	U0LCR = 3;
}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data){
	U0THR = data;
	while(THRE == 0);
}

#define RDR (U0LSR&1)
unsigned char uart0_rx(void){
	while(RDR == 0);
	return U0RBR;
}

void uart0_tx_string(char *ptr){
	while(*ptr){
		U0THR = *ptr;
		while(THRE == 0);
		ptr++;
	}
}

	void uart0_binary(unsigned int temp){
	int n1,i;
	for(i=31;i>=0;i--){
		n1 = (temp>>i)&1;
		uart0_tx(n1 + 48);
	}
}

void uart0_hex(unsigned char temp){
	unsigned int n1,n2;
	n1 = temp&0xf;
	n2 = (temp>>4)&0xf;
	if(n1<= 9)
		n1 = n1 + 48;
	else
		n1 = n1 + 55;
	
	if(n2 <= 9)
		n2 = n2 + 48;
	else
		n2 = n2 + 55;
		
	uart0_tx_string("0x");
	uart0_tx(n2);
	uart0_tx(n1);
	}



	