#pragma once

#include <cstdint>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

inline LOG_MODULE_REGISTER(mpu_driver);

class MPU6050 {

public:
  MPU6050(const device *i2c_dev);

private:
  int initialize();

private:
  std::uint8_t id = 0;
  const device *i2c_dev{};

private:
  constexpr static std::uint16_t sleep_time = 1000;
  constexpr static std::uint8_t MPU_ADDR = 0x68;
  constexpr static std::uint8_t MPU_WHO_AM_I_REG = 0x75;

  constexpr static uint8_t SMPLRT_DIV_REG = 0x19;
  constexpr static uint8_t POWER_MNG_REG = 0x6B;
  constexpr static uint8_t ACCEL_CONFIG_REG = 0x1C;
  constexpr static uint8_t ACCEL_X_OUTH_REG = 0x3B;
  constexpr static uint8_t GYRO_CONFIG_REG = 0x1B;
  constexpr static uint8_t GYRO_X_OUTH_REG = 0x44;

  // configuration
  constexpr static uint8_t MPU6050_WAKEUP = 0x00;
  constexpr static uint8_t MPU6050_RESET = 0x80;
  constexpr static uint8_t MPU6050_SET_CLOCK = 0x03;
};