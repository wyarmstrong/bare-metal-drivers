//Blue LED Port: B
//Blue LED Pin: 7
#include <stdint.h>

#define PERIPH_BASE			(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOB_OFFSET 		(0x00000400UL)
#define GPIOB_BASE			(AHB1PERIPH_BASE + GPIOB_OFFSET)
#define RCC_OFFSET 			(0x3800UL)
#define RCC_BASE 			(AHB1PERIPH_BASE + RCC_OFFSET)
#define GPIOBEN				(1U<<1) // "shift 1 at position 1"
#define PIN7				(1u<<7)
#define LED_PIN				 PIN7
#define __IO				volatile


typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;

#define RCC					((RCC_TypeDef *) RCC_BASE)
#define GPIOB				((GPIO_TypeDef *) GPIOB_BASE)

int main(void)
{
	/* 1. Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOBEN;
	/* 2. Set PB7 as output pin*/
	GPIOB->MODER |= (1U<<14);
	GPIOB->MODER &=~(1U<<15);
	while(1)
	{
		/*Toggle PB7*/
		GPIOB->ODR ^= LED_PIN;
		for(int i=0; i<10000000; i++){}
	}
}
