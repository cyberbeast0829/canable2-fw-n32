# CANable2 N32H473 Makefile
# #####################################
#
# Ported from STM32G431 to N32H473CEU7
#
#######################################
# user configuration:
#######################################

# SOURCES: list of sources in the user application
SOURCES = main.c system.c system_n32h47x_48x.c can.c slcan.c led.c error.c printf.c interrupts.c usbd_cdc_if.c usb_istr.c

# Get git version and dirty flag
GIT_VERSION := $(shell git describe --abbrev=7 --dirty --always --tags)

# Get git remote URL
GIT_REMOTE := $(shell git config --get remote.origin.url | sed 's/^.*github/github/')

# TARGET: name of the user application
TARGET = canable2-n32-$(GIT_VERSION)

# BUILD_DIR: directory to place output files in
BUILD_DIR = build

# LD_SCRIPT: location of the linker script
LD_SCRIPT = N32H473CEUx_FLASH.ld

# USER_DEFS: user defined macros
USER_DEFS = -DHSE_VALUE=24000000 -DN32H473 -DARM_MATH_CM4

# USER_INCLUDES: user defined includes
USER_INCLUDES =

# USER_CFLAGS: user C flags
USER_CFLAGS = -Wall -g -ffunction-sections -fdata-sections -Os

ifneq ($(EXTERNAL_OSCILLATOR), 1)
USER_CFLAGS += -DINTERNAL_OSCILLATOR
endif

# USER_LDFLAGS: user LD flags
USER_LDFLAGS = -fno-exceptions -ffunction-sections -fdata-sections -Wl,--gc-sections

# TARGET_DEVICE: device to compile for
TARGET_DEVICE = N32H473

#######################################
# end of user configuration
#######################################
#
#######################################
# binaries
#######################################
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
RANLIB = arm-none-eabi-ranlib
SIZE = arm-none-eabi-size
OBJCOPY = arm-none-eabi-objcopy
MKDIR = mkdir -p
#######################################

# core and CPU type for Cortex-M4 with FPU
CPU = cortex-m4
FPU = fpv4-sp-d16

# where to build N32 HAL library
HAL_BUILD_DIR = $(BUILD_DIR)/N32HAL
USB_BUILD_DIR = $(BUILD_DIR)/usb

# Paths within the N32 library
CMSIS_PATH = Drivers/CMSIS
HAL_DRIVER_PATH = Drivers/N32H47x_48x_HAL_Driver
USB_DRIVER_PATH = Drivers/USB_Device_Library

# Includes for GCC
INCLUDES = -I$(CMSIS_PATH)
INCLUDES += -I$(HAL_DRIVER_PATH)/Inc
INCLUDES += -I$(USB_DRIVER_PATH)/Inc
INCLUDES += -Iinc
INCLUDES += $(USER_INCLUDES)

# Macros for GCC
DEFS = $(USER_DEFS) -D$(TARGET_DEVICE)

# Compile GCC flags
CFLAGS = $(DEFS) $(INCLUDES)
CFLAGS += -mcpu=$(CPU) -mthumb -mfloat-abi=hard -mfpu=$(FPU)
CFLAGS += $(USER_CFLAGS)
CFLAGS += -DGIT_VERSION=\"$(GIT_VERSION)\"
CFLAGS += -DGIT_REMOTE=\"$(GIT_REMOTE)\"

# Default action: build the user application
all: $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex


flash: all
	@echo "Flash using: dfu-util or openocd"
	# sudo dfu-util -w -d 0483:df11 -c 1 -i 0 -a 0 -s 0x08000000:leave -D $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the N32 HAL peripheral library
#######################################

HAL_LIB = $(HAL_BUILD_DIR)/libn32hal.a

# List of N32 HAL driver objects
HAL_DRIVER_OBJS = $(addprefix $(HAL_BUILD_DIR)/, $(patsubst %.c, %.o, $(notdir $(wildcard $(HAL_DRIVER_PATH)/Src/*.c))))

# Shortcut for building HAL library
hal: $(HAL_LIB)

$(HAL_LIB): $(HAL_DRIVER_OBJS)
	$(AR) rv $@ $(HAL_DRIVER_OBJS)
	$(RANLIB) $@

$(HAL_BUILD_DIR)/%.o: $(HAL_DRIVER_PATH)/Src/%.c | $(HAL_BUILD_DIR)
	$(CC) -c $(CFLAGS) -o $@ $^

$(HAL_BUILD_DIR):
	$(MKDIR) $@

#######################################
# build the N32 USB library
#######################################

USB_LIB = $(USB_BUILD_DIR)/libn32usb.a

# List of USB driver objects
USB_SOURCES = usbfsd_core.c usbfsd_init.c usbfsd_int.c usbfsd_mem.c usbfsd_regs.c usbfsd_sil.c
USB_OBJECTS = $(addprefix $(USB_BUILD_DIR)/,$(notdir $(USB_SOURCES:.c=.o)))

usb: $(USB_LIB)

$(USB_LIB): $(USB_OBJECTS)
	$(AR) rv $@ $(USB_OBJECTS)
	$(RANLIB) $@

$(USB_BUILD_DIR)/%.o: $(USB_DRIVER_PATH)/Src/%.c | $(USB_BUILD_DIR)
	$(CC) -c $(CFLAGS) -o $@ $^

$(USB_BUILD_DIR):
	$(MKDIR) $@

#######################################
# build the user application
#######################################

# List of user program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.c=.o)))
# Add startup code
OBJECTS += $(BUILD_DIR)/startup_n32h47x_48x_gcc.o

# Libraries to link
LIBS = -ln32hal -ln32usb -lc -lm -lnosys
LDFLAGS = -T $(LD_SCRIPT) -L $(HAL_BUILD_DIR) -L $(USB_BUILD_DIR) -static $(LIBS) $(USER_LDFLAGS)

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(TARGET).elf $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(HAL_LIB) $(USB_LIB)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) \
		$(LDFLAGS) -Xlinker \
		-Map=$(BUILD_DIR)/$(TARGET).map
	$(SIZE) $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Os -c -o $@ $^

$(BUILD_DIR)/%.o: src/%.s | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILD_DIR):
	$(MKDIR) $@

# Clean
clean:
	-rm -rf $(BUILD_DIR)

.PHONY: clean all hal usb flash
