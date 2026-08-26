/**
 * @file    led.c
 * @brief   LED control using N32 GPIO API
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "led.h"
#include "error.h"
#include "system.h"


// Private variables
static volatile uint32_t led_blue_laston = 0;
static volatile uint32_t led_green_laston = 0;
static uint32_t led_blue_lastoff = 0;
static uint32_t led_green_lastoff = 0;
static uint8_t error_blink_status = 0;
static uint8_t error_was_indicating = 0;
static uint32_t last_errflash = 0;


// Initialize LED GPIOs
void led_init(void)
{
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA |
                            RCC_AHB_PERIPHEN_GPIOB, ENABLE);

    GPIO_InitType gpio;
    GPIO_InitStruct(&gpio);

    // Blue LED on PA15
    gpio.Pin = LED_BLUE_Pin;
    gpio.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    gpio.GPIO_Pull = GPIO_PULL_UP;
    gpio.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    gpio.GPIO_Current = GPIO_DC_2mA;
    gpio.GPIO_Alternate = 0;
    GPIO_InitPeripheral(LED_BLUE_Port, &gpio);

    // Green LED on PB11
    gpio.Pin = LED_GREEN_Pin;
    GPIO_InitPeripheral(LED_GREEN_Port, &gpio);

    // Start with green LED off (active low with pull-up)
    GPIO_WriteBits(LED_GREEN_Port, LED_GREEN_Pin, Bit_SET);
}


// Turn green LED on (active low)
void led_green_on(void)
{
    if (led_green_laston == 0 && (HAL_GetTick() - led_green_lastoff) > LED_DURATION)
    {
        GPIO_WriteBits(LED_GREEN_Port, LED_GREEN_Pin, Bit_RESET);
        led_green_laston = HAL_GetTick();
    }
}


// Turn green LED off
void led_green_off(void)
{
    GPIO_WriteBits(LED_GREEN_Port, LED_GREEN_Pin, Bit_SET);
}


// Blink blue LED (blocking)
void led_blue_blink(uint8_t numblinks)
{
    for (uint8_t i = 0; i < numblinks; i++)
    {
        GPIO_WriteBits(LED_BLUE_Port, LED_BLUE_Pin, Bit_SET);
        HAL_Delay(100);
        GPIO_WriteBits(LED_BLUE_Port, LED_BLUE_Pin, Bit_RESET);
        HAL_Delay(100);
    }
}


// Turn blue LED on
void led_blue_on(void)
{
    if (led_blue_laston == 0 && (HAL_GetTick() - led_blue_lastoff) > LED_DURATION)
    {
        GPIO_WriteBits(LED_BLUE_Port, LED_BLUE_Pin, Bit_SET);
        led_blue_laston = HAL_GetTick();
    }
}


// Process time-based LED events
void led_process(void)
{
    // Turn off green LED if it's been on for LED_DURATION
    if (led_green_laston > 0 && (HAL_GetTick() - led_green_laston) > LED_DURATION)
    {
        GPIO_WriteBits(LED_GREEN_Port, LED_GREEN_Pin, Bit_SET);
        led_green_laston = 0;
        led_green_lastoff = HAL_GetTick();
    }

    // Turn off blue LED if it's been on for LED_DURATION
    if (led_blue_laston > 0 && (HAL_GetTick() - led_blue_laston) > LED_DURATION)
    {
        GPIO_WriteBits(LED_BLUE_Port, LED_BLUE_Pin, Bit_RESET);
        led_blue_laston = 0;
        led_blue_lastoff = HAL_GetTick();
    }

    // Error blink logic
    if (error_last_timestamp() > 0 && (HAL_GetTick() - error_last_timestamp() < 2000))
    {
        error_was_indicating = 1;
        if ((HAL_GetTick() - last_errflash) > 250)
        {
            last_errflash = HAL_GetTick();
            error_blink_status = !error_blink_status;

            if (error_blink_status)
            {
                GPIO_WriteBits(LED_GREEN_Port, LED_GREEN_Pin, Bit_RESET);
                GPIO_WriteBits(LED_BLUE_Port, LED_BLUE_Pin, Bit_SET);
            }
            else
            {
                GPIO_WriteBits(LED_GREEN_Port, LED_GREEN_Pin, Bit_SET);
                GPIO_WriteBits(LED_BLUE_Port, LED_BLUE_Pin, Bit_RESET);
            }
        }
    }
    else if (error_was_indicating)
    {
        error_was_indicating = 0;
        GPIO_WriteBits(LED_GREEN_Port, LED_GREEN_Pin, Bit_SET);
        GPIO_WriteBits(LED_BLUE_Port, LED_BLUE_Pin, Bit_RESET);
    }
}
