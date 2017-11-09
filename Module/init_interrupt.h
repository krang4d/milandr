#ifndef __INIT_INTERRUPT_H
#define __INIT_INTERRUPT_H

#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_ssp.h"
#include "protocol_brp.h"

//extern volatile uint32_t Delay_dec;

void SysTick_Handler(void);
void SSP2_IRQHandler(void);
void UART2_IRQHandler(void);
void Timer1_IRQHandler(void);
void Timer2_IRQHandler(void);

#endif
