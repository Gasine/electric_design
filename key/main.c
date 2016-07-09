#include <msp430g2553.h>

/*
 * main.c
 */
unsigned int i,j,key,k,l=0,arr[4],keycode[16]={0x11,0x12,0x14,0x18,0x21,0x22,0x24,0x28,0x41,0x42,0x44,0x48,0x81,0x82,0x84,0x88};
unsigned char  num[16]={1,2,3,'+',4,5,6,'-',7,8,9,'*',0,0,0,'='};
void delay(int i)
{
	int j,k;
	for(j=0;j<i;j++)
	for(k=0;k<110;k++);
}


int main(void) {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P2DIR &= ~(BIT0+BIT1+BIT2+BIT3);
	P2REN |= (BIT0+BIT1+BIT2+BIT3);
	P2OUT &= ~( BIT0+BIT1+BIT2+BIT3);
	P1DIR |= (BIT4+BIT5+BIT6+BIT7);
	P1OUT =BIT4+BIT5+BIT6+BIT7;
	P2IE |= BIT0+BIT1+BIT2+BIT3;
	P2IES &=~(BIT0+BIT1+BIT2+BIT3);
	P2IFG &=~(BIT0+BIT1+BIT2+BIT3);

	__enable_interrupt();
	while(1);
	return 0;
}
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
//中断后想干的事写这里;
	delay(30);
	if((P2IN&0x0f)!=0){
	key = P2IN&0x0f;
	P1DIR &= ~(BIT4+BIT5+BIT6+BIT7) ;
	P1REN |= BIT4+BIT5+BIT6+BIT7;
	P2REN &= ~(BIT0+BIT1+BIT2+BIT3);
	P1OUT &=~(BIT4+BIT5+BIT6+BIT7);
	P2DIR |= BIT0+BIT1+BIT2+BIT3;
	P2OUT |= BIT0+BIT1+BIT2+BIT3;
	key = key|(P1IN&0xf0);
	for(i=0;i<16;i++){

		if(key==keycode[i]){
			j = i;
		}
	}
	arr[l] = num[j];
	l++;
	if(j==15){
		k = arr[0]+arr[2];
	}
//	if(j==5){
//		P2DIR |=BIT4;
//		P2OUT |=BIT4;
//	}
	}
	P2DIR &= ~(BIT0+BIT1+BIT2+BIT3);
	P1REN &= ~(BIT4+BIT5+BIT6+BIT7);
	P2REN |= (BIT0+BIT1+BIT2+BIT3);
	P2OUT &= ~( BIT0+BIT1+BIT2+BIT3);
	P1DIR |= (BIT4+BIT5+BIT6+BIT7);
	P1OUT =BIT4+BIT5+BIT6+BIT7;
	P2IFG &= ~(BIT0+BIT1+BIT2+BIT3);		//清中断
}
