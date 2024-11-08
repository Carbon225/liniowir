#ifndef __MPU9250_H__
#define __MPU9250_H__

#define SELF_TEST_X_GYRO 0x00
#define SELF_TEST_Y_GYRO 0x01
#define SELF_TEST_Z_GYRO 0x02

#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E
#define SELF_TEST_Z_ACCEL 0x0F

#define XG_OFFSET_H 0x13
#define XG_OFFSET_L 0x14
#define YG_OFFSET_H 0x15
#define YG_OFFSET_L 0x16
#define ZG_OFFSET_H 0x17
#define ZG_OFFSET_L 0x18

#define XA_OFFSET_H 0x77
#define XA_OFFSET_L 0x78
#define YA_OFFSET_H 0x7A
#define YA_OFFSET_L 0x7B
#define ZA_OFFSET_H 0x7D
#define ZA_OFFSET_L 0x7E

#define SMPLRT_DIV 0x19

#define CONFIG 0x1A

#define GYRO_CONFIG 0x1B

#define ACCEL_CONFIG 0x1C

#define ACCEL_CONFIG_2 0x1D

#define LP_ACCEL_ODR 0x1E

#define WOM_THR 0x1F

#define FIFO_EN 0x23

#define I2C_MST_CTRL 0x24

#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_DO 0x63
#define I2C_SLV0_CTRL 0x27

#define I2C_SLV1_ADDR 0x28
#define I2C_SLV1_REG 0x29
#define I2C_SLV1_DO 0x64
#define I2C_SLV1_CTRL 0x2A

#define I2C_SLV2_ADDR 0x2B
#define I2C_SLV2_REG 0x2C
#define I2C_SLV2_DO 0x65
#define I2C_SLV2_CTRL 0x2D

#define I2C_SLV3_ADDR 0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_DO 0x66
#define I2C_SLV3_CTRL 0x30

#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_DO 0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI 0x35

#define I2C_MST_STATUS 0x36

#define INT_PIN_CFG 0x37

#define INT_ENABLE 0x38

#define INT_STATUS 0x3A

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60

#define I2C_MST_DELAY_CTRL 0x67

#define SIGNAL_PATH_RESET 0x68

#define MOT_DETECT_CTRL 0x69

#define USER_CTRL 0x6A

#define PWR_MGMT_1 0x6B

#define PWR_MGMT_2 0x6C

#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73

#define FIFO_R_W 0x74

#define WHO_AM_I 0x75

#define GFS_250 0x00
#define GFS_500 0x01
#define GFS_1000 0x02
#define GFS_2000 0x03

#define AFS_2G 0x00
#define AFS_4G 0x01
#define AFS_8G 0x02
#define AFS_16G 0x03

#define AK8963_WIA 0x00

#define AK8963_INFO 0x01

#define AK8963_ST1 0x02

#define AK8963_HXL 0x03
#define AK8963_HXH 0x04
#define AK8963_HYL 0x05
#define AK8963_HYH 0x06
#define AK8963_HZL 0x07
#define AK8963_HZH 0x08

#define AK8963_ST2 0x09

#define AK8963_CNTL1 0x0A

#define AK8963_CNTL2 0x0B

#define AK8963_ASTC 0x0C

#define AK8963_TS1 0x0D
#define AK8963_TS2 0x0E

#define AK8963_I2CDIS 0x0F

#define AK8963_ASAX 0x10
#define AK8963_ASAY 0x11
#define AK8963_ASAZ 0x12

#define AK8963_MODE_DOWN 0x00

#define AK8963_MODE_ON 0x01

#define AK8963_BIT_14 0x00
#define AK8963_BIT_16 0x01

#define AK8963_MODE_C8HZ 0x02
#define AK8963_MODE_C100HZ 0x06

#define FIRST_DATA_POSITION ACCEL_XOUT_H
#define ACCEL_OUT ACCEL_XOUT_H
#define GYRO_OUT GYRO_XOUT_H
#define TEMP_OUT TEMP_OUT_H
#define AK8963_MAGNET_OUT AK8963_HXL

#define DEVICE_ID 0x71

#define ACCEL_SCALE_MODIFIER_2G (2.0 / 32768.0)
#define ACCEL_SCALE_MODIFIER_4G (4.0 / 32768.0)
#define ACCEL_SCALE_MODIFIER_8G (8.0 / 32768.0)
#define ACCEL_SCALE_MODIFIER_16G (16.0 / 32768.0)

#define ACCEL_SCALE_MODIFIER_2G_DIV (32768.0 / 2.0)
#define ACCEL_SCALE_MODIFIER_4G_DIV (32768.0 / 4.0)
#define ACCEL_SCALE_MODIFIER_8G_DIV (32768.0 / 8.0)
#define ACCEL_SCALE_MODIFIER_16G_DIV (32768.0 / 16.0)

