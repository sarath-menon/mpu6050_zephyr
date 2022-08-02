# SPDX-License-Identifier: Apache-2.0

target_sources(app PRIVATE src/main.cpp src/mpu6050.cpp)

target_include_directories(app PUBLIC include)