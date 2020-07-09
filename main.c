#ifndef _NSC_MAIN_H
#define _NSC_MAIN_H

#include "stm32f10x.h"
/* #include "stm32l1xx.h" */
#include "nc_defines.h"

#define SYSTICK_COUNT_ENABLE 1
#define SYSTICK_INTERRUPT_ENABLE 2

volatile uint8_t BACKGROUND = 0;                 /* Declare volatile to force compiler to generate code that rereads variable stored in memory & not just in registers */
volatile uint8_t ADC_VAR = 0;
volatile uint8_t SYSTICK= 0;
volatile uint32_t Temp = 0;
volatile uint32_t msTicks = 0;
#endif

void init_ADC (void);

int main (void)
{
    SysTick->VAL = 0x9000;
    SysTick->LOAD = 0x9000;
    SysTick->CTRL = SYSTICK_INTERRUPT_ENABLE|SYSTICK_COUNT_ENABLE;
    init_ADC();
    ADC1->CR1 |= (1UL << 5);          			     /* Enable EOC Interrupt */
    NVIC->ISER[0] = (1UL << 18);
    ADC1->CR2 |= (1UL << 0);								     /* ADC enable */  
/*	
	  NVIC->IP[18] = (2<<4);
	  SCB->SHP[11] = (3<<4);
*/
/*
	  Temp  =  SCB->AIRCR;                                                   
	  Temp &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);             
	  Temp  =  (Temp|((uint32_t)0x5FA << SCB_AIRCR_VECTKEY_Pos) |(5 << 8));                                     
	  SCB->AIRCR =  Temp;
*/
    while(1){
        BACKGROUND = 1;													/* Set the BACKGROUND toggle bit */
    }
}

void ADC1_2_IRQHandler(void){
    int16_t i;


    BACKGROUND = 0;                             /* Clear all the toggle bits */
	  SYSTICK = 0;	
	  for(i = 0;i < 0x1000;i++){
		    ADC_VAR = 1;														/* Set the ADC_VAR toggle bit */	
    }	
	  ADC1->SR &= ~(1 << 1);              				/* Clear the end of conversion status bit */   	
	  ADC_VAR = 0;																/* Clear the ADC toggle bit */
}


void SysTick_Handler(void){
    int i;
    msTicks++;
    BACKGROUND = 0;                             /* Clear all the toggle bits */
    ADC_VAR = 0;
    //ADC1->CR2 |= ADC_CR2_SWSTART;             /* Start the ADC conversion */
	  ADC1->CR2 |= (1UL << 22);
    for(i = 0;i < 0x1000;i++){
        SYSTICK = 1;                            /* Set the SYSTICK toggle bit */
    }
    SYSTICK = 0;                                /* Clear the SYSTICK toggle bit */
}

void init_ADC (void)
{
	RCC->APB2ENR |= ( 1UL <<  2);           			// enable periperal clock for GPIOA 
	GPIOA->CRL &= ~0x000000F0;              			// set PIN1 as analog input         
	RCC->CFGR |= ( 3UL << 14);           					// ADC clk = PCLK2 / 8              
	RCC->APB2ENR |= ( 1UL <<  9);           			// enable periperal clock for ADC1  
	ADC1->SQR1 =  0;                     					// Regular chn. Sequence length = 1 
	ADC1->SQR2 =  0;                     					// Clear register                   
	ADC1->SQR3 = ( 1UL <<  0);          				 	// 1. conversion = channel 1        
	ADC1->SMPR2 = ( 5UL <<  3);           				// sample time channel 1  55,5 cyc. 
	ADC1->CR1 = ( 1UL <<  8);           					// Scan mode on                     
	ADC1->CR2 = ( 7UL << 17)| ( 1UL << 20) ;      // select SWSTART and enable external Trigger 
}
