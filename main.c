#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_config.h"           // Milandr::Device:Startup
#include "MDR32F9Qx_uart.h"             // Milandr::Drivers:UART
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT

#include "Module/init_ports.h"
#include "Module/init_uart.h"
#include "Module/init_spi.h"

void UART2_IRQHandler(void)
{
  uint16_t data;
  if (UART_GetITStatusMasked(MDR_UART2, UART_IT_RX)== SET)
  {
    UART_ClearITPendingBit(MDR_UART2, UART_IT_RX);
    data = UART_ReceiveData(MDR_UART2);
    UART_SendData(MDR_UART2, data);
  }
}

RST_CLK_FreqTypeDef Clocks;

int main(void)
{
  CPU_init();
  
  SystemCoreClockUpdate();
  RST_CLK_GetClocksFreq(&Clocks);

  Init_All_LEDs();
  InitUart();
  SendHello();
  while(1)
  {
    //Delay_ms(1000);
    SSP_SendData(MDR_SSP2, 0x33);
    SendHello();
    BlinkyLed();
  }
}
