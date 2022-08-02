# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(BOARD nucleo_l476rg)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

add_subdirectory(app)