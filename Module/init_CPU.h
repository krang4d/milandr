#ifndef __INIT_CPU_H
#define __INIT_CPU_H

#include "MDR32F9Qx_config.h"           // Milandr::Device:Startup
#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT
#include "MDR32F9Qx_uart.h"             // Milandr::Drivers:UART

void HSE_Init(void);
void HSE_16Mhz_Init (void);
void CPU_init (void);
void SysTick_init(void);

#endif
