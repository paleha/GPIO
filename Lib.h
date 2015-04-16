#include <stdint.h>
void SetSysClockToHSE(uint32_t); //устанавливаем HSE в качестве источника тактирования В аргументе передаем частоту в Гц HSE.


//void SysTick_Handler (void); // SysTick Interrupt Handler

// Set the SysTick interrupt interval to 1ms 
void SysTick_Init (void);


// Wait until msTick reaches 0 
void Delay (uint32_t);
