/*--------- * File LED.c *---*/ 
#include "stm32f1xx.h" // Device header 
// Initialize GPIO Prot 
void LED_Initialize (void) 
{ RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ; //RCC_APB2ENR_GPIOBEN; // Enable Port B clock 
	GPIOB->CRH |=  GPIO_CRH_MODE9_1; //  Port B.09.MODE= 10 2MHZ
	GPIOB->CRH &= ~GPIO_CRH_MODE9_0; //  Port B.09.MODE= 10 2MHZ
	GPIOB->CRH &= ~GPIO_CRH_CNF9; // Port B.09.CNF= 00

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ; // Enable Port C clock 
	GPIOC->CRL &= ~GPIO_CRL_MODE0; //  Port C.0  MODE= 00 
	GPIOC->CRL &= ~GPIO_CRL_CNF0_0; //  
	GPIOC->CRL |= GPIO_CRL_CNF0_1; // Port C.0 CNF= 10
  GPIOC->ODR |= GPIO_ODR_ODR0; // PULL-UP

} 
/* Turn LED on */ 
void LED_Off (void) 
{ GPIOB->BSRR = GPIO_BSRR_BS9; // LED on: set Port 
} 
	/* Turn LED off */ 
void LED_On (void) 
{ GPIOB->BRR = GPIO_BSRR_BS9; // LED off: clear Port 
}
