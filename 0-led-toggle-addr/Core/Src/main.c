//Blue LED Port: B
//Blue LED Pin: 7
#define PERIPH_BASE			(0x40000000UL)

#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOB_OFFSET 		(0x00000400UL)
#define GPIOB_BASE			(AHB1PERIPH_BASE + GPIOB_OFFSET)

#define RCC_OFFSET 			(0x3800UL)
#define RCC_BASE 			(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET		(0x30UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define GPIOBEN				(1U<<1) // "shift 1 at position 1"

#define MODE_R_OFFSET		(0x00UL)
#define GPIOB_MODE_R		(*(volatile unsigned int *)(GPIOB_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14UL)
#define GPIOB_OD_R			(*(volatile unsigned int *)(GPIOB_BASE + OD_R_OFFSET))

#define PIN7				(1u<<7)
#define LED_PIN				 PIN7
/*
* (1U<<14)	//Set bit 14 to 1
* 	&=~(1U<<15) //Set bit 15 to 0*/
int main(void)
{
	/* 1. Enable clock access to GPIOA*/
	RCC_AHB1EN_R |= GPIOBEN;
	/* 2. Set PB7 as output pin*/
	GPIOB_MODE_R |= (1U<<14);
	GPIOB_MODE_R &=~(1U<<15);

	while(1)
	{
		/*Toggle PB7*/
		GPIOB_OD_R ^= LED_PIN;
		for(int i=0; i<100000; i++){}
	}
}
