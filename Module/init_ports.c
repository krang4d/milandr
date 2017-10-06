#include "init_ports.h"

static PORT_InitTypeDef PORT_InitStructure;

void Init_All_LEDs(void)
{
  /* Enable the RTCHSE clock on portE */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);

  PORT_InitStructure.PORT_Pin   = (PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

  PORT_Init(MDR_PORTE, &PORT_InitStructure);
  
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_0);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  
  PORT_Init(MDR_PORTE, &PORT_InitStructure);
  
  //PORT_SetBits(MDR_PORTE, PORT_Pin_0);
  PORT_SetBits(MDR_PORTE, PORT_Pin_1);
  PORT_SetBits(MDR_PORTE, PORT_Pin_2);
  PORT_SetBits(MDR_PORTE, PORT_Pin_3);
}

void BlinkyLed(void)
{
    int i;
    PORT_ResetBits(MDR_PORTE, PORT_Pin_1);
    for(i = 0; i<1000000; i++){;}
    PORT_SetBits(MDR_PORTE, PORT_Pin_1);
    for(i = 0; i<1000000; i++){;} 
}
