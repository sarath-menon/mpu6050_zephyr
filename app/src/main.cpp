/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/zephyr.h>

#include "mpu6050.hpp"

int main() {

  const float f = 123.456;
  static const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c1));

  MPU6050 imu(i2c_dev);

  while (1) {
    k_msleep(1000);

    printf("%.6f\n", f);
  }
}
