#include "protocol_brp.h"

extern volatile uint8_t Timer_tic;

void getData(uint16_t data)
{
  switch(data)
  {
    case RON          :   { SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_6);                                         break; }
    case ROFF         :   { SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_6);                                           break; }
    case KPON         :   { SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_7); PORT_SetBits(MDR_PORTA, PORT_Pin_5);    break; }
    case KPOFF        :   { SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_7);                                           break; }
    case KNON         :   { SendChar(data);  PORT_ResetBits(MDR_PORTA, PORT_Pin_7); PORT_ResetBits(MDR_PORTA, PORT_Pin_5);  break; }
    case KNOFF        :   { SendChar(data);  PORT_SetBits(MDR_PORTA, PORT_Pin_7);                                           break; }
    case SPION        :   { SendChar(data);  SPI1_ON;                                                                       break; }
    case SPIOFF       :   { SendChar(data);  SPI1_OFF;                                                                      break; }
    case D100Hz       :   { SendChar(data);  SetPWM(1);                                                                     break; }
    case D1kHz        :   { SendChar(data);  SetPWM(2);                                                                     break; }
    case D10kHz       :   { SendChar(data);  SetPWM(3);                                                                     break; }
    case D100kHz      :   { SendChar(data);  SetPWM(4);                                                                     break; }
    case D1MHz        :   { SendChar(data);  SetPWM(5);                                                                     break; }
    case D8MHz        :   { SendChar(data);  SetPWM(6);                                                                     break; }
    case DOFF         :   { SendChar(data);  SetPWM(0);                                                                     break; }
    case CHECK        :   { SendChar(data);  /************************************************************/                 break; }
    case BRP_STATUS   :   { SendChar(getStatus());                                                                          break; }
      default         :   SendChar(WRONG_WAY);
  }
}

void InitBRP(void)
{ 
  CPU_init();
  SysTick_init();
  InitUart();
  SPI1_Slave_Init();
  SetPWM(0);
  Init_All_LEDs();
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
    if ((uint8_t)Bit_SET == PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_5)) { status |= (1 << 1); status &= ~(1 << 2); }
    else { status |= (1 << 2); status &= ~(1 << 1); }
    }
  if ((MDR_SSP1->CR1) & (1 << 1)){
    if((MDR_SSP1->SR) & (1 << 4)) status |= (1 << 3) | (1 << 4);
    else { status |= (1 << 3); status &= ~(1 << 4); } 
  }
  else status &= ~((1 << 3) | (1 << 4));
  
  switch(GetPWM()){
    case 0: { status &= ~((1 << 7) | (1 << 6) | (1 << 5));          break; }
    case 1: { status |= (1 << 7); status &= ~((1 << 6) | (1 << 5)); break; }
    case 2: { status |= (1 << 6); status &= ~((1 << 7) | (1 << 5)); break; }
    case 3: { status |= (1 << 7) | (1 << 6); status &= ~(1 << 5);   break; }
    case 4: { status |= (1 << 5); status &= ~((1 << 7) | (1 << 6)); break; }
    case 5: { status |= (1 << 5) | (1 << 7); status &= ~(1 << 6);   break; }
    case 6: { status |= (1 << 5) | (1 << 6); status &= ~(1 << 7);   break; }
      default: status &= ~((1 << 7) | (1 << 6) | (1 << 5));
  }
  return status;
}

void SendDataSPI(uint8_t SYNorTEST)
{
    uint8_t a = 0x00;
    PortE_Bit7 = 0; //НУЖНО ДОБАВИТЬ УСТАНОВКУ SLAVE SELCT КОММУТИРУЕМЫЙ НА PF2 С (PE7)?!
    if(SYNorTEST) a |= (1<<3);
    else a &= ~(1<<3);
    a |= (1<<0);
    Timer_tic = 0;
    a |= (Timer_tic<<4);
    /* byte 1 */
    SSP_SendData(MDR_SSP1, a);
    a |= (1<<1);
    a &= ~((1<<4) | (1<<5) | (1<<6) | (1<<7));
    a |= (Timer_tic<<4);
    /* byte 2 */
    SSP_SendData(MDR_SSP1, a);
    a |= (1<<0) | (1<<1);
    a &= ~((1<<4) | (1<<5) | (1<<6) | (1<<7));
    a = (Timer_tic<<4);
    /* byte 3 */
    SSP_SendData(MDR_SSP1, a);
    a |= (1<<2);
    a &= ~((1<<4) | (1<<5) | (1<<6) | (1<<7));
    a = (Timer_tic<<4);
    /* byte 4 */
    SSP_SendData(MDR_SSP1, a);
    a |= (1<<0) | (1<<2);
    a &= ~((1<<4) | (1<<5) | (1<<6) | (1<<7));
    a = (Timer_tic<<4);
    /* byte 5 */
    SSP_SendData(MDR_SSP1, a);
    PortE_Bit7 = 1; //НУЖНО ДОБАВИТЬ СНЯТИЕ SLAVE SELCT КОММУТИУЕМЫЙ НА PF2 С (PE7)?!
}
