#ifndef LCD_WIFI_I2C_H
#define LCD_WIFI_I2C_H

#include <stdint.h>

int i2c_open(char *bus, int addr, int *fd);
int i2c_write(int fd, uint8_t data);
int i2c_read(int fd, uint8_t *buf);
int i2c_close(int fd);

#endif // LCD_WIFI_I2C_H
