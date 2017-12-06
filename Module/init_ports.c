#include "init_ports.h"

static PORT_InitTypeDef PORT_InitStructure;

void Init_All_LEDs(void)
{
  /* Enable the RTCHSE clock on portE */
  //инициализация порта Е для светодиодов на отладочной плате LDMSYSTEMS
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
  
  /************************************/
  /* Enable the RTCHSE clock on portA */
  //инициализацияя ПОРТОВ PA6, PA5, PA7, отключение нагруски и корпуса на БРП
  //инициализация ПОРТОВ PA0, PA4, включение схемы DD1 на передачю A->B, включение схемы DD1 на передачю B->A
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTA, &PORT_InitStructure);
  PORT_SetBits(MDR_PORTA, PORT_Pin_0 | PORT_Pin_6 | PORT_Pin_7 | PORT_Pin_5);
  PORT_ResetBits(MDR_PORTA, PORT_Pin_4);
  
  //инициализацияя ПОРТОВ PA2, PA3 на прием команд SIN, TEST для передачи по SPI слова данных
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_2 | PORT_Pin_3); //SYN, TEST
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTA, &PORT_InitStructure);

  /* Enable the RTCHSE clock on portB */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
  //инициализацияя ПОРТОВ PB9, PB10 на прием команд на прерывание TEST, SIN для передачи по SPI слова данных
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_9 | PORT_Pin_10); //TEST, SYN
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTB, &PORT_InitStructure);

  NVIC_EnableIRQ(EXT_INT2_IRQn); //SYN
  NVIC_EnableIRQ(EXT_INT4_IRQn); //TEST
}

void BlinkyLed(void)
{
    int i;
    PORT_ResetBits(MDR_PORTE, PORT_Pin_1);
    for(i = 0; i<1000000; i++){;}
    PORT_SetBits(MDR_PORTE, PORT_Pin_1);
    for(i = 0; i<1000000; i++){;} 
}
