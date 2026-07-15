#ifndef DS1307_H
#define DS1307_H

#include <stdint.h>

#define DS1307_ADDR       0x68
#define DS1307_SEC_REG    0x00

void ds1307_start_clock(void);
int8_t read_rtc_seconds(void);

#endif // DS1307_H
