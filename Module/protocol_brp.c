#include "protocol_brp.h"

static PORT_InitTypeDef PORT_InitStructure;

void getData(uint16_t data)
{
  switch(data){
    case RON:     {SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_6); break;}
    case ROFF:    {SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_6); break;}
    case KPON:    {SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_7); PORT_SetBits(MDR_PORTA, PORT_Pin_5); break;}
    case KPOFF:   {SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_7); break;}
    case KNON:    {SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_7); PORT_ResetBits(MDR_PORTA, PORT_Pin_5); break;}
    case KNOFF:   {SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_7); break;}
    case SPION:   {SendChar(data);break;}
    case SPIOFF:  {SendChar(data);break;}
    case D100Hz:  {SendChar(data);break;}
    case D1kHz:   {SendChar(data);break;}
    case D10kHz:  {SendChar(data);break;}
    case D100kHz: {SendChar(data);break;}
    case D1MHz:   {SendChar(data);break;}
    case D8MHz:   {SendChar(data);break;}
    case DOFF:    {SendChar(data);break;}
    case CHECK:   {SendChar(data);break;}
    case STATUS:  {SendChar(data);break;}
      default : SendChar(WRONG_WAY);
  }
}

void initBRP(void)
{
  //инициализацияя ПОРТОВ PA6, PA5, PA7, отключение нагруски и корпуса
  /* Enable the RTCHSE clock on portE */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTA, &PORT_InitStructure);
  PORT_SetBits(MDR_PORTA, PORT_Pin_6 | PORT_Pin_7 | PORT_Pin_5);
  //выключение цифрового интерфейса и дискретного
}
