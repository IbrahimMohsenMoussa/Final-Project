################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/buzzer.c \
../hal/dcMotor.c \
../hal/external_eeprom.c \
../hal/hmi.c \
../hal/lcd.c 

OBJS += \
./hal/buzzer.o \
./hal/dcMotor.o \
./hal/external_eeprom.o \
./hal/hmi.o \
./hal/lcd.o 

C_DEPS += \
./hal/buzzer.d \
./hal/dcMotor.d \
./hal/external_eeprom.d \
./hal/hmi.d \
./hal/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
hal/%.o: ../hal/%.c hal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


