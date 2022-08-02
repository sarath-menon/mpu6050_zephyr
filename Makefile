# Build path
BUILD_DIR = build/zephyr

TARGET = zephyr


OPENOCD           ?= openocd
OPENOCD_INTERFACE ?= interface/stlink.cfg
OPENOCD_TARGET    ?= target/stm32l4x.cfg
OPENOCD_CMDS      ?=
LOAD_ADDRESS		       = 0x8000000

# FLash with ST-LINK
stflash: 
	st-flash erase
	st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000


#Flash the stm.
flash:
	$(OPENOCD) -d2 -f $(OPENOCD_INTERFACE) $(OPENOCD_CMDS) -f $(OPENOCD_TARGET) -c init -c targets -c "reset halt" \
                 -c "flash write_image erase $(BUILD_DIR)/$(TARGET).hex" \
                 -c "verify_image $(BUILD_DIR)/$(TARGET).hex" -c "reset run" -c shutdown

reset:
	$(OPENOCD) -d0 -f $(OPENOCD_INTERFACE) $(OPENOCD_CMDS) -f $(OPENOCD_TARGET) -c init -c targets -c "reset" -c shutdown


erase:
	$(OPENOCD) -d2 -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) -c init -c targets -c "halt" -c "stm32f4x mass_erase 0" -c shutdown


