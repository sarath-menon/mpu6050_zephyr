#include "mpu6050.hpp"
#include "stdio.h"
#include <zephyr/sys/byteorder.h>

LOG_MODULE_REGISTER(mpu_driver);

MPU6050::MPU6050(const device *i2c_dev) : i2c_dev{i2c_dev} {
  MPU6050::initialize();
}

std::uint8_t MPU6050::initialize() {

  // check if i2c is ready
  if (!device_is_ready(i2c_dev)) {
    LOG_ERR("I2C: Device is not ready");
    return -ENODEV;
  }

  k_msleep(100);

  // check device id
  if (i2c_reg_read_byte(i2c_dev, MPU_ADDR, MPU_WHO_AM_I_REG, &id_) < 0) {
    LOG_ERR("Failed to read chip ID.");
    return -EIO;
  }

  if (id_ != MPU_ADDR) {
    LOG_ERR("Invalid chip ID.");
    return -EINVAL;
  }

  // // reset sensor
  // if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, POWER_MNG_REG, MPU6050_RESET) <
  // 0) {
  //   LOG_ERR("Failed to reset chip.");
  //   return -EIO;
  // }
  // k_msleep(100);

  uint8_t data{};

  // wakeup sensor
  data = 0x00;
  if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, POWER_MNG_REG, data) < 0) {
    LOG_ERR("Failed to wakeup mpu6050.");
    return -EIO;
  }

  // gyro z axis as clock source reference
  if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, POWER_MNG_REG, MPU6050_SET_CLOCK) <
      0) {
    LOG_ERR("Failed to set clock source for mpu6050");
    return -EIO;
  }

  // set sample rate as 1khz
  data = 0x07;
  if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, SMPLRT_DIV_REG, data) < 0) {
    LOG_ERR("Failed to set mpu6050 sample rate.");
    return -EIO;
  }

  // set accelerometer config, , FS = ± 2g
  data = 0x00;
  if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, ACCEL_CONFIG_REG, data) < 0) {
    LOG_ERR("Failed to set mpu6050 aceel full scale range.");
    return -EIO;
  }

  // set gyroscope config, FS = ± 250°/ s
  data = 0x00;
  if (i2c_reg_write_byte(i2c_dev, MPU_ADDR, GYRO_CONFIG_REG, data) < 0) {
    LOG_ERR("Failed to mpu6050 gyro full scale range.");
    return -EIO;
  }

  LOG_INF("Initialized MPU6050 imu sensor");
  return 1;
}

std::uint8_t MPU6050::read_sensor_data() {
  // holds data received from accel registers
  std::uint16_t buf[6]{};

  // read data 12 bytes: (accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z)
  if (i2c_burst_read(i2c_dev, MPU_ADDR, MPU_DATA_START_REG, (uint8_t *)buf,
                     12) < 0) {
    LOG_ERR("Failed to read data sample.");
    return -EIO;
  }

  // converte from big endian to little endian
  std::int16_t accel_x = sys_be16_to_cpu(buf[0]);
  std::int16_t accel_y = sys_be16_to_cpu(buf[1]);
  std::int16_t accel_z = sys_be16_to_cpu(buf[2]);

  std::int16_t gyro_x = sys_be16_to_cpu(buf[3]);
  std::int16_t gyro_y = sys_be16_to_cpu(buf[4]);
  std::int16_t gyro_z = sys_be16_to_cpu(buf[5]);

  // convert accel readings to full scale range[0 - 16384]
  imu_data_.accel.x = accel_x / accel_lsb_sensitivity;
  imu_data_.accel.y = accel_y / accel_lsb_sensitivity;
  imu_data_.accel.z = accel_z / accel_lsb_sensitivity;

  // convert gyro readings to full scale range[0 - 16384]
  imu_data_.gyro.x = gyro_x / gyro_lsb_sensitivity;
  imu_data_.gyro.y = gyro_y / gyro_lsb_sensitivity;
  imu_data_.gyro.z = gyro_z / gyro_lsb_sensitivity;

  // printf("%.4f\n", imu_data_.accel.x);
  // printf("%.4f\n", imu_data_.gyro.x);

  char str[10]{};
  sprintf(str, "%f", imu_data_.accel.x);
  LOG_INF("Accel x: %s", str);
  sprintf(str, "%f", imu_data_.gyro.y);
  LOG_INF("Gyro x: %s", str);

  return 1;
}

std::uint8_t MPU6050::process_sensor_data() {
  // holds data received from accel registers

  // // convert accel readings to full scale range[0 - 16384]
  // imu_data_.accel.x = accel_x / accel_lsb_sensitivity;
  // imu_data_.accel.y = accel_y / accel_lsb_sensitivity;
  // imu_data_.accel.z = accel_z / accel_lsb_sensitivity;

  // printf("%.4f\n", imu_data_.accel.x);

  return 1;
}