#ifndef __INIT_SPI_H
#define __INIT_SPI_H

#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_ssp.h"              // Milandr::Drivers:SSP

void SPI_ini(void);
void SPI1_Master_Init(void);
void SPI2_Master_Init(void);
void SPI1_Slave_Init(void);
void SPI2_Slave_Init(void);

#endif
