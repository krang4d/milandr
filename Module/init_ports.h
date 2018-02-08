#ifndef __INIT_PORTS_H
#define __INIT_PORTS_H

#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK

#define PortE_Bit7 (*((volatile unsigned long *) 0x4390001c)) //Bit Banding SLAVE SELECT PIN

void Init_All_LEDs(void);

#endif
