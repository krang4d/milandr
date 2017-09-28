#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_uart.h"             // Milandr::Drivers:UART
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Milandr::Drivers:PORT

#include "init_ports.h"
#include "init_uart.h"
#include "init_spi.h"

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

void CPU_init (void)
{
	RST_CLK_DeInit();

	MDR_RST_CLK->HS_CONTROL=0x00000001;            			//включили HSE, режим осциллятор (16МГц)
	while((MDR_RST_CLK->CLOCK_STATUS&0x04)==0x00); 			//подождали пока HSE выйдет в штатный режим
	MDR_EEPROM->CMD=5<<3;	

	MDR_RST_CLK->PLL_CONTROL=(8<<8)|(1<<2);            //включили PLL CPU и задали к-т умножения;
	while((MDR_RST_CLK->CLOCK_STATUS&0x02)==0x00);      //подождали пока PLL CPU выйдет в штатный режим

	MDR_EEPROM->CMD=3<<3;                     //задали задержку для обращения к flash-памяти Delay = 3    
	 
	MDR_RST_CLK->CPU_CLOCK|=0x00000106;     
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
    SSP_SendData(MDR_SSP2, 0x33);
    SendHello();
    BlinkyLed();
  }
}
