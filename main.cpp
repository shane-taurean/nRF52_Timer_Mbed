/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <stdint.h>
//#include <my_config.h>
#include <mbed.h>
#include <nrf.h>
extern "C" {
#include "nrf_drv_timer.h"
}
//#include <nrf_delay.h>

DigitalOut led1(LED1);
DigitalOut led2(LED2);

const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(2);

void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)
{
    switch (event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
            break;

        default:
            //Do nothing.
            break;
    }
}

// -----------------------------------------------------------------------------
int main()
{
    uint32_t time_us = 100; //Time(in microseconds) between consecutive compare events.
    uint32_t time_ticks;
    
    led1 = 0;
    led2 = 0;

    if (NRF_ASSERT_PRESENT == 1)    led2 = 1;

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_led_event_handler);    

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_us);
    nrf_drv_timer_compare(&TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, true);
    nrf_drv_timer_enable(&TIMER_LED);

    while(1) {        
        wait_ms(500);
        led1 = !led1;
    }
}
