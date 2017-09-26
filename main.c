#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "init_ports.h"
#include "init_uart.h"

char ch = 0xff;

int main()
{
  Init_All_LEDs();
  InitUart();
  
  while(1)
  {
    SendChar(ch);
  }
}
