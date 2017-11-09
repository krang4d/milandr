#include "init_interrupt.h"

extern volatile uint32_t Delay_dec;

void SysTick_Handler(void)
{
  if (Delay_dec) Delay_dec--; 
}

void SSP2_IRQHandler(void)
{
  uint16_t data;
  if (MDR_SSP2->MIS & SSP_IT_RX) //(SSP_GetITStatusMasked(MDR_SSP2, SSP_IT_RX)== SET)
  {
    //SSP_ClearITPendingBit(MDR_SSP2, SSP_IT_RX);
    MDR_SSP2->ICR |= SSP_IT_RX;
    MDR_PORTE->RXTX ^= PORT_Pin_0;
    data = (uint16_t)(MDR_SSP2->DR);
    //MDR_UART2->DR = (data & (uint16_t)0x0FF);
  }
}

void UART2_IRQHandler(void)
{
  uint16_t data;
  if (MDR_UART2->MIS & UART_IT_RX) //(UART_GetITStatusMasked(MDR_UART2, UART_IT_RX)== SET)
  {
    //UART_ClearITPendingBit(MDR_UART2, UART_IT_RX);
    MDR_UART2->ICR |= UART_IT_RX;
    MDR_PORTE->RXTX ^= PORT_Pin_2;
    data = (uint16_t)(MDR_UART2->DR);
    getData(data);
    MDR_UART2->DR = (data & (uint16_t)0x0FF);
  }
  if (MDR_UART2->MIS & UART_IT_TX) //(UART_GetITStatusMasked(MDR_UART2, UART_IT_TX)== SET)
  {
    //UART_ClearITPendingBit(MDR_UART2, UART_IT_TX);
    MDR_UART2->ICR |= UART_IT_TX;
    MDR_PORTE->RXTX ^= PORT_Pin_3;
  }
}

void Timer1_IRQHandler(void)
{
  MDR_PORTE->RXTX ^= PORT_Pin_0;
  MDR_TIMER1->CNT = 0x0000;
  MDR_TIMER1->STATUS &= ~(1 << 1);
  NVIC_ClearPendingIRQ(TIMER1_IRQn);
}

void Timer2_IRQHandler(void)
{
  MDR_PORTE->RXTX ^= PORT_Pin_1;
  MDR_TIMER2->CNT = 0x0000;
  MDR_TIMER2->STATUS &= ~(1 << 1);
  NVIC_ClearPendingIRQ(TIMER2_IRQn);
}
