#include "init_spi.h"

void SPI_ini(void)
{
	PORT_InitTypeDef PORT_InitStructure;
	SSP_InitTypeDef sSSP;

	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP1, ENABLE);

	/* Configure SSP1 pins: TXD, CLK, FSS, RXD,*/
	/* Configure PORTF pins 0, 1, 2, 3 */
	PORT_InitStructure.PORT_Pin	= PORT_Pin_0 | PORT_Pin_1;
	PORT_InitStructure.PORT_OE	= PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
	PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_PD	= PORT_PD_DRIVER;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
	PORT_Init(MDR_PORTF, &PORT_InitStructure);

	PORT_InitStructure.PORT_Pin   = PORT_Pin_2 | PORT_Pin_3;
	PORT_InitStructure.PORT_OE    = PORT_OE_IN;
	PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_PD		= PORT_PD_DRIVER;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
	PORT_Init(MDR_PORTF, &PORT_InitStructure);
	
	SSP_BRGInit(MDR_SSP1,SSP_HCLKdiv1);
	
	SSP_StructInit (&sSSP);
	
	sSSP.SSP_SCR  = 0x00;
	sSSP.SSP_CPSDVSR = 2;
	sSSP.SSP_Mode = SSP_ModeMaster;
	sSSP.SSP_WordLength = SSP_WordLength8b;
	sSSP.SSP_SPH = SSP_SPH_1Edge;
	sSSP.SSP_SPO = SSP_SPO_Low;
	sSSP.SSP_FRF = SSP_FRF_SPI_Motorola;
	sSSP.SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE;
	SSP_Init (MDR_SSP1,&sSSP);

	SSP_Cmd(MDR_SSP1, ENABLE);
}

void SPI_Master_Init(void)
{
  MDR_RST_CLK->PER_CLOCK |= (1UL << 29); //тактирование порта F

  MDR_PORTF->FUNC |= ((2 << 2*2) | (2 << 1*2) | (2 << 3*2) | (2 << 0*2)); //режим работы порта
  MDR_PORTF->ANALOG |= ((1 << 2) | (1 << 1) | (1 << 3) | (1 << 0)); //цифровой
  MDR_PORTF->PWR |= ((3 << 2*2) | (3 << 1*2) | (3 << 3*2) | (3 << 0*2)); //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1 << 8); //тактирование SSP1
  MDR_RST_CLK->SSP_CLOCK = ((2 << 0)|(1 << 24)); //предделитель = 4, разрешение тактирования SSP1 

  MDR_SSP1->CPSR = 2; //делитель тактовой частоты;
  MDR_SSP1->CR0 = (0 << 6); //полярность сигнала
  MDR_SSP1->CR0 |= (0 << 7); //фаза сигнала
  MDR_SSP1->CR0 |= (9 << 8); //коэффициент скорости
  MDR_SSP1->CR0 |= (0 << 4); //формат кадра
  MDR_SSP1->CR0 |= 7; //длина слова = 8 бит
  MDR_SSP1->CR1 |= ((0 << 2)|(1 << 1)); //режим работы и включение приемопередатчика SSP
}

void SPI_Slave_Init(void)
{
  MDR_RST_CLK->PER_CLOCK |= (1UL << 29); //тактирование порта F

  MDR_PORTF->FUNC |= ((2 << 2*2) | (2 << 1*2) | (2 << 3*2) | (2 << 0*2)); //режим работы порта
  MDR_PORTF->ANALOG |= ((1 << 2) | (1 << 1) | (1 << 3) | (1 << 0)); //цифровой
  MDR_PORTF->PWR |= ((3 << 2*2) | (3 << 1*2) | (3 << 3*2) | (3 << 0*2)); //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1 << 8); //тактирование SSP1
  MDR_RST_CLK->SSP_CLOCK = ((2 << 0)|(1 << 24)); //предделитель = 4, разрешение тактирования SSP1 

  MDR_SSP1->CPSR = 2; //делитель тактовой частоты;
  MDR_SSP1->CR0 = (0 << 6); //полярность сигнала
  MDR_SSP1->CR0 |= (0 << 7); //фаза сигнала
  MDR_SSP1->CR0 |= (9 << 8); //коэффициент скорости
  MDR_SSP1->CR0 |= (0 << 4); //формат кадра
  MDR_SSP1->CR0 |= 7; //длина слова = 8 бит
  MDR_SSP1->CR1 |= ((1 << 2)|(1 << 1)); //режим работы и включение приемопередатчика SSP
  MDR_SSP1->CR1 |= (1 << 3); //запрет выходных линий
}


