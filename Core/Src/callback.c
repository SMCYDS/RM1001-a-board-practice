#include "main.h"
// #include "iwdg.h"
#include "gpio.h"
#include "tim.h"

//
// Created by Thomas on 2026/10/1.
//

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == BUT_Pin)
    {
        static uint32_t last_key_tick = 0;
        static uint8_t has_last_key_tick = 0;
        uint32_t now = HAL_GetTick();
        if (!has_last_key_tick || (now - last_key_tick) >= 30U)
        {
            has_last_key_tick = 1;
            last_key_tick = now;
            switch (led_r_status)
            {
                case 0:led_r_status=1;breathe();break;
                case 1:led_r_status=2;blink();break;
                case 2:led_r_status=0;out();break;
                default:break;
            }
            // HAL_IWDG_Refresh(&hiwdg);//watchdog refreshes
        }
    }
}

int stat=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        if (stat)
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);
        else __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
        stat=!stat;
    }
}