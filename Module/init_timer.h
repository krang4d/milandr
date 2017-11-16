#ifndef __INIT_TIMER_H
#define __INIT_TIMER_H

#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"            // Milandr::Drivers:TIMER
#include <stdio.h>

#define TIMERS_ENABLE   TIMER_Cmd(MDR_TIMER1, ENABLE); TIMER_Cmd(MDR_TIMER2, ENABLE)
#define TIMERS_DISABLE  TIMER_Cmd(MDR_TIMER1, DISABLE); TIMER_Cmd(MDR_TIMER2,DISABLE)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
void InitTimer1(void);
void InitTimer2(void);
void Delay_mks(uint32_t);
void SetPWM(uint8_t);
void InitPWM1(void);
void InitPWM2(void);
uint8_t GetPWM(void);
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
