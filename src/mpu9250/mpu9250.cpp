#include "mpu9250.h"

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define MAX_I2C_DATA_SIZE 1024

static int i2c_write_byte_data(int addr, int reg, int value)
{
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = value;
    return i2c_write_blocking(i2c_default, addr, buf, 2, false) == 2 ? 0 : -1;
}

static int i2c_read_i2c_block_data(int addr, int reg, int quantity, uint8_t *buffer)
{
    uint8_t buf[MAX_I2C_DATA_SIZE];
    buf[0] = reg;
    int ret = i2c_write_blocking(i2c_default, addr, buf, 1, true);
    if (ret != 1)
    {
        printf("Failed to write to the i2c bus: %d\n", ret);
        return -1;
    }
    ret = i2c_read_blocking(i2c_default, addr, buffer, quantity, false);
    if (ret != quantity)
    {
        printf("Failed to read from the i2c bus: %d\n", ret);
        return -1;
    }
    return 0;
}

MPU9250::MPU9250(
    int address_ak,
    int address_mpu_master,
    int address_mpu_slave,
    int bus,
    int gfs,
    int afs,
    int mfs,
    int mode)
    : gfs(gfs), afs(afs), mfs(mfs), mode(mode), mpu_addr(address_mpu_master), ak_addr(address_ak)
{
}

void MPU9250::writeMaster(int reg, int value, double sleep)
{
    if (i2c_write_byte_data(mpu_addr, reg, value) != 0)
    {
        // throw std::runtime_error("Failed to write to the i2c bus");
        printf("Failed to write to the i2c bus\n");
        for (;;);
    }
    if (sleep > 0)
    {
        sleep_us(sleep * 1000000);
    }
}

void MPU9250::writeAK(int reg, int value, double sleep)
{
    if (i2c_write_byte_data(ak_addr, reg, value) != 0)
    {
        // throw std::runtime_error("Failed to write to the i2c bus");
        printf("Failed to write to the i2c bus\n");
        for (;;);
    }
    if (sleep > 0)
    {
        sleep_us(sleep * 1000000);
    }
}

std::vector<uint8_t> MPU9250::readMaster(int reg, int quantity)
{
    std::vector<uint8_t> buffer(quantity);
    if (i2c_read_i2c_block_data(mpu_addr, reg, quantity, buffer.data()) != 0)
    {
        // throw std::runtime_error("Failed to read from the i2c bus");
        printf("Failed to read from the i2c bus\n");
        for (;;);
    }
    return buffer;
}

std::vector<uint8_t> MPU9250::readAK(int reg, int quantity)
{
    std::vector<uint8_t> buffer(quantity);
    if (i2c_read_i2c_block_data(ak_addr, reg, quantity, buffer.data()) != 0)
    {
        // throw std::runtime_error("Failed to read from the i2c bus");
        printf("Failed to read from the i2c bus\n");
        for (;;);
    }
    return buffer;
}