#define GYRO_SCALE_MODIFIER_250DEG (250.0 / 32768.0)
#define GYRO_SCALE_MODIFIER_500DEG (500.0 / 32768.0)
#define GYRO_SCALE_MODIFIER_1000DEG (1000.0 / 32768.0)
#define GYRO_SCALE_MODIFIER_2000DEG (2000.0 / 32768.0)

#define GYRO_SCALE_MODIFIER_250DEG_DIV (32768.0 / 250.0)
#define GYRO_SCALE_MODIFIER_500DEG_DIV (32768.0 / 500.0)
#define GYRO_SCALE_MODIFIER_1000DEG_DIV (32768.0 / 1000.0)
#define GYRO_SCALE_MODIFIER_2000DEG_DIV (32768.0 / 2000.0)

#define MAGNOMETER_SCALE_MODIFIER_BIT_14 (4912.0 / 8190.0)
#define MAGNOMETER_SCALE_MODIFIER_BIT_16 (4912.0 / 32760.0)

#define MAGNOMETER_SCALE_MODIFIER_BIT_14_DIV (8190.0 / 4912.0)
#define MAGNOMETER_SCALE_MODIFIER_BIT_16_DIV (32760.0 / 4912.0)

#define GRAVITY 9.80665

#define MPU9050_ADDRESS_68 0x68
#define MPU9050_ADDRESS_69 0x69
#define AK8963_ADDRESS 0x0C

#include <vector>
#include <stdexcept>
#include <cstdint>
#include <cstdio>

class MPU9250
{
public:
    MPU9250(
        int address_ak = AK8963_ADDRESS,
        int address_mpu_master = MPU9050_ADDRESS_68,
        int address_mpu_slave = 0,
        int bus = 1,
        int gfs = GFS_2000,
        int afs = AFS_16G,
        int mfs = AK8963_BIT_16,
        int mode = AK8963_MODE_C100HZ);

    void configure()
    {
        printf("Configuring MPU9250\n");
        configureMPU6500(gfs, afs);
        printf("Configured MPU6500\n");
        printf("Configuring AK8963\n");
        configureAK8963(mfs, mode);
        printf("Configured AK8963\n");
    }

    void configureMPU6500(int gfs, int afs)
    {
        if (gfs == GFS_250)
        {
            gres = GYRO_SCALE_MODIFIER_250DEG;
        }
        else if (gfs == GFS_500)
        {
            gres = GYRO_SCALE_MODIFIER_500DEG;
        }
        else if (gfs == GFS_1000)
        {
            gres = GYRO_SCALE_MODIFIER_1000DEG;
        }
        else if (gfs == GFS_2000)
        {
            gres = GYRO_SCALE_MODIFIER_2000DEG;
        }
        else
        {
            // throw std::runtime_error("Invalid GFS");
            printf("Invalid GFS\n");
            for (;;);
        }

        if (afs == AFS_2G)
        {
            ares = ACCEL_SCALE_MODIFIER_2G;
        }
        else if (afs == AFS_4G)
        {
            ares = ACCEL_SCALE_MODIFIER_4G;
        }
        else if (afs == AFS_8G)
        {
            ares = ACCEL_SCALE_MODIFIER_8G;
        }
        else if (afs == AFS_16G)
        {
            ares = ACCEL_SCALE_MODIFIER_16G;
        }
        else
        {
            // throw std::runtime_error("Invalid AFS");
            printf("Invalid AFS\n");
            for (;;);
        }

        writeMaster(PWR_MGMT_1, 0x00, 0.1);

        writeMaster(PWR_MGMT_1, 0x01, 0.1);

        writeMaster(CONFIG, 0x00);

        writeMaster(SMPLRT_DIV, 0x00);

        writeMaster(GYRO_CONFIG, gfs << 3);

        writeMaster(ACCEL_CONFIG, afs << 3);

        writeMaster(ACCEL_CONFIG_2, 0x00);

        writeMaster(INT_PIN_CFG, 0x02, 0.1);

        writeMaster(USER_CTRL, 0x00, 0.1);
    }

    void configureAK8963(int mfs, int mode)
    {
        if (mfs == AK8963_BIT_14)
        {
            mres = MAGNOMETER_SCALE_MODIFIER_BIT_14;
        }
        else if (mfs == AK8963_BIT_16)
        {
            mres = MAGNOMETER_SCALE_MODIFIER_BIT_16;
        }
        else
        {
            // throw std::runtime_error("Invalid MFS");
            printf("Invalid MFS\n");
            for (;;);
        }

        writeAK(AK8963_CNTL1, 0x00, 0.1);

        writeAK(AK8963_CNTL1, 0x0F, 0.1);

        std::vector<uint8_t> data = readAK(AK8963_ASAX, 3);

        writeAK(AK8963_CNTL1, 0x00, 0.1);

        writeAK(AK8963_CNTL1, (mfs << 4 | mode), 0.1);

        magCalibration = {
            (data[0] - 128) / 256.0 + 1.0,
            (data[1] - 128) / 256.0 + 1.0,
            (data[2] - 128) / 256.0 + 1.0};
    }

