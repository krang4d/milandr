#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_config.h"           // Milandr::Device:Startup
#include "MDR32F9Qx_uart.h"             // Milandr::Drivers:UART
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT
#include "MDR32F9Qx_timer.h"            // Milandr::Drivers:TIMER
#include "MDR32F9Qx_ssp.h"              // Milandr::Drivers:SSP

#include "Module/init_ports.h"
#include "Module/init_uart.h"
#include "Module/init_spi.h"
#include "Module/init_cpu.h"
#include "Module/init_timer.h"
#include "Module/init_interrupt.h"
#include "Module/protocol_brp.h"

RST_CLK_FreqTypeDef Clocks;
char a = 0xFF;
char data[4] = {'0'};
char b = 0x00;
char str[] = "Hellow\n";
int i, counter;

int main(void)
{
  while(1)
  {
    //Delay_mks(1000000);
    MDR_PORTE->RXTX ^= PORT_Pin_2;
    
    if ((MDR_PORTA->RXTX & PORT_Pin_2) || (MDR_PORTA->RXTX & PORT_Pin_3) != Bit_RESET)
    {
      SendDataSPI();
    }
  }
}
