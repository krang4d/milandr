#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "init_ports.h"

PORT_InitTypeDef PORT_InitStructure;

void Init_All_LEDs(void)
{
  /* Enable the RTCHSE clock on portE */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);

  /* Configure all ports to the state as after reset, i.e. low power consumption */
  PORT_StructInit(&PORT_InitStructure);
  PORT_Init(MDR_PORTE, &PORT_InitStructure);


  /* Disable the RTCHSE clock on porte */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, DISABLE);
  
   /* Enables the RTCHSE clock on PORTE */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);

  PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(MDR_PORTE, &PORT_InitStructure);

  PORT_SetBits(MDR_PORTE, PORT_Pin_0);
  PORT_SetBits(MDR_PORTE, PORT_Pin_1);
  PORT_SetBits(MDR_PORTE, PORT_Pin_2);
  PORT_SetBits(MDR_PORTE, PORT_Pin_3);
}
