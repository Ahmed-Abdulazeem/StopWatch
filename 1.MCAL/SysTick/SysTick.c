/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Ahmed Abdulazeem & Ahmed Ragab
 *         File:  SysTick.c
 *        Layer:  MCAL
 *       Module:  SysTick timer
 *      Version:  1.00
 *
 *  Description:  Interfaces Needed by user
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Include Libraries
 *********************************************************************************************************************/
#include "../../4.LIB/Platform_Types.h"
#include "../../4.LIB/TM4C123xx.h"
#include "../../4.LIB/Std_Types.h"
#include "../../4.LIB/Bit_Math.h"
#include "../../4.LIB/hw_gpio.h"
#include "SysTick.h"

/*define a global pointer to function*/
void (*glopal_pfunc)(void);

/***************************************************************************************************************************
* \Syntax          : void SysTick_vidInit(void)
* \Description     : Initialize the systick timer
*
* \Sync\Async      : Synchronous
* \Parameters      : None
* \Return value:   : None
***************************************************************************************************************************/
void SysTick_vidInit(void)
{
    NVIC_ST_CTRL_R=2; //1-enable interrupt 2-system clock divide by 4
    NVIC_ST_CURRENT_R=2;// clear the current register value and the clear the count flag
}

/***************************************************************************************************************************
* \Syntax          : void SysTick_delay_ms(u32 time)
* \Description     : take the wanted time to count
*
* \Sync\Async      : Synchronous
* \Parameters      : u32 time
* \Return value:   : None
***************************************************************************************************************************/
void SysTick_delay_ms(u32 time)
{
    u32 preload_value;
    /*convert the time to the valur that will be stored in the preload register to count from it*/
    preload_value=(time *4000)-1;
    /*store the value*/
    NVIC_ST_RELOAD_R=preload_value;
    /*enable the timer*/
    SET_BIT(NVIC_ST_CTRL_R,0);
}

/***************************************************************************************************************************
* \Syntax          : void  sethandler(void (*local_pfunc)(void))
(void)

* \Description     : assign the function to handle in interupt in the global pointer to function
*
* \Sync\Async      : Synchronous
* \Parameters      : void (*local_pfunc)(void) "pointer to function"
* \Return value:   : None
***************************************************************************************************************************/
void sethandler(void (*local_pfunc)(void))
{
    /*assign the function to handle in interupt in the global pointer to function*/
    glopal_pfunc=local_pfunc;
}

/***************************************************************************************************************************
* \Syntax          : void SysTick_Handler(void)

* \Description     : function handle the interupt when ocurr
*
* \Sync\Async      : Synchronous
* \Parameters      : None
* \Return value:   : None
***************************************************************************************************************************/
void SysTick_Handler(void)
{
    glopal_pfunc();
}


