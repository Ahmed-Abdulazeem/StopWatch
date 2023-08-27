

/**********************************************************************************************************************
 * Include Libraries
 *********************************************************************************************************************/
#include "4.LIB/Bit_Math.h"
#include "4.LIB/Platform_Types.h"
#include "4.LIB/Std_Types.h"
#include "4.LIB/TM4C123xx.h"
#include "4.LIB/hw_gpio.h"

#include "1.MCAL/GPIO/INC/GPIO_Interface.h"
#include "1.MCAL/EXTI/INC/EXTI_Interface.h"
#include "1.MCAL/SysTick/SysTick.h"

#include "2-HAL/LCD/LCD.h"

/*initialize the flags*/
volatile u8 SEC_Counter =0;
volatile u8 isChanged=0;
volatile u8 Start =0;
volatile u8 Pause =0;

void Systick_Timer_callback(void);

void EXTIF0_CallBack(void);
void EXTIF4_CallBack(void);

int main(void)
{
    /*set the function to be handled in the interupt of the systick yimer*/
    sethandler(Systick_Timer_callback);
    /*set GPIO the configration for the reset/lab button and the pause/resume button*/
    const GPIO_Config_t Config[2]={
                                   {GPIO_PORTF,GPIO_PIN0,GPIO_PIN_INPUT,GPIO_PIN_DIGITAL,GPIO_PIN_PUSHPULL,GPIO_PIN_PULLUP,GPIO_2MA_DRIVE,GPIO_ALTFUNC0},
                                   {GPIO_PORTF,GPIO_PIN4,GPIO_PIN_INPUT,GPIO_PIN_DIGITAL,GPIO_PIN_PUSHPULL,GPIO_PIN_PULLUP,GPIO_2MA_DRIVE,GPIO_ALTFUNC0}
    };


    GPIO_Init(Config, 2);

    /*NVIC Enable Port B interrupts*/
    SET_BIT(NVIC_EN0_R,30);

    /*set the interrupt configuration for the buttons*/
    EXTI_Config_t EXTI_Con[4]={{EXTI_PORTF,EXTI_PIN0,EXTI_EDGE,EXTI_FALLING_EDGE},
                               {EXTI_PORTF,EXTI_PIN4,EXTI_EDGE,EXTI_FALLING_EDGE}

    };
    EXTI_Init(EXTI_Con, 2);
    EXTI_SetCallBack(EXTI_PORTF,EXTI_PIN0, EXTIF0_CallBack);
    EXTI_SetCallBack(EXTI_PORTF,EXTI_PIN4, EXTIF4_CallBack);

    /*initialize the LCD */
    LCD_vidInit();
    u8 MIN_Counter = 0;   /*MIN_Counter is a Counter to count number of minutes*/
    u8 time[6] = "00:00"; /* time represents the time string MINs:SECs */
    u8 Labs_count=0;      /*Labs_count is a Counter to count number of Labs Taken*/

    /*move the cursor to row 0 column 2 and print time array (00:00)*/
    LCD_move_cusor(0,2);

    /*First Print 00:00 on the LCD*/
    LCD_vidWriteString(time);

    while(1)
    {
        /*cheking if the reset/lab button is pushed*/
        if(Start == 1)
        {
            /*clear the flag*/
            Start = 0;
            /*checking if the button was pushed while the systick timer was on or not */
            if(GET_BIT(NVIC_ST_CTRL_R,0) == 1)
            {
                /*if it was on then it would take screen shots of the time at the moment the button was pressed  and print it*/
                Labs_count++;
                switch(Labs_count)
                {
                case 1:
                    /*for the first shot move the cursor  to row 0 column 9*/
                    LCD_move_cusor(0,9);
                    break;
                case 2:
                    /*for the first shot move the cursor to row 1 column 1*/

                    LCD_move_cusor(1,1);
                    break;
                case 3:
                    /*for the first shot move the cursor to row 1 column 9*/

                    LCD_move_cusor(1,9);
                    Labs_count=0;
                    break;
                }
                /*print the time */
                LCD_vidWriteChar('>');
                LCD_vidWriteString(time);
            }
            else
            {
                /*if the systick timer was off the button will reset the stop watch */
                /*clear the lcd and clear the time variables */
                LCD_clear();
                time[0] = '0';
                time[1] = '0';
                time[3] = '0';
                time[4] = '0';
                SEC_Counter=0;
                MIN_Counter=0;
                /*initialize the systick timer */
                SysTick_vidInit();
                /*give the timer avalue of 1000ms to fire a interupt when reach it*/
                SysTick_delay_ms(1000);
                LCD_move_cusor(0,2);
                LCD_vidWriteString(time);
            }

        }
        /*check if the pause/resume button is pushed*/
        if(Pause == 1)
        {
            /*if it was pushed toggle the enable bit */
            TOGGLE_BIT(NVIC_ST_CTRL_R,0);
            /*clear the flag */
            Pause=0;
        }

        /*check if the systick timer fire interupt*/
        if(isChanged == 1)
        {
            /*clear the flag*/
            isChanged=0;

            /*check if the seconds exceed 60 second*/
            if(SEC_Counter >= 60)
            {
                /*clear the second counter*/
                time[3] = '0';
                time[4] = '0';
                SEC_Counter=0;
                /*increment the minutes counter*/
                MIN_Counter++;
                /*convert the minutes to string*/
                time[0] = (MIN_Counter%10) +'0';
                time[1] = (MIN_Counter/10) +'0';
            }
            else
            {
                /*convert the second to string*/

                time[4] = (SEC_Counter%10) +'0';
                time[3] = (SEC_Counter/10) +'0';
            }
            //LCD_clear();
            LCD_move_cusor(0,2);
            /*print the time on the lcd */
            LCD_vidWriteString(time);
        }

    }
}
/*call back function for the external interrupt of pin f0*/
void EXTIF0_CallBack(void)
{
    /*set the flag*/
    Start=1;
}
/*call back function for the external interrupt of pin f4*/

void EXTIF4_CallBack(void)
{
    /*set the flag*/
    Pause=1;
}
/*call back function for the systick timer interrupt */

void Systick_Timer_callback(void)
{
    /*increment the seconds counter*/
    SEC_Counter++;
    /*set the flag*/
    isChanged=1;

}
