/**
 * @file    printf.h
 * @brief   Mini printf for CANable2-N32
 */

#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdint.h>

void printf_init(void);
int printf(const char *fmt, ...);

#endif
