#include "protocol_brp.h"
#include "init_ports.h"
#include "init_uart.h"
#include "init_spi.h"
#include "init_cpu.h"
#include "init_timer.h"
#include "init_interrupt.h"

static PORT_InitTypeDef PORT_InitStructure;

void getData(uint16_t data)
{
  switch(data)
  {
    case RON      :   {SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_6);                                        break;}
    case ROFF     :   {SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_6);                                          break;}
    case KPON     :   {SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_7); PORT_SetBits(MDR_PORTA, PORT_Pin_5);   break;}
    case KPOFF    :   {SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_7);                                          break;}
    case KNON     :   {SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_7); PORT_ResetBits(MDR_PORTA, PORT_Pin_5); break;}
    case KNOFF    :   {SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_7);                                          break;}
    case SPION    :   {SendChar(data);  MDR_SSP1->CR1 |= (1 << 1);                                                    break;}
    case SPIOFF   :   {SendChar(data);  MDR_SSP1->CR1 &= ~(1 << 1);                                                   break;}
    case D100Hz   :   {SendChar(data);                                                                                break;}
    case D1kHz    :   {SendChar(data);                                                                                break;}
    case D10kHz   :   {SendChar(data);                                                                                break;}
    case D100kHz  :   {SendChar(data);                                                                                break;}
    case D1MHz    :   {SendChar(data);                                                                                break;}
    case D8MHz    :   {SendChar(data);                                                                                break;}
    case DOFF     :   {SendChar(data);  TIMER_Cmd(MDR_TIMER1,DISABLE); TIMER_Cmd(MDR_TIMER2,DISABLE);                 break;}
    case CHECK    :   {SendChar(data);  /***********************************************************/                 break;}
    case STATUS   :   {SendChar(getStatus());                                                                         break;}
      default     :   SendChar(WRONG_WAY);
  }
}

void initBRP(void)
{
  CPU_init();
  //инициализация UART1
  InitUart();
  SPI1_Slave_Init();
  InitPWM();
  //инициализацияя ПОРТОВ PA6, PA5, PA7, отключение нагруски и корпуса
  /* Enable the RTCHSE clock on portE */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTA, &PORT_InitStructure);
  PORT_SetBits(MDR_PORTA, PORT_Pin_0 | PORT_Pin_6 | PORT_Pin_7 | PORT_Pin_5);
  PORT_ResetBits(MDR_PORTA, PORT_Pin_4);
  
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_2 | PORT_Pin_3); //SYN, TEST
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTA, &PORT_InitStructure);
  //выключение цифрового интерфейса и дискретного
}

uint8_t getStatus(void)
{
  uint8_t status = 0x00;
  
  if ((uint8_t)Bit_SET == PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_6)) status &= ~(1 << 0);
    else status |= (1 << 0);
  if ((uint8_t)Bit_SET == PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_7)) { status &= ~(1 << 2);  }
    else status |= ((1 << 1) | (1 << 2));
  if ((uint8_t)Bit_SET == PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_7)) status &= ~(1 << 1) | (1 << 2); 
    else {
      if ((uint8_t)Bit_SET == PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_5)) {status |= (1 << 1); status &= ~(1 << 2);}
        else {status |= (1 << 2); status &= ~(1 << 1);}
    }
  if ((MDR_SSP1->CR1) & (1 << 1)){
    if((MDR_SSP1->SR) & (1 << 4)) status |= (1 << 3) | (1 << 4);
      else { status |= (1 << 3); status &= ~(1 << 4); } 
  }
  else status &= ~((1 << 3) | (1 << 4));
  
  // <<< 5-7 биты дискрктного интерфейса
  
  return status;
}

