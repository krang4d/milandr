#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_uart.h"             // Milandr::Drivers:UART
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT

#include "init_ports.h"
#include "init_uart.h"

uint16_t i;

int main()
{
  Init_All_LEDs();
  InitUart();
  PORT_SetBits(MDR_PORTE, PORT_Pin_0);
  PORT_SetBits(MDR_PORTE, PORT_Pin_1);
  PORT_SetBits(MDR_PORTE, PORT_Pin_2);
  PORT_SetBits(MDR_PORTE, PORT_Pin_3);
  while(1)
  {
    for(i = 0; i<100000; i++){}
    PORT_ResetBits(MDR_PORTE, PORT_Pin_0);
    for(i = 0; i<100000; i++){}
    PORT_SetBits(MDR_PORTE, PORT_Pin_0);
    for(i = 0; i<100000; i++){}  
  }
}
