#include "init_timer.h"

void InitTimer(void)
{
  MDR_RST_CLK->PER_CLOCK |= 1 << 14; //разрешение тактирования Таймера 1
  MDR_RST_CLK->TIM_CLOCK = (
  4 /*делитель тактовой частоты Таймера 1*/
  |(1 << 24) /*разешение тактирования Таймера 1*/
  );
  NVIC_EnableIRQ(TIMER1_IRQn);
  MDR_TIMER1->CNTRL = 1; /*счет вверх по TIM_CLK, таймер вкл.*/
  MDR_TIMER1->CNT = 0x0;
  
  MDR_TIMER1->PSG = 0x1f;
  MDR_TIMER1->ARR = 0x9895;
  
  MDR_TIMER1->IE = (1 << 1); //разрешение прерывания по совпадению
}
