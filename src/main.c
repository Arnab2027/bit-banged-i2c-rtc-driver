#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c_bb.h"
#include "ds1307.h"

/* 
 * Bare-metal UART Print Module
 * Configures the microcontroller's hardware serial port for terminal debugging.
 */
void uart_init(uint32_t baudrate) {
    // Calculate register value for 16MHz clock
    uint16_t ubrr = (16000000UL / (16UL * baudrate)) - 1;
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << TXEN0);                  // Enable Serial Transmitter (TX)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data size, 1 stop bit
}

void uart_putchar(char c) {
    // Wait for transmit buffer to clear (UDRE0 bit goes high)
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c; // Load byte into output buffer register
}

void uart_print_string(const char *str) {
    while (*str) {
        uart_putchar(*str++);
    }
}

int main(void) {
    // 1. Initialize the custom software I2C bus pins
    i2c_init();
    
    // 2. Initialize the serial console at 9600 baud rate
    uart_init(9600);
    
    uart_print_string("Initializing Bit-Banged I2C DS1307 RTC Driver...\r\n");
    
    // 3. Clear Clock Halt (CH) bit to start the clock's internal crystal oscillator
    ds1307_start_clock();
    uart_print_string("Clock Oscillator Started.\r\n");
    
    char buffer[64];
    
    while(1) {
        int8_t seconds = read_rtc_seconds();
        
        if (seconds == -1) {
            uart_print_string("RTC Error: No ACK received from device!\r\n");
        } else {
            // Explicitly cast seconds to integer for safe string formatting
            sprintf(buffer, "RTC Clock - Live Seconds: %d s\r\n", (int)seconds);
            uart_print_string(buffer);
        }
        
        _delay_ms(1000); // Poll the clock register once per second
    }
}
