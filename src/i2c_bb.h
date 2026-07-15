#ifndef I2C_BB_H
#define I2C_BB_H

#include <avr/io.h>

#define SDA_PIN 4  // PC4
#define SCL_PIN 5  // PC5

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_write_byte(uint8_t byte);
uint8_t i2c_read_byte(uint8_t send_ack);

#endif // I2C_BB_H
