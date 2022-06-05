#include "i2c.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

int i2c_open(char *bus, int addr, int *fd) {
	// Open bus
	if ((*fd = open(bus, O_RDWR)) < 0) {
		return -1;
	}

	// Set bus address
	if (ioctl(*fd, I2C_SLAVE, addr) < 0) {
		return -1;
	}

	return 0;
}

int i2c_write(int fd, uint8_t data) {
	int res = i2c_smbus_write_byte(fd, data);
	if (res < 0) {
		return -1;
	}

	return 0;
}

int i2c_read(int fd, uint8_t *buf) {
	int res = i2c_smbus_read_byte(fd);
	if (res < 0) {
		return -1;
	}

	*buf = res;
	return 0;
}

int i2c_close(int fd) {
	return close(fd);
}
