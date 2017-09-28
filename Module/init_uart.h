#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"          // Milandr::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_uart.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
void InitUart(void);
int SendChar(char ch);
int SendHello(void);

int fputc(int ch, FILE *f);
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
