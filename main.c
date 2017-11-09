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

volatile uint32_t Delay_dec = 0;
void Delay_mks(uint32_t Delay_mks_Data)
{
  Delay_dec = Delay_mks_Data;
  while(Delay_dec) {};
}

RST_CLK_FreqTypeDef Clocks;
char a = 0xFF;
char data[4] = {'0'};
char b = 0x00;
char str[] = "Hellow\n";
int i, counter;

int main(void)
{
  CPU_init();
  Init_All_LEDs();
  SysTick_init();
  InitUart();
  //SPI_ini();
  //InitTimer1();
  //InitTimer2();
  //InitPWM(); 
  SPI1_Master_Init();
  SPI2_Slave_Init();
  //SendString(str, 7);
  while(1)
  {
    Delay_mks(1000000);
    SSP_SendData(MDR_SSP2, --a);
    SSP_SendData(MDR_SSP1, --a);
    SSP_SendData(MDR_SSP1, --a);
    SSP_SendData(MDR_SSP1, --a);
    SSP_SendData(MDR_SSP1, --a);
    //Delay_mks(10);
    b = SSP_ReceiveData(MDR_SSP1);
    data[0] = SSP_ReceiveData(MDR_SSP2);
    data[1] = SSP_ReceiveData(MDR_SSP2);
    data[2] = SSP_ReceiveData(MDR_SSP2);
    data[3] = SSP_ReceiveData(MDR_SSP2);
    counter = 0;
    SendChar(b);
      for(i=0; i<4; i++)
      {
//      if (data[i] == 0xFF) counter++;
//      else counter = 0;      
      }
    MDR_PORTE->RXTX ^= PORT_Pin_2;
//    if (counter == 4) MDR_PORTE->RXTX ^= PORT_Pin_1;
//    else MDR_PORTE->RXTX ^= PORT_Pin_2;
//    switch(data){
//      case 'A': MDR_PORTE->RXTX ^= PORT_Pin_1;
//      default : MDR_PORTE->RXTX ^= PORT_Pin_2;
//    }
      
    //SendHello();
    //BlinkyLed();
  }
}
