#include "init_uart.h"

//#define ROB //инициализация UART2 <<<<<---------после отладки закоментировать для исправления на UART1 (RS422)

void InitUART1(void)
{
  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //тактирование порта B
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //режим работы порта
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); //цифровой
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1UL << 6); //тактирование UART1
  MDR_RST_CLK->UART_CLOCK = (4 /*установка делителя для UART1 = 16*/
  |(1 << 8) /*установка делителя для UART2 = 16*/
  |(1 << 24) /*разрешение тактовой частоты UART1*/
  |(0 << 25)); /*разрешение тактовой частоты UART2*/

  //Параметры делителя при частоте = 5000000Гц и скорости = 115200
  MDR_UART1->IBRD = 0x2; //целая часть делителя скорости
  MDR_UART1->FBRD = 0x2e; //дробная часть делителя скорости
  MDR_UART1->LCR_H = ((0 << 1) /*разрешение проверки четности*/
  |(0 << 2) /*четность/нечетность (нет контроля)*/
  |(0 << 3) /*стоп-бит = 1бит*/
  |(3 << 5) /*длина слова = 8 бит*/
  |(0 << 7)); /*передача бита четности*/

  MDR_UART1->CR = ((1 << 8)|(1 << 9)|1); //передачик и приемник разрешен, разрешение приемопередатчика UART1

  /*Config interrupt*/
  NVIC_EnableIRQ(UART1_IRQn);
  UART_ITConfig(MDR_UART1, UART_IT_RX, ENABLE);
  UART_ITConfig(MDR_UART1, UART_IT_TX, ENABLE);
}

void InitUART2(void)
{
  MDR_RST_CLK->PER_CLOCK |= (1UL << 24); //тактирование порта D

  MDR_PORTD->FUNC |= ((2 << 1*2) | (2 << 0*2)); //режим работы порта
  MDR_PORTD->ANALOG |= ((1 << 1) | (1 << 0)); //цифровой
  MDR_PORTD->PWR |= ((3 << 1*2) | (3 << 0*2)); //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1UL << 7); //тактирование UART2
  MDR_RST_CLK->UART_CLOCK = (0 /*установка делителя для UART1 = undefined*/
  |(4 << 8) /*установка делителя для UART2 = 16*/
  |(0 << 24) /*разрешение тактовой частоты UART1*/
  |(1 << 25)); /*разрешение тактовой частоты UART2*/ 

  //Параметры делителя при частоте = 5000000Гц и скорости = 115200
  MDR_UART2->IBRD = 0x2; //целая часть делителя скорости
  MDR_UART2->FBRD = 0x2e; //дробная часть делителя скорости
  MDR_UART2->LCR_H = ((0 << 1) /*разрешение проверки четности*/
  |(0 << 2) /*четность/нечетность (нет контроля)*/
  |(0 << 3) /*стоп-бит = 1бит*/
  |(3 << 5) /*длина слова = 8 бит*/
  |(0 << 7)); /*передача бита четности*/

  MDR_UART2->CR = ((1 << 8)|(1 << 9)|1); //передачик и приемник разрешен, разрешение приемопередатчика UART2
  
  /*Config interrupt*/
  NVIC_EnableIRQ(UART2_IRQn);
  UART_ITConfig(MDR_UART2, UART_IT_RX, ENABLE);
  UART_ITConfig(MDR_UART2, UART_IT_TX, ENABLE);
}

void InitUart(void)
{
  #ifdef ROB
    InitUART2();
  #else
    InitUART1();
  #endif
}

int SendChar(char ch)
{
#ifdef ROB
  /* Check TXFE flag */
  while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFE)!= SET) ;

  /* Send Data from UART2 */
  UART_SendData (MDR_UART2,(uint16_t)ch);
#else
   /* Check TXFE flag */
  while (UART_GetFlagStatus (MDR_UART1, UART_FLAG_TXFE)!= SET) ;

  /* Send Data from UART2 */
  UART_SendData (MDR_UART1,(uint16_t)ch);
#endif
	return 0;
}

int SendHello(void)
{
  uint16_t i;
  char str[] = "Hello\n";
  for ( i=0; i<7; i++)
  {
    UART_SendData (MDR_UART2,(uint16_t)str[i]);
  }
	return 0;
}

int SendString(char *str, int len)
{
  int i;
  for ( i=0; i<len; i++)
    SendChar(str[i]);
  return 0;
}