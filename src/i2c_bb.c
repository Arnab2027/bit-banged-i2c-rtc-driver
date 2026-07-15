#include i2c_bb.h

void i2c_init(void) {
    SDA_HIGH();
    SCL_HIGH();
    i2c_delay();
}

void i2c_start(void) {
    SDA_HIGH();
    SCL_HIGH();
    i2c_delay();
    SDA_LOW();   
    i2c_delay();
    SCL_LOW();   
    i2c_delay();
}

void i2c_stop(void) {
    SDA_LOW();
    i2c_delay();
    SCL_HIGH();  
    i2c_delay();
    SDA_HIGH();  
    i2c_delay();
}

uint8_t i2c_write_byte(uint8_t byte) {
    uint8_t bit;
    uint8_t ack;
    for (bit = 0; bit < 8; bit++) {
        if (byte & 0x80) {
            SDA_HIGH();
        } else {
            SDA_LOW();
        }
        i2c_delay();
        SCL_HIGH();
        i2c_delay();
        SCL_LOW();
        byte <<= 1;
    }
    SDA_HIGH();
    i2c_delay();
    SCL_HIGH();
    i2c_delay();
    ack = READ_SDA() ? 1 : 0; // 1 = NACK, 0 = ACK
    SCL_LOW();
    i2c_delay();
    return ack;
}

uint8_t i2c_read_byte(uint8_t send_ack) {
    uint8_t byte = 0;
    uint8_t bit;
    SDA_HIGH();
    i2c_delay();
    for (bit = 0; bit < 8; bit++) {
        SCL_HIGH();
        i2c_delay();
        byte <<= 1;
        if (READ_SDA()) {
            byte |= 1;
        }
        SCL_LOW();
        i2c_delay();
    }
    if (send_ack == 0) {
        SDA_LOW();
    } else {
        SDA_HIGH();
    }
    i2c_delay();
    SCL_HIGH();
    i2c_delay();
    SCL_LOW();
    SDA_HIGH();
    i2c_delay();
    return byte;
}
