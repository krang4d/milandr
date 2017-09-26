#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "init_uart.h"

static PORT_InitTypeDef PortInit;
static UART_InitTypeDef UART_InitStructure;

void InitUart(void)
{
  RST_CLK_DeInit();
	RST_CLK_HSEconfig(RST_CLK_HSE_ON );

	if (RST_CLK_HSEstatus() == ERROR)
		while (1);

	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, 0);
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3 );

	/* Enables the HSE clock on PORTB */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);

	/* Fill PortInit structure*/
	PortInit.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PortInit.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PortInit.PORT_PD_SHM = PORT_PD_SHM_OFF;
	PortInit.PORT_PD = PORT_PD_DRIVER;
	PortInit.PORT_GFEN = PORT_GFEN_OFF;
	PortInit.PORT_FUNC = PORT_FUNC_MAIN;
	PortInit.PORT_SPEED = PORT_SPEED_MAXFAST;
	PortInit.PORT_MODE = PORT_MODE_DIGITAL;

	/* Configure PORTB pins 0 (UART1_TX) as output */
	PortInit.PORT_OE = PORT_OE_OUT;
	PortInit.PORT_Pin = PORT_Pin_0;
	PORT_Init(MDR_PORTB, &PortInit);

	/* Configure PORTB pins 1 (UART1_RX) as input */
	PortInit.PORT_OE = PORT_OE_IN;
	PortInit.PORT_Pin = PORT_Pin_1;
	PORT_Init(MDR_PORTB, &PortInit);

	/* Enables the CPU_CLK clock on UART1,UART2 */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_UART1, ENABLE);

	/* Set the HCLK division factor = 1 for UART1,UART2*/
	UART_BRGInit(MDR_UART1, UART_HCLKdiv1 );

	/* Initialize UART_InitStructure */
	UART_InitStructure.UART_BaudRate = 115000;
	UART_InitStructure.UART_WordLength = UART_WordLength8b;
	UART_InitStructure.UART_StopBits = UART_StopBits1;
	UART_InitStructure.UART_Parity = UART_Parity_No;
	UART_InitStructure.UART_FIFOMode = UART_FIFO_ON;
	UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE
												| UART_HardwareFlowControl_TXE;

	/* Configure UART1 parameters*/
	UART_Init(MDR_UART1, &UART_InitStructure);

	/* Enables UART1 peripheral */
	UART_Cmd(MDR_UART1, ENABLE);
}

int SendChar(int ch)
{
	UART_SendD
  ata(MDR_UART1, (uint8_t) ch);
	// Loop until the end of transmission
	while (UART_GetFlagStatus(MDR_UART1, UART_FLAG_TXFF) == SET);

	return (ch);
}
