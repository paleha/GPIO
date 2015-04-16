#include "stm32f1xx.h" // File name depends on device used
#include "Lib.h"
#define HSE_STARTUP_TIMEOUT   ((uint16_t)0x0500) /*!< Time out for HSE start up */
uint32_t volatile msTicks; // Counter for millisecond Interval
void SetSysClockToHSE(uint32_t aHSEValue)
{

  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

  if (HSEStatus == (uint32_t)0x01)
  {


    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE; //ok
    if (aHSEValue <= 24000000)
		{
			/* Flash 0 wait state */
			FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY); //...11111000 ok 0 wait
		}
		else 
		{
      if 	(aHSEValue > 24000000 && aHSEValue <= 48000000 )	
			{ /* Flash 1 wait state */ 
        FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0; /* 001 */
			}	
			else 
			{
				if 	(aHSEValue > 48000000 )	
				{ /* Flash 2 wait state */ 
					FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1; /* 010 */
				}
				else {;}	
		  }
		}
 
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
    
    /* Select HSE as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;    

    /* Wait till HSE is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }  
}



void SysTick_Handler (void) { // SysTick Interrupt Handler
msTicks++; // Increment Counter
}

// Set the SysTick interrupt interval to 1ms 
void SysTick_Init (void) 
{ if (SysTick_Config (SystemCoreClock / 1000)) 
		{; // handle error 
			} 
} 

// Wait until msTick reaches 0 
void Delay (uint32_t aPause) 
{ 
	msTicks = 0; // Reset counter 
	while (msTicks < aPause); // Wait 500ms 
}
