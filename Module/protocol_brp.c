#include "protocol_brp.h"

void getData(uint16_t data)
{
  switch(data){
    case RON: {SendChar(data); break;}
    case ROFF: {SendChar(data);break;}
    case KPON: {SendChar(data);break;}
    case KPOFF: {SendChar(data);break;}
    case KNON: {SendChar(data);break;}
    case KNOFF: {SendChar(data);break;}
    case SPION: {SendChar(data);break;}
    case SPIOFF: {SendChar(data);break;}
    case D100Hz: {SendChar(data);break;}
    case D1kHz: {SendChar(data);break;}
    case D10kHz: {SendChar(data);break;}
    case D100kHz: {SendChar(data);break;}
    case D1MHz: {SendChar(data);break;}
    case D8MHz: {SendChar(data);break;}
    case DOFF: {SendChar(data);break;}
    case CHECK: {SendChar(data);break;}
    case STATUS: {SendChar(data);break;}
    default : SendChar(WRONG_WAY);
  }
}

void initBRP(void)
{
  //инициализацияя ПОРТОВ PA6, PA5, PA7, отключение нагруски и корпуса
  //выключение цифрового интерфейса и дискретного
}