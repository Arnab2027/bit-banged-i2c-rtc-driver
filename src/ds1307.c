#include "ds1307.h"
#include "i2c_bb.h"

/**
 * Helper function to convert Binary Coded Decimal (BCD) to Decimal
 * 
 * In BCD, a number like 45 is stored as:
 * Upper nibble (bits 4-7): 0100 (4)
 * Lower nibble (bits 0-3): 0101 (5)
 */
uint8_t bcd_to_dec(uint8_t val) {
    return ((val / 16) * 10) + (val % 16);
}

/**
 * Force the DS1307 Oscillator to Start
 * This clears the Clock Halt (CH) bit (Bit 7 of Register 0x00).
 */
void ds1307_start_clock(void) {
    i2c_start();
    i2c_write_byte((DS1307_ADDR << 1) | 0); // Write Mode (LSB = 0)
    i2c_write_byte(DS1307_SEC_REG);         // Point to seconds register (0x00)
    i2c_write_byte(0x00);                   // Write 0 to clear CH bit and start clock
    i2c_stop();
}

/**
 * Read seconds from the DS1307 RTC
 * 
 * @return Decoded seconds value (0-59) or -1 on bus communication error
 */
int8_t read_rtc_seconds(void) {
    uint8_t raw_seconds = 0;
    
    // Step 1: Set the register pointer to 0x00 (Seconds)
    i2c_start();
    if (i2c_write_byte((DS1307_ADDR << 1) | 0)) { // Device Address + Write bit
        i2c_stop();
        return -1; // Device failed to ACK (Error)
    }
    i2c_write_byte(DS1307_SEC_REG);
    i2c_stop();
    
    // Step 2: Read the seconds register data
    i2c_start();
    if (i2c_write_byte((DS1307_ADDR << 1) | 1)) { // Device Address + Read bit
        i2c_stop();
        return -1; // Device failed to ACK (Error)
    }
    raw_seconds = i2c_read_byte(1); // Read 1 byte and send NACK (last byte read)
    i2c_stop();
    
    // Bit 7 is the Clock Halt (CH) flag. Mask it off to keep only the seconds bits (0-6).
    raw_seconds &= 0x7F; 
    
    return bcd_to_dec(raw_seconds);
}
