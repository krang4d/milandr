#include "init_spi.h"

void SPI_ini(void)
{
	PORT_InitTypeDef PORT_InitStructure;
	SSP_InitTypeDef sSSP;

	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP1, ENABLE);

	/* Configure SSP1 pins: TXD, CLK, FSS, RXD,*/
	/* Configure PORTD pins 0, 1, 2, 3 */
	PORT_InitStructure.PORT_Pin	= PORT_Pin_0 | PORT_Pin_1;
	PORT_InitStructure.PORT_OE	= PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
	PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_PD	= PORT_PD_DRIVER;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
	PORT_Init(MDR_PORTC, &PORT_InitStructure);

	PORT_InitStructure.PORT_Pin   = PORT_Pin_2 | PORT_Pin_3;
	PORT_InitStructure.PORT_OE    = PORT_OE_IN;
	PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_PD		= PORT_PD_DRIVER;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
	PORT_Init(MDR_PORTC, &PORT_InitStructure);
	
	SSP_BRGInit(MDR_SSP2,SSP_HCLKdiv1);
	
	SSP_StructInit (&sSSP);
	
	sSSP.SSP_SCR  = 0x00;
	sSSP.SSP_CPSDVSR = 2;
	sSSP.SSP_Mode = SSP_ModeSlave;
	sSSP.SSP_WordLength = SSP_WordLength16b;
	sSSP.SSP_SPH = SSP_SPH_1Edge;
	sSSP.SSP_SPO = SSP_SPO_Low;
	sSSP.SSP_FRF = SSP_FRF_SPI_Motorola;
	sSSP.SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE;
	SSP_Init (MDR_SSP2,&sSSP);

	SSP_Cmd(MDR_SSP2, ENABLE);
}

