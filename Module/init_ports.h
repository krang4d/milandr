#ifndef __INIT_PORTS_H
#define __INIT_PORTS_H

#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK

void Init_All_LEDs(void);
void BlinkyLed(void);

#endif
