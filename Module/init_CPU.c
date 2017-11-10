#include "init_CPU.h"

#define HCLK_SEL(CPU_C3)       (1<<8)
#define CPU_C1_SEL(HSE)        (1<<1)
#define PCLK_EN(RST_CLK)       (1<<4)
#define HS_CONTROL(HSE_ON)     (1<<0)

#define REG_0F(HSI_ON)        ~(1<<22)
#define RTC_CS(ALRF)           (1<<2)
#define PCLK(BKP)              (1<<27)
#define CPU_C2_SEL(CPU_C2_SEL) (1<<2)

#define PLL_CONTROL_PLL_CPU_ON  (1<<2) //PLL включена. 

void HSE_Init(void)
{
  MDR_RST_CLK->PER_CLOCK |= PCLK_EN(RST_CLK);                 //Включаем тактирование контроллера тактовой частоты (по умолчанию включено).
  MDR_RST_CLK->HS_CONTROL = HS_CONTROL(HSE_ON);               //Разрешаем использование HSE генератора.
  MDR_RST_CLK->CPU_CLOCK  = CPU_C1_SEL(HSE)|HCLK_SEL(CPU_C3); //Настраиваем "путь" сигнала и включаем тактирование от HSE генератора.
  MDR_RST_CLK->PER_CLOCK |= PCLK(BKP);                        //Включаем тактирование часов (для костыля).
	MDR_BKP->RTC_CS |= RTC_CS(ALRF);                            //Костыль для отключения HSI.
	MDR_BKP->REG_0F  = MDR_BKP->REG_0F&(REG_0F(HSI_ON));            //Отключаем HSI.
}
 
void HSE_16Mhz_Init (void)                                                              //Сюда передаем частоту в разах "в 2 раза" например. 
{
	MDR_RST_CLK->PLL_CONTROL  = PLL_CONTROL_PLL_CPU_ON|(1<<8);                                //Включаем PLL, умножение в 2 раза.
  MDR_RST_CLK->HS_CONTROL = HS_CONTROL(HSE_ON);                                             //Разрешаем использование HSE генератора. 
	MDR_RST_CLK->CPU_CLOCK  = CPU_C1_SEL(HSE)|HCLK_SEL(CPU_C3)|CPU_C2_SEL(CPU_C2_SEL) ;       //Настраиваем "путь частоты" и включаем тактирование от HSE генератора.
}

void CPU_init (void)
{
//Необходимая пауза для работы Flash-памяти программ
  MDR_EEPROM->CMD |= (1 << 3);

  MDR_RST_CLK->HS_CONTROL = 0x01; // вкл. HSE осцилятора 
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ждем пока HSE выйдет в рабочий режим 

  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (4 << 8)); //вкл. PLL | коэф. умножения = 5
  while((MDR_RST_CLK->CLOCK_STATUS & (1 << 1)) != 0x02); //ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK = (2 //источник для CPU_C1
  | (1 << 2) //источник для CPU_C2
  | (0 << 4) //предделитель для CPU_C3
  | (1 << 8));//источник для HCLK
  MDR_BKP->REG_0E |= (7 << 0); //режим встроенного регулятора напряжения DUcc(в зависимости от частоты МК)
  MDR_BKP->REG_0E |= (7 << 3); //выбор доп.стабилизирующей нагрузки
}

void SysTick_init(void)
{
  SysTick->LOAD = (80000000/1000000) - 1;
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
}
