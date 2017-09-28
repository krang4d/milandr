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

void CPU_init (void)
{
	RST_CLK_DeInit();
  //Необходимая пауза для работы Flash-памяти программ
  MDR_EEPROM->CMD |= (0 << 3);

  MDR_RST_CLK->HS_CONTROL = 0x01; // вкл. HSE осцилятора 
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ждем пока HSE выйдет в рабочий режим 

  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (3 << 8)); //вкл. PLL | коэф. умножения = 4
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02); //ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK = (2 //источник для CPU_C1
  | (0 << 2) //источник для CPU_C2
  | (0 << 4) //предделитель для CPU_C3
  | (1 << 8));//источник для HCLK
  MDR_BKP->REG_0E |= (5 << 0); //режим встроенного регулятора напряжения DUcc(в зависимости от частоты МК)
  MDR_BKP->REG_0E |= (5 << 3); //выбор доп.стабилизирующей нагрузки
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
