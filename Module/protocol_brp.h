#ifndef __PROTOCOL_X_H
#define __PROTOCOL_X_H

#include "MDR32Fx.h"
#include "init_ports.h"
#include "init_uart.h"
#include "init_spi.h"
#include "init_cpu.h"
#include "init_timer.h"
#include "init_interrupt.h"

#define BUSY        0xf1 //занят выполнением другой команды
#define WRONG_WAY   0xf2 //неправильная команда
#define ERROR       0xf3 //что-то пошло нетак

#define RON         0x11 //включить нагрущку
#define ROFF        0x12 //выключить нагрущку
#define KPON        0x21 //включиь корпус +27В
#define KPOFF       0x22 //выключить корпус +27В
#define KNON        0x23 //включить корпус -27В
#define KNOFF       0x24 //выключить корпус -27В
#define SPION       0x31 //включить цифровой интерфейс
#define SPIOFF      0x32 //выключить цифровой интерфейс
#define D100Hz      0x41 //включить частоту 100 Гц на дискретном интерфейсе
#define D1kHz       0x42 //включить частоту 1 кГц на дискретном интерфейсе
#define D10kHz      0x43 //включить частоту 10 кГц на дискретном интерфейсе
#define D100kHz     0x44 //включить частоту 100 кГц на дискретном интерфейсе
#define D1MHz       0x45 //включить частоту 1 МГц на дискретном интерфейсе
#define D8MHz       0x46 //включить частоту 8.8 МГц на дискретном интерфейсе
#define DOFF        0x4f //отключить фискретный интерфейс
#define CHECK       0x51 //проверка связи с БРП
#define STATUS      0x61 //передать байт состояния

/* Bit STATUS positions: */

void initBRP(void);
void getData(uint16_t data);
uint16_t getStatus(void);

#endif
