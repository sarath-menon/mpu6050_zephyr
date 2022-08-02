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

} // namespace imu
