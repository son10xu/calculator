# Build configuration
BUILD_DIR = build
TARGET = stm32_calculator

# Toolchain configuration
TOOLCHAIN_PATH ?=
PREFIX ?= arm-none-eabi-

ifeq ($(TOOLCHAIN_PATH),)
  CC := $(PREFIX)gcc
  AS := $(PREFIX)gcc -x assembler-with-cpp
  CP := $(PREFIX)objcopy
  SZ := $(PREFIX)size
else
  CC := $(TOOLCHAIN_PATH)/$(PREFIX)gcc
  AS := $(TOOLCHAIN_PATH)/$(PREFIX)gcc -x assembler-with-cpp
  CP := $(TOOLCHAIN_PATH)/$(PREFIX)objcopy
  SZ := $(TOOLCHAIN_PATH)/$(PREFIX)size
endif

# MCU flags
CPU = -mcpu=cortex-m0
MCU_FLAGS = $(CPU) -mthumb -mfloat-abi=soft

# Sources and includes
C_SOURCES := $(wildcard src/*.c)
C_INCLUDES := -Iinc


# Compiler and linker flags
OPT = -Og -g -gdwarf-2
C_DEFS = -DSTM32F030x6
CFLAGS = $(MCU_FLAGS) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
LDSCRIPT = STM32F030K6TX_FLASH.ld
LDFLAGS = $(MCU_FLAGS) -specs=nano.specs -T$(LDSCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@echo "Build finished successfully"

$(BUILD_DIR)/%.o: src/%.c Makefile | $(BUILD_DIR)
	@echo "Compiling $<"
	@$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	@echo "Linking $@"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/$(TARGET).elf
	@$(CP) -O ihex $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/$(TARGET).elf
	@$(CP) -O binary -S $< $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
