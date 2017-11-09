#ifndef __INIT_TIMER_H
#define __INIT_TIMER_H

#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"            // Milandr::Drivers:TIMER
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
void InitTimer1(void);
void InitTimer2(void);
void Delay_mks(uint32_t);
void InitPWM(uint8_t);
void InitPWM1(void);
void InitPWM2(void);
uint8_t GetPWM(void);
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
