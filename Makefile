# Set the microcontroller and compiler
MCU = atmega328p
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Os -std=c99 -fdata-sections -ffunction-sections
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Set the source files
SRC = main.c utils.c
OBJ = $(SRC:.c=.o)

# Set the output files
TARGET = firmware.hex
OUTPUT = firmware.elf

# Upload port settings (adjust to your setup)
PROGRAMMER = arduino
PORT = /dev/ttyUSB0  # Change this to your actual port

# Default target (build the project)
all: $(TARGET)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create ELF file
$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUTPUT)

# Convert ELF to HEX format
$(TARGET): $(OUTPUT)
	$(OBJCOPY) -O ihex $(OUTPUT) $(TARGET)

# Upload the firmware to the microcontroller
upload: $(TARGET)
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -U flash:w:$(TARGET):i

# Clean the build files
clean:
	rm -f $(OBJ) $(OUTPUT) $(TARGET)