    void reset()
    {
        resetMPU9250Master();
    }

    void resetMPU9250Master()
    {
        writeMaster(PWR_MGMT_1, 0x80, 0.1);
    }

    std::vector<double> readAccelerometerMaster()
    {
        std::vector<uint8_t> data = readMaster(ACCEL_OUT, 6);
        return convertAccelerometer(data, abias);
    }

    std::vector<double> convertAccelerometer(std::vector<uint8_t> data, std::vector<double> abias)
    {
        return {
            dataConv(data[1], data[0]) * ares - abias[0],
            dataConv(data[3], data[2]) * ares - abias[1],
            dataConv(data[5], data[4]) * ares - abias[2]};
    }

    std::vector<double> readGyroscopeMaster()
    {
        std::vector<uint8_t> data = readMaster(GYRO_OUT, 6);
        return convertGyroscope(data, gbias);
    }

    std::vector<double> convertGyroscope(std::vector<uint8_t> data, std::vector<double> gbias)
    {
        return {
            dataConv(data[1], data[0]) * gres - gbias[0],
            dataConv(data[3], data[2]) * gres - gbias[1],
            dataConv(data[5], data[4]) * gres - gbias[2]};
    }

    std::vector<double> readMagnetometerMaster()
    {
        std::vector<uint8_t> data = readAK(AK8963_MAGNET_OUT, 7);
        return convertMagnetometer(data);
    }

    std::vector<double> convertMagnetometer(std::vector<uint8_t> data)
    {
        if ((data[6] & 0x08) != 0x08)
        {
            double x = dataConv(data[0], data[1]) * mres * magCalibration[0] - mbias[0];
            double y = dataConv(data[2], data[3]) * mres * magCalibration[1] - mbias[1];
            double z = dataConv(data[4], data[5]) * mres * magCalibration[2] - mbias[2];
            x *= magScale[0];
            y *= magScale[1];
            z *= magScale[2];
            return {x, y, z};
        }
        else
        {
            return {0.0, 0.0, 0.0};
        }
    }

    double readTemperatureMaster()
    {
        std::vector<uint8_t> data = readMaster(TEMP_OUT, 2);
        return convertTemperature(data);
    }

    double convertTemperature(std::vector<uint8_t> data)
    {
        double temp = dataConv(data[1], data[0]);
        temp = temp / 333.87 + 21.0;
        return temp;
    }

    std::vector<double> readGyroAccMag()
    {
        std::vector<uint8_t> dataMPU = readMaster(FIRST_DATA_POSITION, 28);
        std::vector<double> dataAK = readMagnetometerMaster();

        std::vector<double> accMaster = convertAccelerometer(std::vector<uint8_t>(dataMPU.begin(), dataMPU.begin() + 6), abias);
        std::vector<double> gyroMaster = convertGyroscope(std::vector<uint8_t>(dataMPU.begin() + 8, dataMPU.begin() + 14), gbias);

        return {
            gyroMaster[0],
            gyroMaster[1],
            gyroMaster[2],
            accMaster[0],
            accMaster[1],
            accMaster[2],
            dataAK[0],
            dataAK[1],
            dataAK[2]};
    }

    double dataConv(int data1, int data2)
    {
        int value = data1 | (data2 << 8);
        if (value & (1 << (16 - 1)))
        {
            value -= (1 << 16);
        }
        return value;
    }

    void writeMaster(int reg, int value, double sleep = 0.0);

    void writeAK(int reg, int value, double sleep = 0.0);

    std::vector<uint8_t> readMaster(int reg, int quantity);

    std::vector<uint8_t> readAK(int reg, int quantity);

private:
    int mpu_addr;
    int ak_addr;
    int gfs;
    int afs;
    int mfs;
    int mode;
    double gres;
    double ares;
    double mres;
    std::vector<double> magCalibration {0.0, 0.0, 0.0};
    std::vector<double> magScale {1.0, 1.0, 1.0};
    std::vector<double> gbias {0.0, 0.0, 0.0};
    std::vector<double> gbias_slave {0.0, 0.0, 0.0};
    std::vector<double> abias {0.0, 0.0, 0.0};
    std::vector<double> abias_slave {0.0, 0.0, 0.0};
    std::vector<double> mbias {0.0, 0.0, 0.0};
};

#endif
