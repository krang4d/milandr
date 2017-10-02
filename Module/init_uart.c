#include "init_uart.h"

static PORT_InitTypeDef PortInit;
static UART_InitTypeDef UART_InitStructure;

void InitUart(void)
{
MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //тактирование порта B

  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //тактирование порта B

  MDR_PORTB->FUNC |= ((3 << 0*2) | (3 << 1*2)); //режим работы порта
  MDR_PORTB->ANALOG |= ((1 << 0) | (1 << 1)); //цифровой
  MDR_PORTB->PWR |= ((3 << 0*2) | (3 << 1*2)); //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1UL << 7); //тактирование UART2
  MDR_RST_CLK->UART_CLOCK = (0 /*установка делителя для UART1 = undefined*/
  |(3 << 8) /*установка делителя для UART2 = 8*/
  |(0 << 24) /*разрешение тактовой частоты UART1*/
  |(1 << 25)); /*разрешение тактовой частоты UART2*/ 

  //Параметры делителя при частоте = 4000000Гц и скорости = 115200
  MDR_UART2->IBRD = 0x2; //целая часть делителя скорости
  MDR_UART2->FBRD = 0xb; //дробная часть делителя скорости
  MDR_UART2->LCR_H = ((0 << 1) /*разрешение проверки четности*/
  |(0 << 2) /*четность/нечетность (нет контроля)*/
  |(0 << 3) /*стоп-бит = 1бит*/
  |(3 << 5) /*длина слова = 8 бит*/
  |(0 << 7)); /*передача бита четности*/

  MDR_UART2->CR = ((1 << 8)|(1 << 9)|1); //передачик и приемник разрешен, разрешение приемопередатчика UART2
  
//  /* Enables clock of peripheral PORTD */
//  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);

//  
//  /* Fill PortInit structure*/
//	PortInit.PORT_PULL_UP = PORT_PULL_UP_OFF;
//	PortInit.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
//	PortInit.PORT_PD_SHM = PORT_PD_SHM_OFF;
//	PortInit.PORT_PD = PORT_PD_DRIVER;
//	PortInit.PORT_GFEN = PORT_GFEN_OFF;
//	PortInit.PORT_FUNC = PORT_FUNC_ALTER;
//	PortInit.PORT_SPEED = PORT_SPEED_FAST;
//	PortInit.PORT_MODE = PORT_MODE_DIGITAL;
//  
//  /* Configure PORTD pins 1 (UART2_TX) as output */
//	PortInit.PORT_OE = PORT_OE_OUT;
//	PortInit.PORT_Pin = PORT_Pin_1;
//	PORT_Init(MDR_PORTD, &PortInit);

//	/* Configure PORTD pins 0 (UART2_RX) as input */
//	PortInit.PORT_OE = PORT_OE_IN;
//	PortInit.PORT_Pin = PORT_Pin_0;
//	PORT_Init(MDR_PORTD, &PortInit);
//  
//  /* Select HSI/2 as CPU_CLK source*/
//  //RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, 0);
//  
//  /* Enables the CPU_CLK clock on UART2 */
//  //RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2, ENABLE);
//   /* Set the HCLK division factor = 1 for UART2 */
//	//UART_BRGInit(MDR_UART2, UART_HCLKdiv1);
//  
//  /*Config interrupt*/
//  NVIC_EnableIRQ(UART2_IRQn);
//  UART_ITConfig(MDR_UART2, UART_IT_RX, ENABLE);
//  UART_ITConfig(MDR_UART2, UART_IT_TX, ENABLE);
//  
	/* Initialize UART_InitStructure */
//	UART_InitStructure.UART_BaudRate = 115000;
//	UART_InitStructure.UART_WordLength = UART_WordLength8b;
//	UART_InitStructure.UART_StopBits = UART_StopBits1;
//	UART_InitStructure.UART_Parity = UART_Parity_No;
//	UART_InitStructure.UART_FIFOMode = UART_FIFO_OFF;
//	UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;
 
	/* Configure UART2 parameters*/
//	UART_Init(MDR_UART2, &UART_InitStructure);

	/* Enables UART2 peripheral */
	//UART_Cmd(MDR_UART2, ENABLE);
}

int SendChar(char ch)
{
  /* Check TXFE flag */
//  while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFE)!= SET)
//  {
//  }
  /* Send Data from UART2 */
  UART_SendData (MDR_UART2,(uint16_t)ch);

	return 0;
}

int SendHello(void)
{
  uint16_t i;
  char str[] = "Hellow\n";
  for ( i=0; i<7; i++)
  {
    UART_SendData (MDR_UART2,(uint16_t)str[i]);
  }
	return 0;
}
