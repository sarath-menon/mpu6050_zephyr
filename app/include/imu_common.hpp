#pragma once
#include <cstdint>

namespace imu {

// holds raw acceleratinn values

struct SensorValues {
  float x;
  float y;
  float z;
};

struct ImuData {
  std::uint32_t timestamp;
  SensorValues accel;
  SensorValues gyro;
};

enum class AccelerometerRange { _2_g, _4_g, _8_g, _16_g };

enum class GyroscopeRange { _250_deg_per_s, _4_g, _8_g, _16_g };

} // namespace imu
