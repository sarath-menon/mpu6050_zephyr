#include "mpu6050.hpp"

MPU6050::MPU6050(const device *i2c_dev) : i2c_dev{i2c_dev} {
  MPU6050::initialize();
}

int MPU6050::initialize() {
  if (!device_is_ready(i2c_dev)) {
    LOG_ERR("I2C: Device is not ready");
    return -ENODEV;
  }

  // check device id
  if (i2c_reg_read_byte(i2c_dev, MPU_ADDR, MPU_WHO_AM_I_REG, &id) < 0) {
    LOG_ERR("Failed to read chip ID.");
    return -EIO;
  }

  if (id != MPU_ADDR) {
    LOG_ERR("Invalid chip ID.");
    return -EINVAL;
  }

  // reset sensor
  if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, POWER_MNG_REG, MPU6050_RESET) < 0) {
    LOG_ERR("Failed to reset chip.");
    return -EIO;
  }

  k_msleep(100);

  // // gyro z axis as clock source reference
  // if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, POWER_MNG_REG, MPU6050_SET_CLOCK)
  // <
  //     0) {
  //   LOG_ERR("Failed to set clock source for mpu6050");
  //   return -EIO;
  // }

  LOG_INF("Initialized MPU6050 imu sensor");
  return 1;
}