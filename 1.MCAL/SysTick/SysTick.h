/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Ahmed Abdulazeem & Ahmed Ragab
 *         File:  SysTick.h
 *        Layer:  MCAL
 *       Module:  SysTick timer
 *      Version:  1.00
 *
 *  Description:  Interfaces Needed by user
 *
 *********************************************************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_

/***************************************************************************************************************************
* \Syntax          : void SysTick_vidInit(void)
* \Description     : Initialize the systick timer
*
* \Sync\Async      : Synchronous
* \Parameters      : None
* \Return value:   : None
***************************************************************************************************************************/
void SysTick_vidInit(void);

/***************************************************************************************************************************
* \Syntax          : void SysTick_delay_ms(u32 time)
* \Description     : take the wanted time to count
*
* \Sync\Async      : Synchronous
* \Parameters      : u32 time
* \Return value:   : None
***************************************************************************************************************************/
void SysTick_delay_ms(u32 time);

/***************************************************************************************************************************
* \Syntax          : void  sethandler(void (*local_pfunc)(void))
(void)

* \Description     : assign the function to handle in interupt in the global pointer to function
*
* \Sync\Async      : Synchronous
* \Parameters      : void (*local_pfunc)(void) "pointer to function"
* \Return value:   : None
***************************************************************************************************************************/
void sethandler(void (*local_pfunc)(void));


/***************************************************************************************************************************
* \Syntax          : void SysTick_Handler(void)

* \Description     : function handle the interrupt when occur
*
* \Sync\Async      : Synchronous
* \Parameters      : None
* \Return value:   : None
***************************************************************************************************************************/

void SysTick_Handler(void);

#endif /* 1_MCAL_SYSTICK_SYSTICK_H_ */
